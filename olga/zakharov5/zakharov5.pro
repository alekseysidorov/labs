#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T22:17:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zakharov5
TEMPLATE = app
CONFIG += C++11


SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp \
    generator.cpp

HEADERS  += mainwindow.h \
    paintwidget.h \
    generator.h

FORMS    += mainwindow.ui
