QT       += widgets xml gui network multimedia multimediawidgets concurrent sql opengl openglextensions

TEMPLATE = lib
TARGET = TPFramework

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPCORESHARED_LIBRARY

DEFINES += QT_DLL QT_OPENGL_LIB QT_OPENGLEXTENSIONS_LIB QT_WIDGETS_LIB QT_MULTIMEDIA_LIB

INCLUDEPATH += $$PWD/../Interface \
                $$PWD/../ThirdInclude

win32:{
       CONFIG(debug, debug|release){
        message("D*****TP***** win32 version-TPFramework")
        }
        else{
            message("R*****TP***** win32 version-TPFramework")
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
        message("D*****TP***** linux version-TPFramework")
    }
    else{
        message("R*****TP***** linux version-TPFramework")
    }
    PlatformFolder = Linux
}
DESTDIR = $$PWD/../bin/$$PlatformFolder

LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase -lopengl32 \
    -lglu32

LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib -lavformat -lavutil -lavcodec -lswresample

HEADERS += \
    TPAudioDevice.h \
    TPAudioThread.h \
    TPComDecodeThread.h \
    TPCoreFramework.h \
    TPDecoder.h \
    TPDemuxThread.h \
    TPDemuxer.h \
    TPMuxer.h \
    TPResampler.h \
    TPVideoThread.h \
    TPVideoWidget.h

SOURCES += \
    TPAudioDevice.cpp \
    TPAudioThread.cpp \
    TPComDecodeThread.cpp \
    TPCoreFramework.cpp \
    TPDecoder.cpp \
    TPDemuxThread.cpp \
    TPDemuxer.cpp \
    TPMuxer.cpp \
    TPResampler.cpp \
    TPVideoThread.cpp \
    TPVideoWidget.cpp
