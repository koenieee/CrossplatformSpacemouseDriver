#ifndef VISIBLE3DOBJECT_H
#define VISIBLE3DOBJECT_H

#include <QMainWindow>

namespace Ui {
class Visible3DObject;
}

class Visible3DObject : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visible3DObject(QWidget *parent = 0);
    ~Visible3DObject();

private:
    Ui::Visible3DObject *ui;
};

#endif // VISIBLE3DOBJECT_H
