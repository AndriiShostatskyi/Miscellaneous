#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T12:20:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scheduler
TEMPLATE = app


SOURCES += main.cpp\
        scheduler.cpp \
    database.cpp \
    dateTimeDelegate.cpp \
    comboBoxDelegate.cpp

HEADERS  += scheduler.h \
    database.h \
    dateTimeDelegate.h \
    comboBoxDelegate.h

FORMS    += scheduler.ui
