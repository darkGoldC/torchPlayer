TEMPLATE = subdirs


DEFINES += NOMINMAX

SUBDIRS += \
        Demux \
        Decode \
        videoOuput \

DESTDIR = $$PWD/../bin/$$PlatformFolder

CONFIG += ordered

LIBS += -L$$PWD/../bin/$$PlatformFolder/ -lTPBase -lTPFramework
