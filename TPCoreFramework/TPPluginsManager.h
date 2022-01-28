#ifndef TPPLUGINSMANAGER_H
#define TPPLUGINSMANAGER_H
#include "ITPPlugin.h"
#include "ITPPluginsManager.h"
#include <list>
#include <map>
#include <QObject>
#include "TP_CoreDefine.h"

//可以通过宏命令控制new出类，然后将类实例放到工厂类的静态成员变量map中，之后遍历动态库后，从map中取出对应的实例

class TPCORESHARED_EXPORT TPPluginsManager : public QObject, public ITPPluginsManager
{
    Q_OBJECT
public:
    TPPluginsManager();

    ITPPlugin   *getInstance(const std::string strType) override;
    QObject     *getObject() override;
    bool        loadAllPlugins(const std::string strLibPath) override;
    void        listFiles(std::list<std::string> &list, const std::string &folder, const std::string &extension, bool recursive);

private:
    ITPPlugin *load(const std::string &path);
    void unLoad(ITPPlugin *pPlugin);
    void *getSymbol(ITPPlugin *pPlugin, const std::string &symbol);

private:

};

#endif // TPPLUGINSMANAGER_H
