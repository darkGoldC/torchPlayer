
#include "TPVideoWidget.h"
#include "TPVideoThread.h"
#include "TPDecoder.h"
#include <iostream>
using namespace std;
//打开，不管成功与否都清理
bool TPVideoThread::Open(AVCodecParameters *para, ITPVideoWidget *call,int width,int height)
{
	if (!para)return false;
	Clear();

	m_vmux.lock();
	synpts = 0;
	//初始化显示窗口
	this->m_ivideoWidget = call;
	if (call)
	{
		call->Init(width, height);
	}
	m_vmux.unlock();
	int re = true;
	if (!m_decoder->Open(para))
	{
		cout << "audio XDecode open failed!" << endl;
		re = false;
	}
	
	cout << "XAudioThread::Open :" << re << endl;
	return re;
}
void TPVideoThread::SetPause(bool isPause)
{
	m_vmux.lock();
	this->isPause = isPause;
	m_vmux.unlock();
}
void TPVideoThread::run()
{
	while (!isExit)
	{
		m_vmux.lock();
		if (this->isPause)
		{
			m_vmux.unlock();
			msleep(5);
			continue;
		}
		//cout << "synpts = " << synpts << " dpts =" << decode->pts << endl;
		//音视频同步
		if (synpts >0 && synpts < m_decoder->pts)
		{
			m_vmux.unlock();
			msleep(1);
			continue;
		}
		AVPacket *pkt = Pop();
		bool re = m_decoder->Send(pkt);
		if (!re)
		{
			m_vmux.unlock();
			msleep(1);
			continue;
		}
		//一次send 多次recv
		while (!isExit)
		{
			AVFrame * frame = m_decoder->Recv();
			if (!frame)break;
			//显示视频
			if (m_ivideoWidget)
			{
				m_ivideoWidget->Repaint(frame);
			}

		}
		m_vmux.unlock();
	}
}
//解码pts，如果接收到的解码数据pts >= seekpts return true 并且显示画面
bool TPVideoThread::RepaintPts(AVPacket *pkt, long long seekpts)
{
	m_vmux.lock();
	bool re = m_decoder->Send(pkt);
	if (!re)
	{
		m_vmux.unlock();
		return true; //表示结束解码
	}
	AVFrame *frame = m_decoder->Recv();
	if (!frame)
	{
		m_vmux.unlock();
		return false;
	}
	//到达位置
	if (m_decoder->pts >= seekpts)
	{
		if(m_ivideoWidget)
			m_ivideoWidget->Repaint(frame);
		m_vmux.unlock();
		return true;
	}
	XFreeFrame(&frame);
	m_vmux.unlock();
	return false;
}
TPVideoThread::TPVideoThread()
{
}


TPVideoThread::~TPVideoThread()
{

}
