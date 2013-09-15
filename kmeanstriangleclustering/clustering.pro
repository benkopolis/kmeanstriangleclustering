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
    KMeans.cpp \
    kmeanstriangle.cpp \
    ui/clusteringview.cpp \
    readers/abstractdatareader.cpp \
    readers/defaultnormalizedformatdatareader.cpp \
    spaces/abstractpointsspace.cpp \
    spaces/pointsspace.cpp \
    spaces/normalizedpointsspace.cpp \
    kmeanscomparer.cpp \
    tfidf/stemmedfileinmemoryparser.cpp \
    commons/abstractcenterspicker.cpp \
    commons/sequentialcenterspicker.cpp

HEADERS += \
    models.hpp \
    KMeans.hpp \
    kmeanstriangle.hpp \
    ui/clusteringview.h \
    readers/abstractdatareader.h \
    readers/defaultnormalizedformatdatareader.h \
    spaces/abstractpointsspace.h \
    spaces/pointsspace.h \
    spaces/normalizedpointsspace.h \
    kmeanscomparer.h \
    tfidf/stemmedfileinmemoryparser.h \
    commons/abstractcenterspicker.h \
    commons/sequentialcenterspicker.h

FORMS += \
    ui/clusteringview.ui
