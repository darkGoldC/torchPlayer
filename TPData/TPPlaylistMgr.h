#ifndef TPPLAYLISTMGR_H
#define TPPLAYLISTMGR_H

#include <QObject>
#include "TP_DataDefine.h"

class TPDATASHARED_EXPORT TPPlaylistMgr : public QObject
{
    Q_OBJECT
public:
    explicit TPPlaylistMgr(QObject *parent = nullptr);

signals:

};

#endif // TPPLAYLISTMGR_H
