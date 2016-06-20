#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T20:34:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    httprequestworker.cpp

HEADERS  += mainwindow.h \
    httprequestworker.h

FORMS    += mainwindow.ui
