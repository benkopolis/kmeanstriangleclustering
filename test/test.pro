 include(../defaults.pri)

CONFIG   -= app_bundle
LIBS += -L /usr/local/lib/ -lUnitTest++ -L$$OUT_PWD/../dev -lclustering

TARGET = test
TEMPLATE = app

HEADERS += \
    readers/readersut.h \
    commons/testpoint.h

SOURCES += \
    algorithms/kmeansalgorithmut.cpp \
    commons/centersdataut.cpp \
    commons/partitiondataut.cpp \
    distances/cosinedistanceut.cpp \
    distances/euclideandistanceut.cpp \
    distances/hamiltondistanceut.cpp \
    readers/readersut.cpp \
    main.cpp \
    commons/densepointut.cpp \
    commons/sparsepointut.cpp \
    pickers/randomcenterspickerut.cpp \
    pickers/sequentialcenterspickerut.cpp \
    commons/testpoint.cpp \
    distances/manhattandistanceut.cpp \
    pickers/dimensionbasedcenterspicker.cpp \
    tfidf/stemmedinmemoryfileparserut.cpp \
    commons/hashtableut.cpp
