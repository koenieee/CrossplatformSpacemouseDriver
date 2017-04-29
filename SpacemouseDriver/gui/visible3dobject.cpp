#include "visible3dobject.h"
#include "ui_visible3dobject.h"

Visible3DObject::Visible3DObject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visible3DObject)
{
    ui->setupUi(this);
}

Visible3DObject::~Visible3DObject()
{
    delete ui;
}
