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


SOURCES += src/dev/main.cpp \
    src/dev/KMeans.cpp \
    src/dev/kmeanstriangle.cpp \
    src/dev/ui/clusteringview.cpp \
    src/dev/readers/abstractdatareader.cpp \
    src/dev/spaces/abstractpointsspace.cpp \
    src/dev/spaces/pointsspace.cpp \
    src/dev/spaces/normalizedpointsspace.cpp \
    src/dev/tfidf/stemmedfileinmemoryparser.cpp \
    src/dev/pickers/abstractcenterspicker.cpp \
    src/dev/pickers/sequentialcenterspicker.cpp \
    src/dev/pickers/randomcenterpicker.cpp \
    src/dev/triangle/abstractaccountingcontainer.cpp \
    src/dev/triangle/upperbounds.cpp \
    src/dev/exceptions/badindex.cpp \
    src/dev/commons/partitiondata.cpp \
    src/dev/exceptions/notacenterpicker.cpp \
    src/dev/commons/sparsepoint.cpp \
    src/dev/distances/abstractdistance.cpp \
    src/dev/debug/moc_clusteringview.cpp \
    src/dev/clustering.cpp \
    src/dev/moc_clusteringview.cpp \
    src/dev/simpdist.cpp \
    src/dev/test.cpp \
    src/dev/commons/abstractpoint.cpp \
    src/dev/commons/densepoint.cpp \
    src/dev/exceptions/notsparsepoint.cpp \
    src/dev/distances/cosinedistance.cpp \
    src/dev/commons/utils.cpp \
    src/dev/exceptions/notimplemented.cpp \
    src/dev/commons/centersdata.cpp \
    src/dev/algorithms/abstractalgorithm.cpp \
    src/dev/algorithms/kmeansalgorithm.cpp \
    src/dev/distances/hamiltondistance.cpp \
    src/dev/distances/euclideandistance.cpp \
    src/dev/readers/fulldatareader.cpp \
    src/dev/readers/normalizedformatdatareader.cpp \

HEADERS += \
    src/dev/models.hpp \
    src/dev/KMeans.hpp \
    src/dev/kmeanstriangle.hpp \
    src/dev/ui/clusteringview.h \
    src/dev/readers/abstractdatareader.h \
    src/dev/spaces/abstractpointsspace.h \
    src/dev/spaces/pointsspace.h \
    src/dev/spaces/normalizedpointsspace.h \
    src/dev/tfidf/stemmedfileinmemoryparser.h \
    src/dev/commons/abstractcenterspicker.h \
    src/dev/commons/sequentialcenterspicker.h \
    src/dev/triangle/abstractaccountingcontainer.h \
    src/dev/triangle/upperbounds.h \
    src/dev/main.hpp \
    src/dev/exceptions/badindex.h \
    src/dev/commons/randomcenterpicker.h \
    src/dev/commons/partitiondata.h \
    src/dev/exceptions/notacenterpicker.h \
    src/dev/commons/sparsepoint.h \
    src/dev/distances/abstractdistance.h \
    src/dev/ui_clusteringview.h \
    src/dev/pickers/abstractcenterspicker.h \
    src/dev/pickers/randomcenterpicker.h \
    src/dev/pickers/sequentialcenterspicker.h \
    src/dev/commons/abstractpoint.h \
    src/dev/commons/densepoint.h \
    src/dev/exceptions/notsparsepoint.h \
    src/dev/distances/cosinedistance.h \
    src/dev/commons/utils.h \
    src/dev/exceptions/notimplemented.h \
    src/dev/commons/centersdata.h \
    src/dev/algorithms/abstractalgorithm.h \
    src/dev/algorithms/kmeansalgorithm.h \
    src/dev/distances/hamiltondistance.h \
    src/dev/distances/euclideandistance.h \
    src/dev/readers/fulldatareader.h \
    src/dev/readers/normalizedformatdatareader.h \

FORMS += \
    src/dev/ui/clusteringview.ui
