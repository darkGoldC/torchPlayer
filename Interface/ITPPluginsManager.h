#ifndef ITPPluginsManager_H
#define ITPPluginsManager_H
#include <iostream>
#include <memory>
#include "ITPPlugin.h"
#include "TPInterfacePtr.h"

class ITPPluginsManager
{
public:
    virtual bool        loadAllPlugins(const std::string strLibPath) = 0;
    virtual QObject     *getObject() = 0;
    virtual ITPPlugin   *getInstance(const std::string strType) = 0;
};
TP_DECLARE_OBJ(ITPPluginsManager, "org.torchPlayer.ITPPluginsManager")

#endif
