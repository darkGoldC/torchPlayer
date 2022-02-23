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

#define DECLARE_CLASS(ClassName)\
static TPRegisterPlugin* ClassName::m_className##dc;


#define IMPLEMENT_CLASS(ClassName)  \
TPRegisterPlugin* ClassName::m_className##dc = \
new TPRegisterPlugin(#ClassName, ClassName::instance) ;

class ITPPlugin;

typedef std::map<std::string, ITPPlugin *> plugin_map;
typedef std::function<ITPPlugin * ()>             createFunc;

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

class TPRegisterPlugin
{
public:
    TPRegisterPlugin(const std::string &strName, createFunc func)
    {
        TPSingleton::instance<plugin_map>().insert(std::make_pair(strName, func()));
    }
};


#define REGISTER(ClassName) \
    static ITPPlugin* instance() \
    { \
        return new ClassName; \
    } \


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

#endif
