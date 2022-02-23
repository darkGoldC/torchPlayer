TEMPLATE = lib
TARGET = TPDemux
CONFIG += c++17
INCLUDEPATH += $$PWD/../../TPCoreFramework \
                $$PWD/../../Interface \
                $$PWD/../../ThirdInclude/ffmpeg
HEADERS += \
    TPFFmpegDemuxer.h

SOURCES += \
    TPFFmpegDemuxer.cpp

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPDemux")
        }
        else{
            message("R*****TP***** win32 version-TPDemux")
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
        message("D*****TP***** linux version-TPDemux")
    }
    else{
        message("R*****TP***** linux version-TPDemux")
    }
    PlatformFolder = Linux
}

LIBS += -L$$PWD/../../bin/$$PlatformFolder/ThirdLib/ffmpeg/Debug -lavformat -lavutil -lavcodec -lswresample

LIBS += -L$$PWD/../../bin/$$PlatformFolder/ -lTPBase -lTPFramework
DESTDIR = $$PWD/../../bin/$$PlatformFolder
