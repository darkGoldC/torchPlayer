TEMPLATE = subdirs

DEFINES += NOMINMAX

SUBDIRS += \
        TPBase \
        TPNet \
        TPCoreFramework \
        TPData \
        TPUI \
        TPController \
        TPPlugins \
        TPMain \



CONFIG += c++17
CONFIG += ordered



CONFIG += ordered C++11

HEADERS += \
    Interface/TPUIData.h
