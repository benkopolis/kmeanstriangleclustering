#-------------------------------------------------
#
# Project created by QtCreator 2012-12-14T05:34:49
#
#-------------------------------------------------

QT       += core

QT       += gui

TARGET = clustering
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11


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
    tfidf/stemmedfileinmemoryparser.cpp \
    pickers/abstractcenterspicker.cpp \
    pickers/sequentialcenterspicker.cpp \
    pickers/randomcenterpicker.cpp \
    triangle/abstractaccountingcontainer.cpp \
    triangle/upperbounds.cpp \
    exceptions/badindex.cpp \
    commons/partitiondata.cpp \
    exceptions/notacenterpicker.cpp \
    commons/sparsepoint.cpp \
    distances/abstractdistance.cpp \
    debug/moc_clusteringview.cpp \
    clustering.cpp \
    moc_clusteringview.cpp \
    simpdist.cpp \
    test.cpp \
    commons/abstractpoint.cpp \
    commons/densepoint.cpp \
    exceptions/notsparsepoint.cpp \
    distances/cosinedistance.cpp \
    commons/utils.cpp \
    exceptions/notimplemented.cpp \
    commons/centersdata.cpp \
    algorithms/abstractalgorithm.cpp \
    algorithms/kmeansalgorithm.cpp

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
    tfidf/stemmedfileinmemoryparser.h \
    commons/abstractcenterspicker.h \
    commons/sequentialcenterspicker.h \
    triangle/abstractaccountingcontainer.h \
    triangle/upperbounds.h \
    main.hpp \
    exceptions/badindex.h \
    commons/randomcenterpicker.h \
    commons/partitiondata.h \
    exceptions/notacenterpicker.h \
    commons/sparsepoint.h \
    distances/abstractdistance.h \
    ui_clusteringview.h \
    pickers/abstractcenterspicker.h \
    pickers/randomcenterpicker.h \
    pickers/sequentialcenterspicker.h \
    commons/abstractpoint.h \
    commons/densepoint.h \
    exceptions/notsparsepoint.h \
    distances/cosinedistance.h \
    commons/utils.h \
    exceptions/notimplemented.h \
    commons/centersdata.h \
    algorithms/abstractalgorithm.h \
    algorithms/kmeansalgorithm.h

FORMS += \
    ui/clusteringview.ui
