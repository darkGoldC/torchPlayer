#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef RZTBASEEVENT_H
#define RZTBASEEVENT_H

#include <tuple>
#include <memory>
#include <functional>
#include <QVariant>
#include <QObject>
#include "TP_BaseDefine.h"

class TPBASESHARED_EXPORT TPBaseEvent : public QObject
{
    Q_OBJECT
public:
    explicit TPBaseEvent(QObject *parant = Q_NULLPTR);
    void setFunc(const std::function<void ()> func);
    ~TPBaseEvent();

    void release();

public slots:
    void    sltFunc();

public:
    std::function<void ()>          m_func;
};
Q_DECLARE_METATYPE(TPBaseEvent *)

#endif
 // RZTBASEEVENT_H
