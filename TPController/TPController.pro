QT       += widgets xml gui network multimedia multimediawidgets concurrent sql opengl openglextensions
CONFIG += c++17
TEMPLATE = lib
TARGET = TPController

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPCONTROLLERSHARED_LIBRARY

INCLUDEPATH += $$PWD/../Interface \
                $$PWD/../TPUI

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPController")
        }
        else{
            message("R*****TP***** win32 version-TPController")
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
LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib
LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase -lTPUI -lTPFramework

HEADERS += \
    TPMainController.h \
    TPPlayController.h \
    TPTopFrameController.h \
    TP_ControllerDefine.h \
    TP_ControllerDefine.h

SOURCES += \
    TPMainController.cpp \
    TPPlayController.cpp \
    TPTopFrameController.cpp
