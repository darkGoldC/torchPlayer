#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TPOBJECTMGR_H
#define TPOBJECTMGR_H

#include "ITPObjectMgr.h"
#include <QString>
#include <QMap>
#include <QHash>
#include <QReadWriteLock>
#include "TP_BaseDefine.h"
#include "TPCommonDefine.h"

class TPBASESHARED_EXPORT TPInterfaceMgr : public QObject, public ITPInterfaceMgr
{
    Q_OBJECT

    typedef struct _ObjectWrapper
    {
        QString     strName;
        int         nIndex = -1;
        QObject*    obj = nullptr;
        bool        bUsed = true;//使用中
    }STObjectWrapper;

public:
    TPInterfaceMgr();

    QObject* getObject(const QString& strName, const int& nIndex = OBJDEFAULT) override;
    QObject* getObject(const TPObjKey& key) override;

    void            addObject(const TPObjKey& key, const QObject* obj, const bool& bUsed = true) override;
    QVector<int>    getObjectsIndex(const QString& strName) override;
    int             mallocObject(const QString& strName);//获取一个对象，同时标记为使用

private:
    QMap<TPObjKey, STObjectWrapper> m_mapData;//所有对象
    QReadWriteLock                   m_lockerRW;
};

#endif // ALLOBJMGR_H
