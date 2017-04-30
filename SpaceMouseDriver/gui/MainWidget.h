#pragma once

#include "GeometryEngine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "../driver/SpaceMouseListener.h"


class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions, public SpaceMouseListener
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    bool isSpaceMouseActive() override;
    void setSpaceMouseActive(bool value) override;
    void spaceMouseMovement(const int &TX, const int &TY, const int &TZ, const int &RX, const int &RY, const int &RZ) override;
    void spaceMouseButton(const int &id) override;

protected:
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 2.30;
    QQuaternion rotation;

    bool space_mouse_active = false;
};

