#-------------------------------------------------
#
# Project created by QtCreator 2013-09-30T18:19:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS3307Asn1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    city.cpp \
    datamanager.cpp

HEADERS  += mainwindow.h \
    city.h \
    datamanager.h

FORMS    += mainwindow.ui
