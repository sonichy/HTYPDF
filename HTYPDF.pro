#-------------------------------------------------
#
# Project created by QtCreator 2020-04-23T12:02:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HTYPDF
TEMPLATE = app

PKGCONFIG += poppler-qt5
CONFIG += c++14 link_pkgconfig

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc