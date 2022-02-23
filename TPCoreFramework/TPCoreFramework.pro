QT       += widgets xml gui network multimedia multimediawidgets concurrent sql opengl openglextensions
CONFIG += c++17
TEMPLATE = lib
TARGET = TPFramework

DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QT_DEPRECATED_WARNINGS TPCORESHARED_LIBRARY

DEFINES += QT_DLL QT_OPENGL_LIB QT_OPENGLEXTENSIONS_LIB QT_WIDGETS_LIB QT_MULTIMEDIA_LIB

INCLUDEPATH += $$PWD/../Interface \
                $$PWD/../TPBase \
                $$PWD/../ThirdInclude/ffmpeg

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

        CONFIG(debug, debug){
            LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib/ffmpeg/Debug
        }
        else{
            LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib/ffmpeg/Release
        }
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


LIBS += -L$$PWD/../bin/$$PlatformFolder/ThirdLib/ffmpeg -lavformat -lavutil -lavcodec -lswresample

HEADERS += \
    TPAudioDevice.h \
    TPAudioOuput.h \
    TPCoreFramework.h \
    TPDecoder.h \
    TPDemuxer.h \
    TPEsOut.h \
    TPInputManager.h \
    TPMuxer.h \
    TPPluginsManager.h \
    TPResampler.h \
    TPVideoOutput.h \
    TPVideoWidget.h

SOURCES += \
    TPAudioDevice.cpp \
    TPAudioOuput.cpp \
    TPCoreFramework.cpp \
    TPDecoder.cpp \
    TPDemuxer.cpp \
    TPEsOut.cpp \
    TPInputManager.cpp \
    TPMuxer.cpp \
    TPPluginsManager.cpp \
    TPResampler.cpp \
    TPVideoOutput.cpp \
    TPVideoWidget.cpp
