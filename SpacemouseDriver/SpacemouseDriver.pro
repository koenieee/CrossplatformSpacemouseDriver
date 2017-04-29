#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T15:44:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpacemouseDriver
TEMPLATE = app


SOURCES += main.cpp\
    driver/SpaceMouseController.cpp \
    gui/VisibleSpaceMouseListener.cpp \
    gui/MainWidget.cpp \
    gui/GeometryEngine.cpp

HEADERS  += \
    driver/hidapi.h \
    driver/SpaceMouseListener.h \
    driver/SpaceMouseController.h \
    gui/VisibleSpaceMouseListener.h \
    gui/MainWidget.h \
    gui/GeometryEngine.h

RESOURCES += \
    gui/resources/shaders.qrc \
    gui/resources/textures.qrc

LIBS += -L"$$PWD/lib/x64/" -lhidapi



