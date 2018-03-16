#-------------------------------------------------
#
# Project created by QtCreator 2017-08-28T14:19:28
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    usrinfo.cpp \
    chatwindow.cpp \
    udpserver.cpp \
    login.cpp \
    friend.cpp \
    changeinfo.cpp

HEADERS  += mainwindow.h \
    usrinfo.h \
    chatwindow.h \
    udpserver.h \
    login.h \
    connection.h \
    friend.h \
    changeinfo.h

FORMS    += mainwindow.ui \
    usrinfo.ui \
    chatwindow.ui \
    login.ui \
    changeinfo.ui

RESOURCES += \
    images/images.qrc
