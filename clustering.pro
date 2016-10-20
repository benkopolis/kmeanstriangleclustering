#-------------------------------------------------
#
# Project created by QtCreator 2012-12-14T05:34:49
#
#-------------------------------------------------

include(defaults.pri)

CONFIG += ordered

TARGET = all

TEMPLATE = subdirs

SUBDIRS = \
    dev \
    test \
    app

app.depends = dev
test.depends = dev
