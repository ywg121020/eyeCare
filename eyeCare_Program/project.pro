#-------------------------------------------------
#
# Project created by QtCreator 2017-05-15T17:52:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
    basicwidget.cpp \
    mainwindow.cpp \
    lockdialog.cpp

HEADERS  += \
    basicwidget.h \
    mainwindow.h \
    lockdialog.h

FORMS    += \
    mainwindow.ui \
    lockdialog.ui

RESOURCES += \
    scource/scource.qrc

win32:RC_FILE=scource/main.rc

DISTFILES +=

