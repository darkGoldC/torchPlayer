#ifndef ITPPLAYCONTROLLER_H
#define ITPPLAYCONTROLLER_H

#include <QWidget>
#include "TPInterfacePtr.h"

class ITPPlayController
{
public:
    virtual QObject *getObject() = 0;
    virtual void    initController() =0;
    virtual QWidget *getWidget() = 0;
};

TP_DECLARE_OBJ(ITPPlayController, "org.torchPlayer.ITPPlayController")
#endif
