#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include "TPLog.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageLogContext>
#include <QtDebug>
#include <QDebug>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#include <QMutex>
#include <QSettings>
#include <QtAlgorithms>
#include <iostream>
#include <iostream>
#include "TPNanoLog.h"
#include "TPGlobalInfoMgr.h"
#define CYAN        "\e[1;36m"

TPLog g_log;

#ifndef WIN32
#include "unistd.h"
void sigHander(int sigNum)
{
    TPNanolog::flush();
    //恢复SIGALRM 信号到默认处理动作
    TPLog::instance()->restoreSignalHandler(sigNum);
}

void TPLog::installSignalHandler()
{
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_handler = sigHander; // callback to crashHandler for fatal signals
    // sigaction to use sa_sigaction file. ref: http://www.linuxprogrammingblog.com/code-examples/sigaction
    action.sa_flags = SA_SIGINFO;

    // do it verbose style - install all signal actions
    for (const auto& sig_pair : m_kSignals)
    {
        struct sigaction old_action;
        memset(&old_action, 0, sizeof (old_action));

        if (sigaction(sig_pair.first, &action, &old_action) < 0) {
            std::string signalerror = "sigaction - " +  sig_pair.second;
            perror(signalerror.c_str());
        } else {
            m_savedSigActions[sig_pair.first] = old_action;
        }
    }
}

void TPLog::restoreSignalHandler(int signal_number)
{
    auto old_action_it = m_savedSigActions.find(signal_number);
    if (old_action_it == m_savedSigActions.end()) {
        return;
    }

    if (sigaction(signal_number, &(old_action_it->second), nullptr) < 0) {
        auto signalname = std::string("sigaction - ") + m_kSignals.at(signal_number);
        perror(signalname.c_str());
    }

    m_savedSigActions.erase(old_action_it);
}
#endif

TPLog::TPLog(QObject *parent)
    :QObject(parent),
      m_mutex(QMutex::Recursive),
      m_backConsole(false)
{

}

TPLog::~TPLog()
{

}

void TPLog::initLog(const bool &bConsole, const QString &strFilePath)
{
    QMutexLocker locker(&m_mutex);

    //change sigaction
#ifndef WIN32
    installSignalHandler();
#endif

    m_bConsole = bConsole;

    setBackConsole(m_bConsole);

    m_bNeedLog = true;
    m_nMaxCountLogFile = 30;

    TPNanolog::STTPLogConfig logConfig;
    TPNanolog::setLogConfig(logConfig);


    QString strLogPath = TPGlobalInfoMgr::getInstance()->getLongPath() +"/";
    QString strOparaLogPath = strLogPath + "TPOparaLog/";
    deleteLogFile(strLogPath, m_nMaxCountLogFile);
    //corefile clear
    deleteLogFile(COREFILE_DIR_PATH, m_nMaxCountCoreFile);
    QDir dirLog(strLogPath);
    if (!dirLog.exists())
    {
        dirLog.mkpath(strLogPath);
    }

    QDir dirOpara(strOparaLogPath);
    if (!dirOpara.exists())
    {
        dirOpara.mkpath(strOparaLogPath);
    }

    if(!m_bNeedLog)
    {
        return;
    }

    QDateTime nowDate = QDateTime::currentDateTime();
    QString strBuf = QString("%1.log").arg(nowDate.toString("yyyyMMdd-hhmmss"));
    TPNanolog::initialize(TPNanolog::GuaranteedLogger(), strLogPath.toStdString(), strBuf.toStdString(), 5);
    TPNanolog::initialize(TPNanolog::GuaranteedLogger(), strOparaLogPath.toStdString(), strBuf.toStdString(), 1, true);
    //操作日志是否输出到开发日志中
    TPNanolog::set_oparate_log(false);
}

void TPLog::setBackConsole(const bool &bStatus)
{
    m_backConsole.store(bStatus);

    QMutexLocker locker(&m_mutex);
    TPNanolog::TPLogCallBack callBack;
    if(bStatus)
    {
        callBack = std::bind(&TPLog::logProCallBack, this,  std::placeholders::_1);
    }
    TPNanolog::setLogCallback(callBack);
}

void TPLog::logProCallBack(std::string strLineLog)
{
    QMutexLocker locker(&m_mutex);

    //for devloper
    if (m_bConsole)
    {
#ifdef WIN32
        QString strConsole = QString("%1\n").arg(strLineLog.c_str());
        std::cout << strConsole.toLocal8Bit().data() << std::endl;
#else
        QString strTemp(strLineLog.c_str());
        std::cout << strTemp.replace("\n", "").toStdString().c_str() << std::endl;
#endif
    }
    //wcz 2020-12-31 win异常，不明原因，暂时封掉
//    ObjectPtr<ITPBackConsoleController> backConsoleController;
//    if (backConsoleController && m_backConsole.load())
//    {
//        QMetaObject::invokeMethod(backConsoleController->getObject(),
//                                  "sltTextBrowerText",
//                                  Q_ARG(QString, QString::fromStdString(strLineLog) + "\r\n\r\n"));
//    }
}

TPLog *TPLog::instance()
{
    static TPLog s_log;
    return &s_log;
}


void TPLog::deleteLogFile(const QString &strDir, const int& nCount)
{
    QDir dir(strDir);
    dir.setFilter(QDir::Files);

    QList<QFileInfo> fileInfoList = dir.entryInfoList();

    if(fileInfoList.size() > nCount)
    {
        std::sort(fileInfoList.begin(),fileInfoList.end(),[](const QFileInfo &a,const QFileInfo &b)
        {
            return a.lastModified() > b.lastModified();
        });

        for(int i = nCount; i < fileInfoList.size();i++)
        {
            dir.remove(fileInfoList.at(i).fileName());
        }
    }
}

