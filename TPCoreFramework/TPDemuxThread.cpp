#include "TPDemuxThread.h"
#include "TPDemuxer.h"
#include "TPVideoThread.h"
#include "TPAudioThread.h"
#include <iostream>
extern "C"
{
#include <libavformat/avformat.h>
}
#include "TPDecoder.h"

using namespace std;
void TPDemuxThread::Clear()
{
	m_demuxThreadMux.lock();
	if (m_demuxer)m_demuxer->Clear();
	if (m_vthread) m_vthread->Clear();
	if (m_athread) m_athread->Clear();
	m_demuxThreadMux.unlock();
}

void TPDemuxThread::Seek(double pos)
{
	//清理缓存
	Clear();

	m_demuxThreadMux.lock();
	bool status = this->isPause;
	m_demuxThreadMux.unlock();
	//暂停
	SetPause(true);

	m_demuxThreadMux.lock();
	if (m_demuxer)
		m_demuxer->Seek(pos);
	//实际要显示的位置pts
	long long seekPts = pos*m_demuxer->m_totalMs;
	while (!isExit)
	{
		AVPacket *pkt = m_demuxer->ReadVideo();
		if (!pkt) break;
		//如果解码到seekPts
		if (m_vthread->RepaintPts(pkt, seekPts))
		{
			this->pts = seekPts;
			break;
		}
		//bool re = vt->decode->Send(pkt);
		//if (!re) break;
		//AVFrame *frame = vt->decode->Recv();
		//if (!frame) continue;
		////到达位置
		//if (frame->pts >= seekPts)
		//{
		//	this->pts = frame->pts;
		//	vt->call->Repaint(frame);
		//	break;
		//}
		//av_frame_free(&frame);
	}

	m_demuxThreadMux.unlock();

	//seek是非暂停状态
	if(!status)
		SetPause(false);
}

void TPDemuxThread::SetPause(bool isPause)
{
	m_demuxThreadMux.lock();
	this->isPause = isPause;
	if (m_athread) m_athread->SetPause(isPause);
	if (m_vthread) m_vthread->SetPause(isPause);
	m_demuxThreadMux.unlock();
}

void TPDemuxThread::run()
{
	while (!isExit)
	{
		m_demuxThreadMux.lock();
		if (isPause)
		{
			m_demuxThreadMux.unlock();
			msleep(5);
			continue;
		}
		if (!m_demuxer)
		{
			m_demuxThreadMux.unlock();
			msleep(5);
			continue;
		}

		
		//音视频同步
		if (m_vthread && m_athread)
		{
			pts = m_athread->pts;
			m_vthread->synpts = m_athread->pts;
		}


		AVPacket *pkt = m_demuxer->Read();
		if (!pkt) 
		{
			m_demuxThreadMux.unlock();
			msleep(5);
			continue;
		}
		//判断数据是音频
		if (m_demuxer->IsAudio(pkt))
		{
			//while (at->IsFull())
			{
			//	vt->synpts = at->pts;
			}
			if(m_athread)m_athread->Push(pkt);
		}
		else //视频
		{
			//while (vt->IsFull())
			//{
			//	vt->synpts = at->pts;
			//}
			if (m_vthread)m_vthread->Push(pkt);
		}
		m_demuxThreadMux.unlock();
		msleep(1);
	}
}


bool TPDemuxThread::Open(const char *url, ITPVideoWidget *videoWidget)
{
	if (url == 0 || url[0] == '\0')
		return false;

	m_demuxThreadMux.lock();
	if (!m_demuxer) m_demuxer = new TPDemuxer();
	if (!m_vthread) m_vthread = new TPVideoThread();
	if (!m_athread) m_athread = new TPAudioThread();

	//打开解封装
	bool re = m_demuxer->Open(url);
	if (!re)
	{
		m_demuxThreadMux.unlock();
		cout << "demux->Open(url) failed!" << endl;
		return false;
	}
	//打开视频解码器和处理线程
    if (!m_vthread->Open(m_demuxer->CopyVPara(), videoWidget, m_demuxer->m_width, m_demuxer->m_height))
	{
		re = false;
		cout << "vt->Open failed!" << endl;
	}
	//打开音频解码器和处理线程
	if (!m_athread->Open(m_demuxer->CopyAPara(), m_demuxer->m_sampleRate, m_demuxer->m_channels))
	{
		re = false;
		cout << "at->Open failed!" << endl;
	}
	totalMs = m_demuxer->m_totalMs;
	m_demuxThreadMux.unlock();

	cout << "XDemuxThread::Open " << re << endl;
	return re;
}

//关闭线程清理资源
void TPDemuxThread::Close()
{
	isExit = true;
	wait();
	if (m_vthread) m_vthread->Close();
	if (m_athread) m_athread->Close();
	m_demuxThreadMux.lock();
	delete m_vthread;
	delete m_athread;
	m_vthread = NULL;
	m_athread = NULL;
	m_demuxThreadMux.unlock();
}
//启动所有线程
void TPDemuxThread::StartWork()
{
	m_demuxThreadMux.lock();
	if (!m_demuxer) m_demuxer = new TPDemuxer();
	if (!m_vthread) m_vthread = new TPVideoThread();
	if (!m_athread) m_athread = new TPAudioThread();
	//启动当前线程
	QThread::start();
	if (m_vthread)m_vthread->start();
	if (m_athread)m_athread->start();
	m_demuxThreadMux.unlock();
}
TPDemuxThread::TPDemuxThread()
{
}


TPDemuxThread::~TPDemuxThread()
{
	isExit = true;
	wait();
}
