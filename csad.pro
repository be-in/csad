
LANGUAGE  = C++
CONFIG += ordered
CONFIG                      += build_all debug_and_release warn_on thread plugin
CONFIG                      -= flat qt

CONFIG( debug, debug|release ) {
    PROJECT_DIR              = debug
    OBJECTS_DIR              = debug/obj
} else {
    PROJECT_DIR              = release
    OBJECTS_DIR              = release/obj
}

QMAKE_LIBDIR_QT =
QMAKE_INCDIR_QT =
QMAKE_LIBFLAGS += -v
QMAKE_LIBS_QT_ENTRY -= -lqtmain
QMAKE_LIBDIR = $$PROJECT_DIR

TEMPLATE = lib
TARGET = csad

win32-msvc: {
QMAKE_LFLAGS = -Wl,-enable-stdcall-fixup
QMAKE_CXXFLAGS += -frtti
QMAKE_CXXFLAGS -= -fno-tti

LIBS += -lwsock32 -lgdi32
TARGET_EXT = .dll
}

win32-g++: {
QMAKE_LFLAGS = -Wl,-enable-stdcall-fixup
QMAKE_CXXFLAGS += -frtti
QMAKE_CXXFLAGS -= -fno-tti

LIBS += -lwsock32 -lgdi32
TARGET_EXT = .dll
}

linux-g++: {
QMAKE_CFLAGS += -mmmx -msse -msse2 -msse3 -msse4.1 -msse4.2 -m3dnow
QMAKE_CXXFLAGS += -mmmx -msse -msse2 -msse3 -msse4.1 -msse4.2 -m3dnow

LIBS += -lGL -lX11 -ldl -lpthread -lfreetype
TARGET_EXT = .so

INCLUDEPATH += /usr/include/freetype2
VPATH += /usr/include/freetype2
}

linux-e3s: {
QMAKE_CFLAGS += -mmmx -msse -msse2 -msse3
QMAKE_CXXFLAGS += -mmmx -msse -msse2 -msse3

LIBS += -lGL -lX11 -ldl -lpthread -lfreetype
TARGET_EXT = .so

INCLUDEPATH += /usr/include/freetype2
VPATH += /usr/include/freetype2
}

DESTDIR                     =   $${PROJECT_DIR}

DEFINES = LIB_CSAD LIB_BT LOG_CSAD SOFT_RENDER_CSAD JPEG_CSAD TGA_CSAD _3DS_CSAD PAK_CSAD

INCLUDEPATH += . ./csad/include
VPATH += . ./csad/include

QT -= core gui

include(csad/rtl.pri)
include(csad/bt.pri)
include(csad/csad.pri)

