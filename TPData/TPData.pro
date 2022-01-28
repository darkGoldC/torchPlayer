QT       += widgets xml gui network multimedia multimediawidgets concurrent sql
CONFIG += c++17

TEMPLATE = lib
TARGET = TPData

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPDATASHARED_LIBRARY

INCLUDEPATH += $$PWD/../Interface \

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPData")
        }
        else{
            message("R*****TP***** win32 version-TPData")
        }
        PlatformFolder = Win32
        QMAKE_LFLAGS_RELEASE += /MAP
        QMAKE_CFLAGS_RELEASE += /Zi
        QMAKE_LFLAGS_RELEASE += /debug /opt:ref
 }

unix:!macx:{
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -std=c++14
    CONFIG(debug, debug|release){
        message("D*****TP***** linux version-TPBase")
    }
    else{
        message("R*****TP***** linux version-TPBase")
    }
    PlatformFolder = Linux
}
DESTDIR = $$PWD/../bin/$$PlatformFolder

LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase

HEADERS += \
    TPDataMain.h \
    TPPlaylistMgr.h \
    TPValueMgr.h

SOURCES += \
    TPDataMain.cpp \
    TPPlaylistMgr.cpp \
    TPValueMgr.cpp
