#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T11:34:56
#
#-------------------------------------------------

QT       += core gui printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhotoElectricEffect


DESTDIR = bin
targetinstall.path = /usr/local/bin/PhotoElectricEffect
targetinstall.files = bin/PhotoElectricEffect

INSTALLS += targetinstall

icon.path = /usr/local/PhotoElectricEffect
icon.files = data/iconPhotoElectricEffect.png
icon.extra = cp data/PhotoElectricEffect.desktop ~/Desktop/PhotoElectricEffect.desktop

INSTALLS += icon


TEMPLATE = app

OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/serialmaster.cpp \
    src/keithley.cpp \
    src/qcustomplot.cpp \
    src/graph.cpp

INCLUDEPATH += include
HEADERS  += include/mainwindow.h \
    include/serialmaster.h \
    include/keithley.h \
    include/qcustomplot.h \
    include/graph.h

FORMS += form/mainwindow.ui \

QMAKE_CXXFLAGS += -std=c++0x
