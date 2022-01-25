TEMPLATE = lib
TARGET = TPDecode

INCLUDEPATH += $$PWD/../../TPCoreFramework \
                $$PWD/../../Interface

HEADERS += \
    TPFFmpegDecode.h

SOURCES += \
    TPFFmpegDecode.cpp

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPDecode")
        }
        else{
            message("R*****TP***** win32 version-TPDecode")
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
        message("D*****TP***** linux version-TPDecode")
    }
    else{
        message("R*****TP***** linux version-TPDecode")
    }
    PlatformFolder = Linux
}

LIBS += -L$$PWD/../../bin/$$PlatformFolder/ -lTPBase -lTPFramework
DESTDIR = $$PWD/../../bin/$$PlatformFolder
