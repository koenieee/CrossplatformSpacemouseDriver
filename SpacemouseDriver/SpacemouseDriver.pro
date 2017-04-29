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
        gui/visible3dobject.cpp \
    driver/SpaceMouseController.cpp \
    gui/VisibleSpaceMouseListener.cpp

HEADERS  += gui/visible3dobject.h \
    driver/hidapi.h \
    driver/SpaceMouseListener.h \
    driver/SpaceMouseController.h \
    gui/VisibleSpaceMouseListener.h

FORMS    += gui/visible3dobject.ui
