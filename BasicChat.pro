QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BChat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS



SOURCES += \
    main.cpp \
    server/serverwidget.cpp \
    client/clientwidget.cpp

HEADERS += \
    server/serverwidget.h \
    client/clientwidget.h


FORMS += \
    client/clientwidget.ui \
    server/serverwidget.ui

CONFIG += C++14

RESOURCES += \
    bchat.qrc


