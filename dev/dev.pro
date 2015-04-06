include(../defaults.pri)

TARGET = clustering
TEMPLATE = lib

SOURCES += \
    algorithms/abstractalgorithm.cpp \
    algorithms/kmeansalgorithm.cpp \
    commons/abstractpoint.cpp \
    commons/centersdata.cpp \
    commons/densepoint.cpp \
    commons/partitiondata.cpp \
    commons/sparsepoint.cpp \
    commons/utils.cpp \
    distances/abstractdistance.cpp \
    distances/cosinedistance.cpp \
    distances/euclideandistance.cpp \
    distances/hamiltondistance.cpp \
    exceptions/badindex.cpp \
    exceptions/invalidfileformat.cpp \
    exceptions/notacenterpicker.cpp \
    exceptions/notimplemented.cpp \
    exceptions/notsparsepoint.cpp \
    pickers/abstractcenterspicker.cpp \
    pickers/randomcenterpicker.cpp \
    pickers/sequentialcenterspicker.cpp \
    readers/abstractdatareader.cpp \
    readers/fulldatareader.cpp \
    readers/normalizedformatdatareader.cpp \
    spaces/abstractpointsspace.cpp \
    spaces/normalizedpointsspace.cpp \
    spaces/pointsspace.cpp \
    tfidf/stemmedfileinmemoryparser.cpp \
    triangle/abstractaccountingcontainer.cpp \
    triangle/upperbounds.cpp \
    exceptions/notdensepoint.cpp
HEADERS += \
    algorithms/abstractalgorithm.h \
    algorithms/kmeansalgorithm.h \
    commons/abstractpoint.h \
    commons/centersdata.h \
    commons/densepoint.h \
    commons/partitiondata.h \
    commons/sparsepoint.h \
    commons/utils.h \
    distances/abstractdistance.h \
    distances/cosinedistance.h \
    distances/euclideandistance.h \
    distances/hamiltondistance.h \
    exceptions/badindex.h \
    exceptions/invalidfileformat.h \
    exceptions/notacenterpicker.h \
    exceptions/notimplemented.h \
    exceptions/notsparsepoint.h \
    pickers/abstractcenterspicker.h \
    pickers/randomcenterpicker.h \
    pickers/sequentialcenterspicker.h \
    readers/abstractdatareader.h \
    readers/fulldatareader.h \
    readers/normalizedformatdatareader.h \
    spaces/abstractpointsspace.h \
    spaces/normalizedpointsspace.h \
    spaces/pointsspace.h \
    tfidf/stemmedfileinmemoryparser.h \
    triangle/abstractaccountingcontainer.h \
    triangle/upperbounds.h \
    models.hpp \
    exceptions/notdensepoint.h

FORMS +=