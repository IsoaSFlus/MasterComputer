#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T15:50:14
#
#-------------------------------------------------

QT       += core gui \
    serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtcomm.cpp \
    mcu.cpp

HEADERS  += mainwindow.h \
    qtcomm.h \
    mcu.h

FORMS    += mainwindow.ui
