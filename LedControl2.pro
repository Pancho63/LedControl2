#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T12:21:03
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LedControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogno.cpp

HEADERS  += mainwindow.h \
    oscpkt.hh \
    dialogno.h

FORMS    += mainwindow.ui \
    dialogno.ui
