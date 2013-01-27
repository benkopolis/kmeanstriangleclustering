#-------------------------------------------------
#
# Project created by QtCreator 2012-12-14T05:34:49
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = clustering
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    KMeans_test.cpp \
    KMeans.cpp \
    kmeanstriangle.cpp

HEADERS += \
    models.hpp \
    KMeans.hpp \
    kmeanstriangle.hpp
