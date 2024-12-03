include($$(LIBRARIESINCLUDE)/qmake/LibraryFunctions.pri)

# configure
include(../Applications.config.pri)
QT -= gui
CONFIG += console
CONFIG -= app_bundle

# build
include(../Applications.build.pri)
SOURCES += Day1.cpp

# install
include(../Applications.install.pri)
