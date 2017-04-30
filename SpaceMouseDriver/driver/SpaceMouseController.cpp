#include "SpaceMouseController.h"


// from Virtual Reality Peripheral Network - vrpn_3DConnexion.C
// and https://www.3dconnexion.com/forum/viewtopic.php?t=1610&start=15
static const int _3DCONNEXION_VENDOR_LOGITECH = 0x046d;			// 1133 // Logitech (3Dconnexion is made by Logitech)
static const int _3DCONNEXION_VENDOR_3DCONNECTION = 0x256F;		// 9583 // 3Dconnexion
static const int _3DCONNEXION_TRAVELER = 0xC623;				// 50723
static const int _3DCONNEXION_NAVIGATOR = 0xC626;				// 50726
static const int _3DCONNEXION_NAVIGATOR_FOR_NOTEBOOKS = 0xc628;	// 50728
static const int _3DCONNEXION_SPACEEXPLORER = 0xc627;			// 50727
static const int _3DCONNEXION_SPACEMOUSE = 0xC603;				// 50691
static const int _3DCONNEXION_SPACEMOUSEPRO = 0xC62B;			// 50731
static const int _3DCONNEXION_SPACEBALL5000 = 0xc621;			// 50721
static const int _3DCONNEXION_SPACEPILOT = 0xc625;				// 50725
static const int _3DCONNEXION_SPACEPILOTPRO = 0xc629;			// 50729



SpaceMouseController::SpaceMouseController(SpaceMouseListener * listener)
    : m_retrieved_data()
    , m_thread(nullptr)
    , m_current_listener(listener)
{

    m_mouse_found = initialize();

    if(m_mouse_found && m_current_listener) //this can't be a nullptr.
    {
        if (!m_current_listener->isSpaceMouseActive() && !m_running)
        {
            m_thread.reset(new std::thread(&SpaceMouseController::run, this));
        }
    }
}

SpaceMouseController::~SpaceMouseController()
{
    m_current_listener->setSpaceMouseActive(false);

    if(m_thread)
    {
        if(m_thread->joinable())
        {
            m_thread->join();
        }
    }
}

bool SpaceMouseController::initialize()
{
    struct hid_device_info * devs;

    unsigned short current_vendor_id = 0x0;
    unsigned short current_product_id = 0x0;

    devs = hid_enumerate(0x0, 0x0);
    m_cur_dev = devs;

    while (m_cur_dev)
    {

        if ((m_cur_dev->vendor_id == _3DCONNEXION_VENDOR_LOGITECH ||
                m_cur_dev->vendor_id == _3DCONNEXION_VENDOR_3DCONNECTION)
                && (m_cur_dev->product_id == _3DCONNEXION_TRAVELER ||
                    m_cur_dev->product_id == _3DCONNEXION_NAVIGATOR ||
                    m_cur_dev->product_id == _3DCONNEXION_NAVIGATOR_FOR_NOTEBOOKS ||
                    m_cur_dev->product_id == _3DCONNEXION_SPACEEXPLORER ||
                    m_cur_dev->product_id == _3DCONNEXION_SPACEMOUSE ||
                    m_cur_dev->product_id == _3DCONNEXION_SPACEMOUSEPRO ||
                    m_cur_dev->product_id == _3DCONNEXION_SPACEBALL5000 ||
                    m_cur_dev->product_id == _3DCONNEXION_SPACEPILOT ||
                    m_cur_dev->product_id == _3DCONNEXION_SPACEPILOTPRO))
        {
            //setup the values with the founded vendor id.s
            current_vendor_id = m_cur_dev->vendor_id;
            current_product_id = m_cur_dev->product_id;

            break; //break when first comaptaible device is found.
        }

        m_cur_dev = m_cur_dev->next;
    }
    hid_free_enumeration(devs);

    if (current_vendor_id == 0x0 || current_product_id == 0x0)
    {
        std::cout << "SpaceMouseInfo: No compatible SpaceMouse device found!\n";
        return false;
    }

    //open device with current_vendor_id and current_product_id
    m_current_opened_handle = hid_open(current_vendor_id, current_product_id, NULL);
    if (!m_current_opened_handle)
    {
        std::cout << "SpaceMouseError: Unable to open device!\n";
        return false;
    }

    std::cout << "SpaceMouseFound! Current Connected SpaceMouse:";
    std::cout << "Manufacturer: "<< current_vendor_id << ",  Product: " << current_product_id << "\n";


    return true;

}

void SpaceMouseController::processData()
{
    switch ((DATATYPE)m_retrieved_data[0])
    {
    case DATATYPE::TRANSLATION:
        if (!m_translation_vector)
        {
            m_TX = (int)convertInput((m_retrieved_data[1] & 0x000000ff), (m_retrieved_data[2]));
            m_TY = (int)convertInput((m_retrieved_data[3] & 0x000000ff), (m_retrieved_data[4]));
            m_TZ = (int)convertInput((m_retrieved_data[5] & 0x000000ff), (m_retrieved_data[6]));
            m_translation_vector = true;
        }
        break;
    case DATATYPE::ROTATION:
        if (!m_rotation_vector)
        {
            m_RX = (int)convertInput((m_retrieved_data[1] & 0x000000ff), (m_retrieved_data[2]));
            m_RY = (int)convertInput((m_retrieved_data[3] & 0x000000ff), (m_retrieved_data[4]));
            m_RZ = (int)convertInput((m_retrieved_data[5] & 0x000000ff), (m_retrieved_data[6]));
            m_rotation_vector = true;
        }
        break;
    case DATATYPE::BUTTON:
        m_current_listener->spaceMouseButton(m_retrieved_data[1]);
        break;
    default:
        break;
    }

    if (m_rotation_vector && m_translation_vector)
    {
        m_current_listener->spaceMouseMovement(m_TX, m_TY, m_TZ, m_RX, m_RY, m_RZ);
        m_translation_vector = false;
        m_rotation_vector = false;
    }
}

int SpaceMouseController::convertInput(int first, unsigned char val)
{
    switch (val)
    {
    case 0:
        return first;
    case 1:
        return first + 255;
    case 254:
        return -512 + first;
    case 255:
        return -255 + first;
    default:
        return 0;
    }
}


void SpaceMouseController::run()
{
    m_running = true;

    m_current_listener->setSpaceMouseActive(true);
    int result = 0;

    while (m_current_listener->isSpaceMouseActive())
    {
        result = hid_read_timeout(m_current_opened_handle, m_retrieved_data, sizeof(m_retrieved_data), 400); //when timeout
        if (result == 0)
        {

        }
        else if (result > 0)
        {
            processData();
            result = 0;
        }
        else
        {
            std::cout << "SpaceMouseLog: Unable to read(), stopping thread.\n";
            stop();
        }
    }
    m_running = false;
    stop();
    std::cout << "SpaceMouseLog: run() has ended\n";
}

void SpaceMouseController::stop()
{
    if (m_current_listener->isSpaceMouseActive())
    {
        m_current_listener->setSpaceMouseActive(false);

        if (m_mouse_found && m_running)
        {
            hid_close(m_current_opened_handle); //only try closing when the handle is open.
            hid_exit();
        }
    }
}
