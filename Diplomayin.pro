#-------------------------------------------------
#
# Project created by QtCreator 2017-09-08T10:53:16
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diplomayin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processutil.cpp \
    chartshelper.cpp

HEADERS  += mainwindow.h \
    processutil.h \
    chartshelper.h

FORMS    += mainwindow.ui

LIBS += -lKernel32\
        -lPsapi
