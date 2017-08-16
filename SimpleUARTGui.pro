#-------------------------------------------------
#
# Project created by QtCreator 2017-08-16T19:12:22
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleUARTGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myuartcontroller.cpp

HEADERS  += mainwindow.h \
    myuartcontroller.h

FORMS    += mainwindow.ui
