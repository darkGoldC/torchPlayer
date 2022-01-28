#ifndef ITPDataMain_H
#define ITPDataMain_H

#include "TPInterfacePtr.h"

class ITPDataMain
{
public:
    virtual QObject *getObject() = 0;
    virtual void    registerObject() = 0;;
};

#endif
