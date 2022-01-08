
#pragma once
#include <QThread>
#include <mutex>
#include <list>
struct AVCodecParameters;
class TPAudioDevice;
class TPResampler;
#include "TPComDecodeThread.h"

class TPAudioThread:public TPComDecodeThread
{
public:
	//当前音频播放的pts
	long long pts = 0;
	//打开，不管成功与否都清理
	virtual bool Open(AVCodecParameters *para,int sampleRate,int channels);

	//停止线程，清理资源
	virtual void Close();

	virtual void Clear();
	void run();
    TPAudioThread();
    virtual ~TPAudioThread();
	void SetPause(bool isPause);
    bool isPause = true;
protected:
    std::mutex m_amux;
    TPAudioDevice *m_audioDevice = 0;
    TPResampler *m_resampler = 0;

};

