QT       += widgets xml gui network multimedia multimediawidgets concurrent sql

TEMPLATE = lib
TARGET = TPBase

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPBASESHARED_LIBRARY

INCLUDEPATH +=   $$PWD/../Interface \
                $$PWD/

HEADERS += \
    ../Interface/BlockDataQueue.h \
    ../Interface/TPCommonDefine.h \
    ../Interface/TPCommonUtils.h \
    ../Interface/TPGlobalInfoMgr.h \
    ../Interface/TPInterfacePtr.h \
    ../Interface/TPLog.h \
    ../Interface/TPNanoLog.h \
    ../Interface/TPObjectMgr.h \
    ../Interface/TP_ControllerDefine.h \
    ../Interface/BlockData.h    \
    ../Interface/TPInputClock.h

SOURCES += \
    BlockData.cpp \
    BlockDataQueue.cpp \
    TPCommonUtils.cpp \
    TPGlobalInfoMgr.cpp \
    TPLog.cpp \
    TPNanoLog.cpp \
    TPObjectMgr.cpp \
    TPInputClock.cpp

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPBase")
        }
        else{
            message("R*****TP***** win32 version-TPBase")
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
