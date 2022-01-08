QT       += widgets xml gui network multimedia multimediawidgets concurrent sql

TEMPLATE = lib
TARGET = TPNet

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPNETSHARED_LIBRARY

INCLUDEPATH += $$PWD/../Interface \

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPNet")
        }
        else{
            message("R*****TP***** win32 version-TPNet")
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
        message("D*****TP***** linux version-TPNet")
    }
    else{
        message("R*****TP***** linux version-TPNet")
    }
    PlatformFolder = Linux
}
DESTDIR = $$PWD/../bin/$$PlatformFolder

LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase

HEADERS += \
    TPServerReq.h

SOURCES += \
    TPServerReq.cpp
