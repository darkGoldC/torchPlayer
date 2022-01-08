#pragma once
#include <mutex>
struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;
class TPDemuxer
{
public:

	//打开媒体文件，或者流媒体 rtmp http rstp
	virtual bool Open(const char *url);

	//空间需要调用者释放 ，释放AVPacket对象空间，和数据空间 av_packet_free
	virtual AVPacket *Read();
	//只读视频，音频丢弃空间释放
	virtual AVPacket *ReadVideo();

	virtual bool IsAudio(AVPacket *pkt);

	//获取视频参数  返回的空间需要清理  avcodec_parameters_free
	virtual AVCodecParameters *CopyVPara();
	
	//获取音频参数  返回的空间需要清理 avcodec_parameters_free
	virtual AVCodecParameters *CopyAPara();

	//seek 位置 pos 0.0 ~1.0
	virtual bool Seek(double pos);

	//清空读取缓存
	virtual void Clear();
	virtual void Close();


    TPDemuxer();
    virtual ~TPDemuxer();


public:
	//媒体总时长（毫秒）
    int m_totalMs = 0;
    int m_width = 0;
    int m_height = 0;
    int m_sampleRate = 0;
    int m_channels = 0;



protected:
    std::mutex m_demuxMux;
	//解封装上下文
    AVFormatContext *m_demuxIc = NULL;
	//音视频索引，读取时区分音视频
    int m_videoStream = 0;
    int m_audioStream = 1;
};

