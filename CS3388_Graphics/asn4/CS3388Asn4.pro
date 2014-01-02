#-------------------------------------------------
#
# Project created by QtCreator 2013-12-03T17:10:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS3388Asn4
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    ray.cpp \
    sphere.cpp \
    matrixoperations.cpp \
    camera.cpp \
    trace.cpp \
    plane.cpp \
    light.cpp \
    dialog.cpp \
    object.cpp

HEADERS  += mainwindow.h \
    ray.h \
    sphere.h \
    matrixoperations.h \
    camera.h \
    trace.h \
    plane.h \
    light.h \
    dialog.h \
    object.h

FORMS    += mainwindow.ui \
    dialog.ui
