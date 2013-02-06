#-------------------------------------------------
#
# Project created by QtCreator 2012-12-14T05:34:49
#
#-------------------------------------------------

QT       += core

QT       += gui

TARGET = clustering
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    KMeans_test.cpp \
    KMeans.cpp \
    kmeanstriangle.cpp \
    ui/clusteringview.cpp \
    readers/abstractdatareader.cpp \
    readers/defaultnormalizedformatdatareader.cpp

HEADERS += \
    models.hpp \
    KMeans.hpp \
    kmeanstriangle.hpp \
    ui/clusteringview.h \
    readers/abstractdatareader.h \
    readers/defaultnormalizedformatdatareader.h

FORMS += \
    ui/clusteringview.ui
