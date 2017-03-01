#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T21:00:15
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = a1c-analyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    labmeasure.cpp \
    medicationorder.cpp \
    csv.cpp \
    tst_testcsv.cpp \
    tst_testanalysis.cpp \
    configdialog.cpp \
    drugfilter.cpp \
    database.cpp \
    querydialog.cpp \
    delta.cpp \
    labfilter.cpp \
    patientrecord.cpp \
    dataset.cpp \
    statistics.cpp

HEADERS  += mainwindow.h \
    labmeasure.h \
    medicationorder.h \
    csv.h \
    tst_testcsv.h \
    tst_testanalysis.h \
    configdialog.h \
    drugfilter.h \
    database.h \
    querydialog.h \
    delta.h \
    labfilter.h \
    patientrecord.h \
    dataset.h \
    statistics.h

FORMS    += mainwindow.ui \
    configdialog.ui \
    querydialog.ui

DISTFILES +=
