#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#include "TPBaseEvent.h"
#include <QThread>
#include <thread>
#include <iostream>
TPBaseEvent::TPBaseEvent(QObject *parant): QObject(parant)
{

}

void TPBaseEvent::setFunc(std::function<void ()> func)
{
    m_func = func;
}

TPBaseEvent::~TPBaseEvent()
{
}

void TPBaseEvent::release()
{
    this->deleteLater();
}

void TPBaseEvent::sltFunc()
{
    //std::cout << "curthread:" << std::this_thread::get_id() << std::endl;
    if(m_func)
    {
        m_func();
    }
    release();
}


