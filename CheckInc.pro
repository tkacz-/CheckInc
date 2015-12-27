#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T21:00:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CheckInc
TEMPLATE = app

VERSION = 0.0.0.6
QMAKE_TARGET_PRODUCT = CheckInc
QMAKE_TARGET_COPYRIGHT = Andrei Tkachenko
QMAKE_TARGET_DESCRIPTION = Check increment at a data file


SOURCES += main.cpp\
        CheckInc.cpp \
    CheckIncrement.cpp \
    aboutdialog.cpp \
    coloredprogressbar.cpp

HEADERS  += CheckInc.h \
    aboutdialog.h \
    coloredprogressbar.h

FORMS    += CheckInc.ui \
    aboutdialog.ui

RC_ICONS = CheckInc.ico

RESOURCES += \
    icon.qrc
