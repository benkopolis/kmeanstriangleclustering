 include(../defaults.pri)

CONFIG   -= app_bundle
LIBS += -L /usr/local/lib/ -lUnitTest++ -L$$OUT_PWD/../dev -lclustering

TARGET = test
TEMPLATE = app

HEADERS += \
    algorithms/kmeansalgorithmut.h \
    commons/centersdataut.h \
    commons/densepointut.h \
    commons/partitiondataut.h \
    commons/sparsepointut.h \
    distances/cosinedistanceut.h \
    distances/euclideandistanceut.h \
    distances/hamiltondistanceut.h \
    pickers/randomcenterpickerut.h \
    pickers/sequentialcenterspickerut.h \
    readers/readersut.h

SOURCES += \
    algorithms/kmeansalgorithmut.cpp \
    commons/centersdataut.cpp \
    commons/partitiondataut.cpp \
    distances/cosinedistanceut.cpp \
    distances/euclideandistanceut.cpp \
    distances/hamiltondistanceut.cpp \
    pickers/randomcenterpickerut.cpp \
    pickers/sequentialcenterspickerut.cpp \
    readers/readersut.cpp \
    main.cpp
