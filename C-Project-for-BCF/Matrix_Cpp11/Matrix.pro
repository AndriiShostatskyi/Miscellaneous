#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T19:34:58
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matrix
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14


SOURCES += main.cpp\
        mainwindow.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    matrix.h

FORMS    += mainwindow.ui
