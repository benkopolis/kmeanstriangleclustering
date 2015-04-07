 include(../defaults.pri)

CONFIG   -= app_bundle
LIBS += -lunittest++ -L../dev -lclustering

TARGET = test
TEMPLATE = app

HEADERS += \
    algorithms/kmeansalgorithmut.h \
    commons/centersdataut.h \
    commons/densepointut.h \
    commons/partitiondataut.h \
    commons/sparsepointut.h \
    commons/utilsut.h \
    distances/cosinedistanceut.h \
    distances/euclideandistanceut.h \
    distances/hamiltondistanceut.h \
    pickers/randomcenterpickerut.h \
    pickers/sequentialcenterspickerut.h \
    readers/readersut.h

SOURCES += \
    algorithms/kmeansalgorithmut.cpp \
    commons/centersdataut.cpp \
    commons/densepointut.cpp \
    commons/partitiondataut.cpp \
    commons/sparsepointut.cpp \
    commons/utilsut.cpp \
    distances/cosinedistanceut.cpp \
    distances/euclideandistanceut.cpp \
    distances/hamiltondistanceut.cpp \
    pickers/randomcenterpickerut.cpp \
    pickers/sequentialcenterspickerut.cpp \
    readers/readersut.cpp \
    main.cpp
