#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef RztEventNotifyMgr_H
#define RztEventNotifyMgr_H

#include <iostream>
#include <mutex>
#include <QThread>
#include "TP_BaseDefine.h"
#include "TPBaseEvent.h"

class TPBASESHARED_EXPORT TPEventNotifyMgr : public QObject
{
    Q_OBJECT
public:

    ~TPEventNotifyMgr() override;

private:
    TPEventNotifyMgr();

public:
    static TPEventNotifyMgr *getInstance();

    void    addEventNotify(TPBaseEvent *event);
private slots:
    void    sltEventProcess(TPBaseEvent *event);

private:
    //std::mutex                                      m_lockObserver;
    QThread                                         *m_eventThread;               
};

#endif
