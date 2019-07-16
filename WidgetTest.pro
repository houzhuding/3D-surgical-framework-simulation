#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T17:57:31
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calculate.cpp \
    globals.cpp \
    myglwidget.cpp

HEADERS  += mainwindow.h \
    calculate.h \
    angle.h \
    globals.h \
    myglwidget.h

FORMS    += mainwindow.ui \
    calculate.ui

LIBS += -LC:\Users\Michael\Documents\GL\lib
