#-------------------------------------------------
#
# Project created by QtCreator 2015-01-27T16:32:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SharedMemory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    contact.h

FORMS    += mainwindow.ui \
    dialog.ui
