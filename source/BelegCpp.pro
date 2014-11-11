#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T17:05:29
#
#-------------------------------------------------

QT       += core gui
QT        += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BelegCpp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp \
    dialognewentry.cpp \
    dialogsearchcriteria.cpp \
    dialogsettings.cpp \
    dialogsimpleentry.cpp \
    flowlayout.cpp \
    simplecriteria.cpp \
    entrywidget.cpp \
    entrydetails.cpp \
    entryentity.cpp \
    dialoghelp.cpp \
    headerwidget.cpp


HEADERS  += mainwindow.h \
    databasemanager.h \
    dialognewentry.h \
    dialogsearchcriteria.h \
    dialogsettings.h \
    dialogsimpleentry.h \
    flowlayout.h \
    simplecriteria.h \
    entrywidget.h \
    entrydetails.h \
    entryentity.h \
    dialoghelp.h \
    headerwidget.h


FORMS    += mainwindow.ui \
    dialognewentry.ui \
    dialogsearchcriteria.ui \
    dialogsettings.ui \
    dialogsimpleentry.ui \
    simplecriteria.ui \
    entrywidget.ui \
    entrydetails.ui \
    headerwidget.ui \
    dialoghelp.ui

RESOURCES += \
    ressourcesCollection.qrc


