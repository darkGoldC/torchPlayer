#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include "TPEventNotifyMgr.h"
#include <QObject>
#include <QMetaObject>

TPEventNotifyMgr::TPEventNotifyMgr()
{
    m_eventThread = new QThread;
    this->moveToThread(m_eventThread);
    m_eventThread->start();
}

TPEventNotifyMgr::~TPEventNotifyMgr()
{
    m_eventThread->quit();
    m_eventThread->deleteLater();
}

void TPEventNotifyMgr::sltEventProcess(TPBaseEvent *event)
{
//    qRztDebug() << "eventProcess";
    QMetaObject::invokeMethod(event, "sltFunc", Qt::QueuedConnection);
}


TPEventNotifyMgr *TPEventNotifyMgr::getInstance()
{
    static TPEventNotifyMgr eventNotifyMgr;
    return &eventNotifyMgr;
}

void TPEventNotifyMgr::addEventNotify(TPBaseEvent *event)
{
    //为什么不直接invokeEvent, 原因是不想阻塞代码 ，因为mgr独立线程
//    qRztDebug() << "addEventNotify";
    QMetaObject::invokeMethod(this, "sltEventProcess",
                              Q_ARG(TPBaseEvent *, event));
}


