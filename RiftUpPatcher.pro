#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T22:45:50
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wno-long-long
QMAKE_CXXFLAGS_DEBUG += -D_GLIBCXX_DEBUG -DDEBUG
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG

CONFIG += static

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RiftUp!Patcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    patch.cpp

HEADERS  += mainwindow.h \
    patch.h
