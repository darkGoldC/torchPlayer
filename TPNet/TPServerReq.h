#ifndef TPSERVERREQ_H
#define TPSERVERREQ_H

#include <QObject>
#include "TP_NetDefine.h"

class TPNETSHARED_EXPORT TPServerReq : public QObject
{
    Q_OBJECT
public:
    explicit TPServerReq(QObject *parent = nullptr);

signals:

};

#endif // TPSERVERREQ_H
