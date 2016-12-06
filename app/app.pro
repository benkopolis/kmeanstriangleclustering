include (../defaults.pri)

CONFIG += app_bundle

HEADERS += main.hpp \
    models/histogramsdrawingdata.h \
    models/histogramseriesdata.h
SOURCES += main.cpp \
    models/histogramsdrawingdata.cpp \
    models/histogramseriesdata.cpp

LIBS += -L../dev -lclustering
