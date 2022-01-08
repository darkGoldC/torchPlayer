
#include "TPAudioThread.h"
#include "TPDecoder.h"
#include "TPAudioDevice.h"
#include "TPResampler.h"
#include <iostream>
using namespace std;

void TPAudioThread::Clear()
{
    TPComDecodeThread::Clear();
	m_mux.lock();
	if (m_audioDevice) m_audioDevice->Clear();
	m_mux.unlock();
}
//停止线程，清理资源
void TPAudioThread::Close()
{
    TPComDecodeThread::Close();
	if (m_resampler)
	{
		m_resampler->Close();
		m_amux.lock();
		delete m_resampler;
		m_resampler = NULL;
		m_amux.unlock();
	}
	if (m_audioDevice)
	{
		m_audioDevice->Close();
		m_amux.lock();
		m_audioDevice = NULL;
		m_amux.unlock();
	}
}
bool TPAudioThread::Open(AVCodecParameters *para,int sampleRate, int channels)
{
	if (!para)return false;
	Clear();

	m_amux.lock();
	pts = 0;
	bool re = true;
	if (!m_resampler->Open(para, false))
	{
		cout << "XResample open failed!" << endl;
		re = false;
	}
	m_audioDevice->m_nSampleRate = sampleRate;
	m_audioDevice->m_nChannels = channels;
	if (!m_audioDevice->Open())
	{
		re = false;
		cout << "XAudioPlay open failed!" << endl;
	}
	if (!m_decoder->Open(para))
	{
		cout << "audio XDecode open failed!" << endl;
		re = false;
	}
	m_amux.unlock();
	cout << "XAudioThread::Open :" << re << endl;
	return re;
}

void TPAudioThread::SetPause(bool isPause)
{
	//amux.lock();
	this->isPause = isPause;
	if (m_audioDevice)
		m_audioDevice->SetPause(isPause);
	//amux.unlock();
}

void TPAudioThread::run()
{
	unsigned char *pcm = new unsigned char[1024 * 1024 * 10];
	while (!isExit)
	{
		m_amux.lock();
		if (isPause)
		{
			m_amux.unlock();
			msleep(5);
			continue;
		}

		//没有数据
		//if (packs.empty() || !decode || !res || !ap)
		//{
		//	mux.unlock();
		//	msleep(1);
		//	continue;
		//}

		//AVPacket *pkt = packs.front();
		//packs.pop_front();
		AVPacket *pkt = Pop();
		bool re = m_decoder->Send(pkt);
		if (!re)
		{
			m_amux.unlock();
			msleep(1);
			continue;
		}
		//一次send 多次recv
		while (!isExit)
		{
			AVFrame * frame = m_decoder->Recv();
			if (!frame) break;

			//减去缓冲中未播放的时间
			pts = m_decoder->pts - m_audioDevice->GetNoPlayMs();

			//cout << "audio pts = " << pts << endl;

			//重采样 
			int size = m_resampler->Resample(frame, pcm);
			//播放音频
			while (!isExit)
			{
				if (size <= 0)break;
				//缓冲未播完，空间不够
				if (m_audioDevice->GetFree() < size || isPause)
				{
					msleep(1);
					continue;
				}
				m_audioDevice->Write(pcm, size);
				break;
			}
		}
		m_amux.unlock();
	}
	delete pcm;
}

TPAudioThread::TPAudioThread()
{
    if (!m_resampler) m_resampler = new TPResampler();
    if (!m_audioDevice) m_audioDevice = TPAudioDevice::Get();
}


TPAudioThread::~TPAudioThread()
{
	//等待线程退出
	isExit = true;
	wait();
}
