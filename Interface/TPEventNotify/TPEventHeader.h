#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#ifndef RZTMETAOBJECT_H
#define RZTMETAOBJECT_H

#include<functional>
#include<memory>
#include<QVector>
#include<mutex>
#include<assert.h>
#include<iostream>
#include <QObject>
#include <atomic>
#include "TPBaseEvent.h"
#include "TPEventNotifyMgr.h"

#define TPEventBindWithNone(EVENT, TPPTR, funcAddr)   \
{ \
    if(TPPTR) \
    { \
        EVENT.connect(TPPTR, \
        std::bind(funcAddr, TPPTR)); \
    } \
}


#define TPEventBindWithOne_Index(EVENT, ITPInterface, index, desc)   \
{ \
    ObjectPtr<ITPInterface> iTP(index); \
    if(iTP) \
    { \
        EVENT.connect(iTP->getObject(), \
        std::bind(& ITPInterface::desc, dynamic_cast<ITPInterface *>(iTP->getObject()), std::placeholders::_1)); \
    } \
}

//多个接口
#define TPEventBindWithOne2(EVENT, ITPInterface, ITPInterface2, desc2)   \
{ \
    ObjectPtr<ITPInterface> iTP; \
    if(iTP) \
    { \
        EVENT.connect(iTP->getObject(), \
        std::bind(& ITPInterface2::desc2, dynamic_cast<ITPInterface2 *>(iTP->getObject()), std::placeholders::_1)); \
    } \
} \

#define TPEventBindWithOne(EVENT, ITPInterface, desc)   \
{ \
    ObjectPtr<ITPInterface> iTP; \
    if(iTP) \
    { \
        EVENT.connect(iTP->getObject(), \
        std::bind(& ITPInterface::desc, dynamic_cast<ITPInterface *>(iTP->getObject()), std::placeholders::_1)); \
    } \
}

#define TPEventBindWithTwo(EVENT, ITPInterface, desc)   \
{ \
    ObjectPtr<ITPInterface> iTP; \
    if(iTP) \
    { \
        EVENT.connect(iTP->getObject(), \
        std::bind(& ITPInterface::desc, \
        dynamic_cast<ITPInterface *>(iTP->getObject()), std::placeholders::_1, std::placeholders::_2)); \
    } \
}

template<typename... ARGS>
class TPSignal
{
    typedef QPair<std::function<void (ARGS...)>, QThread *> funcPair;
public:
    TPSignal()
    {

    }

    void    checkParam(ARGS...){}

    void    connect(const QObject *object, const std::function<void (ARGS...)> func) const
    {
        m_vecFunc.push_back(qMakePair(func, object->thread()));
    }

    void    rztEmit(ARGS... args) const
    {
        for(funcPair &item : m_vecFunc)
        {
            auto subFunc = [=](){
                item.first(args ...);
            };
            TPBaseEvent *event = new TPBaseEvent();
            event->moveToThread(item.second);

            event->setFunc(subFunc);
            TPEventNotifyMgr::getInstance()->addEventNotify(event);
        }
    }

private:
    mutable QVector<QPair<std::function<void (ARGS...)>, QThread *>> m_vecFunc;
};

#endif // RZTMETAOBJECT_H
