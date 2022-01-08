#include "TPComDecodeThread.h"
#include "TPDecoder.h"
//清理资源，停止线程
void TPComDecodeThread::Close()
{
	Clear();
	
	//等待线程退出
	isExit = true;
	wait();
    m_decoder->Close();

    m_mux.lock();
    delete m_decoder;
    m_decoder = NULL;
    m_mux.unlock();
}
void TPComDecodeThread::Clear()
{
    m_mux.lock();
    m_decoder->Clear();
    while (!m_listPacks.empty())
	{
        AVPacket *pkt = m_listPacks.front();
		XFreePacket(&pkt);
        m_listPacks.pop_front();
	}

    m_mux.unlock();
}


//取出一帧数据，并出栈，如果没有返回NULL
AVPacket *TPComDecodeThread::Pop()
{
    m_mux.lock();
    if (m_listPacks.empty())
	{
        m_mux.unlock();
		return NULL;
	}
    AVPacket *pkt = m_listPacks.front();
    m_listPacks.pop_front();
    m_mux.unlock();
	return pkt;
}
void TPComDecodeThread::Push(AVPacket *pkt)
{
	if (!pkt)return;
	//阻塞
	while (!isExit)
	{
        m_mux.lock();
        if (m_listPacks.size() < maxList)
		{
            m_listPacks.push_back(pkt);
            m_mux.unlock();
			break;
		}
        m_mux.unlock();
		msleep(1);
	}
}


TPComDecodeThread::TPComDecodeThread()
{
	//打开解码器
    if (!m_decoder) m_decoder = new TPDecoder();
}


TPComDecodeThread::~TPComDecodeThread()
{	//等待线程退出
	isExit = true;
	wait();
}
