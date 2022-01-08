
#pragma once

///解码和显示视频
struct AVPacket;
struct AVCodecParameters;
class TPDecoder;
#include <list>
#include <mutex>
#include <QThread>
#include "TPVideoWidget.h"
#include "TPComDecodeThread.h"

class TPVideoThread:public TPComDecodeThread
{
public:

	//解码pts，如果接收到的解码数据pts >= seekpts return true 并且显示画面
	virtual bool RepaintPts(AVPacket *pkt, long long seekpts);
	//打开，不管成功与否都清理
    virtual bool Open(AVCodecParameters *para,ITPVideoWidget *m_ivideoWidget,int width,int height);
	void run();
    TPVideoThread();
    virtual ~TPVideoThread();
	//同步时间，由外部传入
	long long synpts = 0;

	void SetPause(bool isPause);
    bool isPause = true;
protected:
    ITPVideoWidget *m_ivideoWidget = 0;
    std::mutex m_vmux;


};

