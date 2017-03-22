include (../defaults.pri)

CONFIG += app_bundle

HEADERS += main.hpp \
    models/histogramsdrawingdata.h \
    models/histogramseriesdata.h \
    processors/silhouetteprocessor.h \
    processors/abstractprocessor.h \
    processors/randprocessor.h \
    processors/obsoleteclusteringprocessor.h \
    processors/obsoletetfidfprocessor.h \
    processors/variationofinformationprocessor.h
SOURCES += main.cpp \
    models/histogramsdrawingdata.cpp \
    models/histogramseriesdata.cpp \
    processors/silhouetteprocessor.cpp \
    processors/abstractprocessor.cpp \
    processors/randprocessor.cpp \
    processors/obsoleteclusteringprocessor.cpp \
    processors/obsoletetfidfprocessor.cpp \
    processors/variationofinformationprocessor.cpp

LIBS += -L../dev -lclustering
