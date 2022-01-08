#ifndef TPMAINCONTROLLER_H
#define TPMAINCONTROLLER_H

#include <QObject>
#include "TP_ControllerDefine.h"

class TPCONTROLLERSHARED_EXPORT TPMainController : public QObject
{
    Q_OBJECT
public:
    explicit TPMainController(QObject *parent = nullptr);

    void    install();
};

#endif // TPMAINCONTROLLER_H
