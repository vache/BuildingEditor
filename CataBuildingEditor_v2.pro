#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T12:53:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CataBuildingEditor_v2
TEMPLATE = app

CONFIG += c++11 debug_and_release

SOURCES += main.cpp\
        buildingeditor.cpp \
    buildingeditorview.cpp \
    drawableitem.cpp \
    tile.cpp \
    buildinginfodialog.cpp \
    buildinginfo.cpp \
    terrain.cpp \
    furniture.cpp \
    trap.cpp \
    jsonparser.cpp \
    options.cpp \
    newbuildingwizard.cpp \
    highlightableitem.cpp \
    buildingmodel.cpp \
    overmapterrain.cpp \
    tripoint.cpp \
    features.cpp \
    jsonwriter.cpp \
    colors.cpp

HEADERS  += buildingeditor.h \
    buildingeditorview.h \
    drawableitem.h \
    tile.h \
    buildinginfodialog.h \
    buildinginfo.h \
    terrain.h \
    furniture.h \
    trap.h \
    jsonparser.h \
    options.h \
    newbuildingwizard.h \
    highlightableitem.h \
    buildingmodel.h \
    overmapterrain.h \
    tripoint.h \
    features.h \
    colors.h \
    jsonwriter.h

FORMS    += buildingeditor.ui \
    buildinginfodialog.ui
