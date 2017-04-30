#pragma once

#include <string>
#include <thread>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
#include <iostream>
#include "SpaceMouseListener.h"


class SpaceMouseController
{

public:
    SpaceMouseController(SpaceMouseListener * spacemouse_listener);
    ~SpaceMouseController();
    void run();
    void stop();

private:

    // variables SpaceMouse
    bool            m_translation_vector;
    bool            m_rotation_vector;
    bool            m_mouse_found;
    bool            m_running = false;
    int             m_TX = 0;
    int             m_TY = 0;
    int             m_TZ = 0;
    int             m_RX = 0;
    int             m_RY = 0;
    int             m_RZ = 0;
    unsigned char	m_retrieved_data[7] = { 0 };


    enum class DATATYPE
    {
        TRANSLATION =       1,
        ROTATION    =       2,
        BUTTON      =       3
    };

    std::unique_ptr<std::thread>    m_thread;
    hid_device *                    m_current_opened_handle;
    struct hid_device_info *        m_cur_dev;
    SpaceMouseListener *            m_current_listener;

    void processData();
    bool initialize();
    int convertInput(int first, unsigned char val);





};


