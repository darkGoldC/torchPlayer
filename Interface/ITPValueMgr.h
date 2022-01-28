#ifndef ITPVALUEMGR_H
#define ITPVALUEMGR_H
#include "TPInterfacePtr.h"
#include <any>

class ITPValueMgr
{
public:
    virtual QObject *getObject() = 0;
};
TP_DECLARE_OBJ(ITPValueMgr, "org.torchPlayer.ITPValueMgr")

#endif
