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
    xmlparser.cpp \
    pictureedits.cpp \
    resizewindow.cpp \
    cropfunction.cpp \
    descriptionwindow.cpp

#RESOURCES = mainwindow.qrc #possibly. but we dont have one, so.

HEADERS  += mainwindow.h \
    xmlparser.h \
    Photo.h \
    pictureedits.h \
    resizewindow.h \
    cropfunction.h \
    descriptionwindow.h

FORMS    += mainwindow.ui \
    pictureedits.ui \
    resizewindow.ui \
    descriptionwindow.ui
