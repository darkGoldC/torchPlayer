QT       += widgets xml gui network multimedia multimediawidgets concurrent sql opengl openglextensions

TEMPLATE = app
TARGET = TPMain

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../TPUtil \
                $$PWD/../TPBase \
                $$PWD/../Interface \
                $$PWD/../TPController \
                $$PWD/../TPCoreFramework


win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPMain")
        }
        else{
            message("R*****TP***** win32 version-TPMain")
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

SOURCES += \
    $$PWD/main.cpp \
    TPApplication.cpp

LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib
LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase -lTPFramework -lTPController

HEADERS += \
    TPApplication.h
