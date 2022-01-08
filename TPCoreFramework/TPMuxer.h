#ifndef TPMUXER_H
#define TPMUXER_H

#include <QObject>
#include "TP_CoreDefine.h"

class TPCORESHARED_EXPORT TPMuxer : public QObject
{
    Q_OBJECT
public:
    explicit TPMuxer(QObject *parent = nullptr);

signals:

};

#endif // TPMUXER_H
