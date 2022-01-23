TEMPLATE = subdirs

DEFINES += NOMINMAX

SUBDIRS += \
        TPBase \
        TPNet \
        TPCoreFramework \
        TPData \
        TPUI \
        TPController \
        TPMain \
        TPPlugins


CONFIG += ordered C++11
