#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef ITPOBJECTMGR_H
#define ITPOBJECTMGR_H

#define OBJDEFAULT -9999

#include <QObject>
#include <QVector>

using TPObjKey     = std::tuple<QString, int>;


class ITPInterfaceMgr
{
public:
    virtual QObject* getObject(const QString& strName, const int& nIndex = OBJDEFAULT) = 0;
    virtual QObject* getObject(const TPObjKey& key) = 0;
    virtual void     addObject(const TPObjKey& key, const QObject* obj, const bool& bUsed = true) = 0;

    virtual QVector<int> getObjectsIndex(const QString& strName) = 0;
};

#endif // IRZTOBJECTMGR_H
