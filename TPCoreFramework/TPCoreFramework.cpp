#include "TPCoreFramework.h"

TPCoreFramework::TPCoreFramework(QObject *parent) : QObject(parent)
{

}

void TPCoreFramework::initWork()
{
    //TPVideoWidget::getInstance();
    m_pInputManager = std::make_shared<TPInputManager>();
}

QObject *TPCoreFramework::getObject()
{
    return this;
}

void TPCoreFramework::startWork()
{

}

void TPCoreFramework::stopWork()
{

}

void TPCoreFramework::pauseWork()
{

}

double TPCoreFramework::getProcess()
{
    double nPos = 0.0;

    return nPos;
}

void TPCoreFramework::seekProcess(const double nValue)
{

}

bool TPCoreFramework::openVideo(const QString strUrl, ITPVideoWidget *pWidget)
{
    bool ret = false;
    m_pInputManager->start(strUrl.toStdString());
    return ret;
}
