INTODIR = ../../
include($$INTODIR/base.pri)

qt5: QT += widgets
FORMS += ui/*.ui
RESOURCES += resources.qrc

HEADERS   = *.h
SOURCES   = *.cc
LIBS += -lpiiydin$$LIBVER -lpiicore$$LIBVER

TARGET = $$PRO_FILE_BASENAME
defined(DEMO_INSTALL_PATH, var): {
  target.path = $$DEMO_INSTALL_PATH
  INSTALLS += target
}
