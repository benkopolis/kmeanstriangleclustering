#-------------------------------------------------
#
# Project created by QtCreator 2012-12-14T05:34:49
#
#-------------------------------------------------

include(defaults.pri)

QT       += gui

CONFIG += ordered

TARGET = all

TEMPLATE = subdirs

SUBDIRS = \
    src/app \
    src/dev \
    src/test

src/app.DEPENDPATH = src/dev
src/test.DEPENDPATH = src/dev
