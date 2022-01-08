#ifndef ITPTopFrameController_H
#define ITPTopFrameController_H

#include "TPInterfacePtr.h"

class ITPTopFrameController
{
public:
    virtual QObject *getObject() = 0;
    virtual void    initController() = 0;
    virtual QWidget  *getTopWidget() = 0;
};

TP_DECLARE_OBJ(ITPTopFrameController, "org.torchPlayer.ITPTopFrameController")
#endif
