#ifndef TPGlobalInfoMgr_H
#define TPGlobalInfoMgr_H

#include <QObject>
#include "TPObjectMgr.h"
#include "TP_BaseDefine.h"

class TPBASESHARED_EXPORT TPGlobalInfoMgr : public QObject
{
    Q_OBJECT
public:
    explicit TPGlobalInfoMgr(QObject *parent = nullptr);
    static          TPGlobalInfoMgr *getInstance();
    void            initPath();

    QString         getLongPath();
    static TPInterfaceMgr    *getObjectMgr();
signals:

private:
    QString         m_strLogPath;

};

#endif // TPPATHMGR_H
