#-------------------------------------------------
#
# Project created by QtCreator 2014-01-11T23:39:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Metro_Paris
TEMPLATE = app


SOURCES += main.cpp\
    station.cpp \
    reseauparis.cpp \
    ligne.cpp \
    trajetunit.cpp \
    dijkstra.cpp \
    estimdurees.cpp \
    interface.cpp \
    ongletdetailtrajet.cpp

HEADERS  += \
    station.h \
    reseauparis.h \
    ligne.h \
    trajetunit.h \
    dijkstra.h \
    estimdurees.h \
    interface.h \
    ongletdetailtrajet.h

FORMS    += mainwindow.ui
