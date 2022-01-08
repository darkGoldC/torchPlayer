#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#ifndef TPLOG_H
#define TPLOG_H
#include <QObject>
#include <QMutex>
#include <atomic>
#include "TP_BaseDefine.h"

#ifdef WIN32
#define COREFILE_DIR_PATH "C:\\corefile"
#define WCOREFILE_DIR_PATH L"C:\\corefile"
#else
#define COREFILE_DIR_PATH "/corefile"
#include <signal.h>
#endif

class TPBASESHARED_EXPORT TPLog : public QObject
{
public:
    TPLog(QObject *parent = Q_NULLPTR);
    ~TPLog();

    /**
    * @brief               接口说明
    * @author              Zhaojianbiao
    * @date                2018-10-19
    * @param bConsole      [in]   是否控制台输出
    * @param strFilePath   [in]   日志输出路径
    */
    void     initLog(const bool& bConsole,const QString &strFilePath);

    void     setBackConsole(const bool &bStatus);
    void     logProCallBack(std::string strLineLog);
    static   TPLog*  instance();

#ifndef WIN32
    void     restoreSignalHandler(int signal_number);
    void     installSignalHandler();
#endif

private:
    /**
    * @brief               删除日志文件
    * @author              Zhaojianbiao
    * @date                2018-10-19
    * @param strDir        [in]   文件夹路径
    */
    void     deleteLogFile(const QString &strDir, const int& nCount);

private:
    QMutex    m_mutex;
    int       m_nMaxCountLogFile = 30;
    const int  m_nMaxCountCoreFile = 1;
    bool      m_bNeedLog = true;
    bool      m_bConsole = true;
    std::atomic<bool>   m_backConsole;

#ifndef WIN32
    //崩溃信号处理
    std::map<int, struct sigaction> m_savedSigActions;
    const std::map<int, std::string> m_kSignals = {
        {SIGABRT, "SIGABRT"},
        {SIGFPE, "SIGFPE"},
        {SIGILL, "SIGILL"},
        {SIGSEGV, "SIGSEGV"},
        {SIGTERM, "SIGTERM"},
        {SIGBUS, "SIGBUS"},
    };
#endif

};

extern TPBASESHARED_EXPORT TPLog g_log;
#endif // TPLOG_H
