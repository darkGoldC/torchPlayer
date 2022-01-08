QT       += widgets xml gui network multimedia multimediawidgets concurrent sql opengl openglextensions

TEMPLATE = lib
TARGET = TPUI

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPUISHARED_LIBRARY

INCLUDEPATH += $$PWD/../Interface \
                $$PWD/../ThirdInclude

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPUI")
        }
        else{
            message("R*****TP***** win32 version-TPUI")
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
        message("D*****TP***** linux version-TPUI")
    }
    else{
        message("R*****TP***** linux version-TPUI")
    }
    PlatformFolder = Linux
}
DESTDIR = $$PWD/../bin/$$PlatformFolder

HEADERS += \
    TPParentWindowWidget.h \
    TPPlayWidget.h \
    TPTopFrameWidget.h

SOURCES += \
    TPParentWindowWidget.cpp \
    TPPlayWidget.cpp \
    TPTopFrameWidget.cpp

LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib
LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase -lTPFramework
