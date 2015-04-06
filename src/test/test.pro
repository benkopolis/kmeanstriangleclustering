 include(../../defaults.pri)

CONFIG   -= app_bundle
LIBS += -lunittest++ -L../src -lclustering

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
    algorithms/moc_kmeansalgorithmut.cpp \
    commons/centersdataut.cpp \
    commons/densepointut.cpp \
    commons/moc_centersdataut.cpp \
    commons/moc_densepointut.cpp \
    commons/moc_partitiondataut.cpp \
    commons/moc_sparsepointut.cpp \
    commons/partitiondataut.cpp \
    commons/sparsepointut.cpp \
    commons/utilsut.cpp \
    distances/cosinedistanceut.cpp \
    distances/euclideandistanceut.cpp \
    distances/hamiltondistanceut.cpp \
    distances/moc_cosinedistanceut.cpp \
    distances/moc_euclideandistanceut.cpp \
    distances/moc_hamiltondistanceut.cpp \
    pickers/moc_randomcenterpickerut.cpp \
    pickers/moc_sequentialcenterspickerut.cpp \
    pickers/randomcenterpickerut.cpp \
    pickers/sequentialcenterspickerut.cpp \
    readers/moc_fulldatareaderut.cpp \
    readers/moc_normalizedformatdatareaderut.cpp \
    readers/readersut.cpp \
    main.cpp
