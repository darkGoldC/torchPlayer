#ifndef ITPVALUEMGR_H
#define ITPVALUEMGR_H
#include "TPInterfacePtr.h"
#include <any>

class ITPValueMgr
{
public:
    virtual QObject     *getObject() = 0;
    virtual void        setValue(const std::string &strName, const std::any &value) = 0;
    virtual std::any    getValue(const std::string &strName) = 0;
};
TP_DECLARE_OBJ(ITPValueMgr, "org.torchPlayer.ITPValueMgr")

#endif
