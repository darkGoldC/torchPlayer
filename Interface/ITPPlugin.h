#ifndef ITPPlugin_H
#define ITPPlugin_H
#include <iostream>
#include "TPInterfacePtr.h"

enum Plugin_Type
{
    PPlugin_Type_Demux,
    PPlugin_Type_decode,
    PPlugin_Type_output,
    PPlugin_Type_unkonw,
};

class ITPPlugin
{
public:
    //ITPPlugin(void *pHandle):nLibHandle(pHandle){}

    virtual bool            load() = 0;
    virtual bool            unload() = 0;

    std::string strPluginName;
    Plugin_Type pluginType = PPlugin_Type_unkonw;
    int         nScoreProperty = 0;
    void        *nLibHandle = nullptr;
    void        *loadFunc = nullptr;
};

typedef std::map<std::string, ITPPlugin *> plugin_map;

class TPSingleton
{

public:

    template<class T>
    static T& instance()
    {
        static T m_instance;
        return m_instance;
    }
};

void insertClassName(std::string strName, ITPPlugin *pPlugin)
{
    TPSingleton::instance<plugin_map>().insert(std::make_pair(strName, pPlugin));
}

#define LOAD_PLUGIN(ClassName)   \
    bool            load() override \
    {\
        return true;\
    }

#define UNLOAD_PLUGIN(ClassName)\
    bool    unload() override\
    {\
        return true;\
    }

#define REGISTER(ClassName) \
    class Register##ClassName \
    { \
    public: \
        static ITPPlugin* instance() \
        { \
            return new ClassName; \
        } \
    private: \
    }; \
    LOAD_PLUGIN(ClassName)\
    UNLOAD_PLUGIN(ClassName)

#endif
