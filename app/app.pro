include (../defaults.pri)

QT += gui
QT += widgets

CONFIG += app_bundle

HEADERS += main.hpp \
    mainwindow.h \
    dialogs/stemmedfileprocessingdialog.h
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogs/stemmedfileprocessingdialog.cpp

LIBS += -L../dev -lclustering

FORMS += \
    mainwindow.ui \
    dialogs/stemmedfileprocessingdialog.ui
