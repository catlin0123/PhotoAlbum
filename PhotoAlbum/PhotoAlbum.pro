#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T14:41:23
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhotoAlbum
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlparser.cpp

HEADERS  += mainwindow.h \
    xmlparser.h \
    Photo.h

FORMS    += mainwindow.ui
