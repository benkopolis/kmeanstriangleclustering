include (../defaults.pri)

QT += core
QT += gui
QT += widgets

CONFIG += app_bundle
CONFIG += qwt

HEADERS += main.hpp \
    mainwindow.h \
    dialogs/stemmedfileprocessingdialog.h \
    controllers/stemmedfileparsercontroller.h \
    controllers/histogramcontroller.h \
    dialogs/histogramdialog.h \
    views/histogramsview.h \
    models/histogramsdrawingdata.h \
    models/histogramseriesdata.h
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogs/stemmedfileprocessingdialog.cpp \
    controllers/stemmedfileparsercontroller.cpp \
    controllers/histogramcontroller.cpp \
    dialogs/histogramdialog.cpp \
    views/histogramsview.cpp \
    models/histogramsdrawingdata.cpp \
    models/histogramseriesdata.cpp

LIBS += -L../dev -lclustering -L/usr/local/qwt-6.1.3-svn/lib -lqwt
QMAKE_CXXFLAGS += -I/usr/local/qwt-6.1.3-svn/include

FORMS += \
    mainwindow.ui \
    dialogs/stemmedfileprocessingdialog.ui \
    dialogs/histogramdialog.ui \
    views/histogramsview.ui
