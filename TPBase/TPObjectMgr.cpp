#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include "TPObjectMgr.h"
#include <QDebug>

TPInterfaceMgr::TPInterfaceMgr():
    m_lockerRW(QReadWriteLock::Recursive)
{
}

QObject *TPInterfaceMgr::getObject(const QString& strName, const int& nIndex)
{
    return getObject(TPObjKey(strName, nIndex));
}

QObject *TPInterfaceMgr::getObject(const TPObjKey &key)
{
    QWriteLocker locker(&m_lockerRW);
    QString strName;
    int nIndex = -1;
    std::tie(strName, nIndex) = key;
    // qTPDebug() << strName << nIndex;

    if (!m_mapData.contains(key))
    {
        // qTPDebug() << "code err 1" << strName << nIndex;
        return nullptr;
    }

    QObject *testObject = m_mapData.value(key).obj;
    return m_mapData.value(key).obj;

}

void TPInterfaceMgr::addObject(const TPObjKey &key, const QObject *obj, const bool& bUsed)
{
    QWriteLocker locker(&m_lockerRW);

    QString strName;
    int nIndex = -1;
    std::tie(strName, nIndex) = key;
    //qTPDebug() << strName << nIndex;

    if (strName.isEmpty())
    {
        qFatal("obj name: error");
    }

    if (m_mapData.find(key) != m_mapData.end())
    {
        qFatal("add obj too much");
    }

    //    qTPInfo() << "obj name:" << strName << nIndex;

    STObjectWrapper objWrapper;
    objWrapper.obj = const_cast<QObject*>(obj);
    objWrapper.bUsed = bUsed;
    objWrapper.nIndex = nIndex;
    objWrapper.strName = strName;
    m_mapData[key] = objWrapper;
}

QVector<int> TPInterfaceMgr::getObjectsIndex(const QString &strName)
{
    QWriteLocker locker(&m_lockerRW);
    QVector<int> vecRet;

    for (auto iter = m_mapData.begin(); iter != m_mapData.end(); iter++)
    {
        if (std::get<0>(iter.key()) == strName)
        {
            vecRet.push_back(std::get<1>(iter.key()));
        }
    }

    return vecRet;
}

int TPInterfaceMgr::mallocObject(const QString &strName)
{
    QWriteLocker locker(&m_lockerRW);
    int nRet = INVALID_ID;
    for (auto iter = m_mapData.begin(); iter != m_mapData.end(); iter++)
    {
        if (std::get<0>(iter.key()) == strName && !iter.value().bUsed)
        {
            nRet = std::get<1>(iter.key());
            iter.value().bUsed = true;
            break;
        }
    }

    if (nRet == INVALID_ID)
    {
        qTPDebug() << "code err 1";
    }
    return nRet;
}

