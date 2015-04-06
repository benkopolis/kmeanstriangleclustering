include (../defaults.pri)

QT += gui

CONFIG += app_bundle

HEADERS += main.hpp
SOURCES += main.cpp

LIBS += -L../dev -lclustering
