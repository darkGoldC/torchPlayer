#ifndef ITPCOREFRAMEWORK_H
#define ITPCOREFRAMEWORK_H

#include "TPInterfacePtr.h"
#include "ITPVideoWidget.h"

class ITPCoreFramework
{
public:
    virtual void    initWork() = 0;
    virtual QObject *getObject() = 0;
    virtual void    startWork() = 0;
    virtual void    stopWork() = 0;
    virtual void    pauseWork() = 0;
    virtual double  getProcess() = 0;
    virtual void    seekProcess(const double nValue) = 0;
    virtual bool    openVideo(const QString strUrl, ITPVideoWidget *pWidget) = 0;
};

TP_DECLARE_OBJ(ITPCoreFramework, "org.torchPlayer.ITPCoreFramework")
#endif
