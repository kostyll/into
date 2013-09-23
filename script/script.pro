TEMPLATE = lib
TARGET = piiscript
CONFIG += plugin
QT += script
HEADERS = *.h
SOURCES = *.cc

INTODIR = ..
include($$INTODIR/base.pri)
include($$INTODIR/libinstall.pri)
DEFINES += PII_BUILD_SCRIPT
LIBS += -lpiicore$$LIBVER -lpiiydin$$LIBVER
