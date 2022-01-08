﻿
#pragma once
class TPAudioDevice
{
public:
	
	//打开音频播放
	virtual bool Open() = 0;
	virtual void Close() = 0;
	virtual void Clear() = 0;
	//返回缓冲中还没有播放的时间（毫秒）
	virtual long long GetNoPlayMs() = 0;
	//播放音频
	virtual bool Write(const unsigned char *data, int datasize) = 0;
	virtual int GetFree() = 0;
	virtual void SetPause(bool isPause) = 0;

    static TPAudioDevice *Get();
    TPAudioDevice();
    virtual ~TPAudioDevice();

public:
    int m_nSampleRate = 44100;
    int m_nSampleSize = 16;
    int m_nChannels = 2;
};

