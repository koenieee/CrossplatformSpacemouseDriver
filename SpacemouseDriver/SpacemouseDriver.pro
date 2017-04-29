#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T15:44:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceMouseDriver
TEMPLATE = app


SOURCES += main.cpp\
    driver/SpaceMouseController.cpp \
    example/ExampleSpaceMouseListener.cpp \
    gui/MainWidget.cpp \
    gui/GeometryEngine.cpp

HEADERS  += \
    driver/hidapi.h \
    driver/SpaceMouseListener.h \
    driver/SpaceMouseController.h \
    example/ExampleSpaceMouseListener.h \
    gui/MainWidget.h \
    gui/GeometryEngine.h

RESOURCES += \
    gui/resources/shaders.qrc \
    gui/resources/textures.qrc

win32 {
!contains(QMAKE_TARGET.arch, x86_64) {
        message("x86 build")
        LIBS += -L"$$PWD/lib/windows/x86/" -lhidapi
    } else {
        message("x86_64 build")
        LIBS += -L"$$PWD/lib/windows/x64/" -lhidapi
    }
}






