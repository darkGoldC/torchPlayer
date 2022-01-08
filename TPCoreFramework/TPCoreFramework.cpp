#include "TPCoreFramework.h"

TPCoreFramework::TPCoreFramework(QObject *parent) : QObject(parent)
{

}

void TPCoreFramework::initWork()
{
    TPVideoWidget::getInstance();
}

QObject *TPCoreFramework::getObject()
{
    return this;
}

void TPCoreFramework::startWork()
{
    m_demuxThread.StartWork();
}

void TPCoreFramework::stopWork()
{
    m_demuxThread.Close();
}

void TPCoreFramework::pauseWork()
{
    bool bChange = !m_demuxThread.isPause;
    m_demuxThread.SetPause(bChange);
}

double TPCoreFramework::getProcess()
{
    double nPos = 0.0;
    long long total = m_demuxThread.totalMs;
    if (total > 0)
    {
        nPos = (double)m_demuxThread.pts / total;
    }
    return nPos;
}

void TPCoreFramework::seekProcess(const double nValue)
{
    m_demuxThread.Seek(nValue);
}

bool TPCoreFramework::openVideo(const QString strUrl, ITPVideoWidget *pWidget)
{
    bool ret = m_demuxThread.Open(strUrl.toStdString().c_str(), pWidget);

    return ret;
}
