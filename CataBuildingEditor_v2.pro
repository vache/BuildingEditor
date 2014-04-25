#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T12:53:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CataBuildingEditor_v2
TEMPLATE = app


SOURCES += main.cpp\
        buildingeditor.cpp \
    buildingmodel.cpp \
    buildingtile.cpp \
    building.cpp \
    buildingeditorview.cpp \
    drawableitem.cpp \
    tile.cpp \
    buildinginfodialog.cpp \
    buildinginfo.cpp \
    terrain.cpp \
    furniture.cpp \
    trap.cpp \
    jsonparser.cpp \
    options.cpp

HEADERS  += buildingeditor.h \
    buildingmodel.h \
    buildingtile.h \
    building.h \
    buildingeditorview.h \
    drawableitem.h \
    tile.h \
    buildinginfodialog.h \
    buildinginfo.h \
    terrain.h \
    furniture.h \
    trap.h \
    jsonparser.h \
    options.h

FORMS    += buildingeditor.ui \
    buildinginfodialog.ui
