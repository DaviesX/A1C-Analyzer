#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T21:00:15
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++1y

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = a1c-analyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linkedlist.cpp \
    bst.cpp \
    tst_testlinkedlist.cpp \
    tst_testbst.cpp \
    labmeasure.cpp \
    medicationorder.cpp \
    csv.cpp \
    linkedbst.cpp \
    tst_testcsv.cpp \
    deltaanalysis.cpp \
    analyzer.cpp \
    tst_testanalysis.cpp \
    timeddata.cpp \
    configdialog.cpp

HEADERS  += mainwindow.h \
    linkedlist.h \
    bst.h \
    tst_testlinkedlist.h \
    tst_testbst.h \
    labmeasure.h \
    medicationorder.h \
    csv.h \
    linkedbst.h \
    tst_testcsv.h \
    deltaanalysis.h \
    analyzer.h \
    tst_testanalysis.h \
    timeddata.h \
    configdialog.h

FORMS    += mainwindow.ui \
    configdialog.ui

DISTFILES +=
