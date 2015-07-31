include (../defaults.pri)

QT += core
QT += gui
QT += widgets

CONFIG += app_bundle

HEADERS += main.hpp \
    mainwindow.h \
    dialogs/stemmedfileprocessingdialog.h \
    controllers/stemmedfileparsercontroller.h \
    controllers/histogramcontroller.h \
    dialogs/histogramdialog.h \
    views/histogramsview.h \
    models/histogramsdrawingdata.h
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogs/stemmedfileprocessingdialog.cpp \
    controllers/stemmedfileparsercontroller.cpp \
    controllers/histogramcontroller.cpp \
    dialogs/histogramdialog.cpp \
    views/histogramsview.cpp \
    models/histogramsdrawingdata.cpp

LIBS += -L../dev -lclustering

FORMS += \
    mainwindow.ui \
    dialogs/stemmedfileprocessingdialog.ui \
    dialogs/histogramdialog.ui \
    views/histogramsview.ui
