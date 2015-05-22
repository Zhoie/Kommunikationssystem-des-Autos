#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T19:34:11
#
#-------------------------------------------------

QT       += core gui

TARGET = serialcom
TEMPLATE = app

include(./src/qextserialport.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    uartobject.cpp \
    uartwidget.cpp \
    gpswidget.cpp \
    mainwidget.cpp \
    gsmwidget.cpp \
    nmea/tok.c \
    nmea/time.c \
    nmea/sentence.c \
    nmea/parser.c \
    nmea/parse.c \
    nmea/info.c \
    nmea/gmath.c \
    nmea/generator.c \
    nmea/generate.c \
    nmea/context.c \
    controllerobject.cpp

HEADERS  += mainwindow.h \
    uartobject.h \
    uartwidget.h \
    gpswidget.h \
    mainwidget.h \
    gsmwidget.h \
    nmea/units.h \
    nmea/tok.h \
    nmea/time.h \
    nmea/sentence.h \
    nmea/parser.h \
    nmea/parse.h \
    nmea/nmea.h \
    nmea/info.h \
    nmea/gmath.h \
    nmea/generator.h \
    nmea/generate.h \
    nmea/context.h \
    nmea/config.h \
    controllerobject.h


FORMS    +=
