include (../defaults.pri)

QT += core
QT += gui
QT += widgets

CONFIG += app_bundle

HEADERS += main.hpp \
    mainwindow.h \
    dialogs/stemmedfileprocessingdialog.h \
    controllers/stemmedfileparsercontroller.h
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogs/stemmedfileprocessingdialog.cpp \
    controllers/stemmedfileparsercontroller.cpp

LIBS += -L../dev -lclustering

FORMS += \
    mainwindow.ui \
    dialogs/stemmedfileprocessingdialog.ui
