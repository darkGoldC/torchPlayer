#pragma once
#include <QThread>
#include "ITPVideoWidget.h"
#include <mutex>

class TPDemuxer;
class TPVideoThread;
class TPAudioThread;
class TPDemuxThread:public QThread
{
public:
	//创建对象并打开
    virtual bool Open(const char *url, ITPVideoWidget *videoWidget);

	//启动所有线程
    virtual void StartWork();

	//关闭线程清理资源
	virtual void Close();
	virtual void Clear();

	virtual void Seek(double pos);

	void run();
    TPDemuxThread();
    virtual ~TPDemuxThread();
	bool isExit = false;
	long long pts = 0;
	long long totalMs = 0;
	void SetPause(bool isPause);
    bool isPause = true;
protected:
    std::mutex m_demuxThreadMux;
    TPDemuxer *m_demuxer = 0;
    TPVideoThread *m_vthread = 0;
    TPAudioThread *m_athread = 0;
};

