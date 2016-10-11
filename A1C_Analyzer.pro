#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T21:00:15
#
#-------------------------------------------------

QT       += core gui

CONFIG  += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A1C_Analyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linkedlist.cpp \
    bst.cpp \
    tst_testlinkedlist.cpp \
    tst_testbst.cpp

HEADERS  += mainwindow.h \
    linkedlist.h \
    bst.h \
    tst_testlinkedlist.h \
    tst_testbst.h

FORMS    += mainwindow.ui
