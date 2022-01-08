
#include "TPDemuxer.h"
#include <iostream>
using namespace std;
extern "C" {
	#include "libavformat/avformat.h"
}
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
static double r2d(AVRational r)
{
	return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}

bool TPDemuxer::Open(const char *url)
{
	Close();
	//参数设置
	AVDictionary *opts = NULL;
	//设置rtsp流已tcp协议打开
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//网络延时时间
	av_dict_set(&opts, "max_delay", "500", 0);

	m_demuxMux.lock();
	int re = avformat_open_input(
		&m_demuxIc,
		url,
		0,  // 0表示自动选择解封器
		&opts //参数设置，比如rtsp的延时时间
	);
	if (re != 0)
	{
		m_demuxMux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << url << " failed! :" << buf << endl;
		return false;
	}
	cout << "open " << url << " success! " << endl;

	//获取流信息 
	re = avformat_find_stream_info(m_demuxIc, 0);

	//总时长 毫秒
	this->m_totalMs = m_demuxIc->duration / (AV_TIME_BASE / 1000);
	cout << "totalMs = " << m_totalMs << endl;

	//打印视频流详细信息
	av_dump_format(m_demuxIc, 0, url, 0);


	//获取视频流
	m_videoStream = av_find_best_stream(m_demuxIc, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream *as = m_demuxIc->streams[m_videoStream];
	m_width = as->codecpar->width;
	m_height = as->codecpar->height;

	cout << "=======================================================" << endl;
	cout << m_videoStream << "视频信息" << endl;
	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << "width=" << as->codecpar->width << endl;
	cout << "height=" << as->codecpar->height << endl;
	//帧率 fps 分数转换
	cout << "video fps = " << r2d(as->avg_frame_rate) << endl;

	cout << "=======================================================" << endl;
	cout << m_audioStream << "音频信息" << endl;
	//获取音频流
	m_audioStream = av_find_best_stream(m_demuxIc, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
	as = m_demuxIc->streams[m_audioStream];
	m_sampleRate = as->codecpar->sample_rate;
	m_channels = as->codecpar->channels;

	cout << "codec_id = " << as->codecpar->codec_id << endl;
	cout << "format = " << as->codecpar->format << endl;
	cout << "sample_rate = " << as->codecpar->sample_rate << endl;
	//AVSampleFormat;
	cout << "channels = " << as->codecpar->channels << endl;
	//一帧数据？？ 单通道样本数 
	cout << "frame_size = " << as->codecpar->frame_size << endl;
	//1024 * 2 * 2 = 4096  fps = sample_rate/frame_size
	m_demuxMux.unlock();


	return true;
}
//清空读取缓存
void TPDemuxer::Clear()
{
	m_demuxMux.lock();
	if (!m_demuxIc)
	{
		m_demuxMux.unlock();
		return ;
	}
	//清理读取缓冲
	avformat_flush(m_demuxIc);
	m_demuxMux.unlock();
}
void TPDemuxer::Close()
{
	m_demuxMux.lock();
	if (!m_demuxIc)
	{
		m_demuxMux.unlock();
		return;
	}
	avformat_close_input(&m_demuxIc);
	//媒体总时长（毫秒）
	m_totalMs = 0;
	m_demuxMux.unlock();
}

//seek 位置 pos 0.0 ~1.0
bool TPDemuxer::Seek(double pos)
{
	m_demuxMux.lock();
	if (!m_demuxIc)
	{
		m_demuxMux.unlock();
		return false;
	}
	//清理读取缓冲
	avformat_flush(m_demuxIc);

	long long seekPos = 0;
	seekPos = m_demuxIc->streams[m_videoStream]->duration * pos;
	int re = av_seek_frame(m_demuxIc, m_videoStream, seekPos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
	m_demuxMux.unlock();
	if (re < 0) return false;
	return true;
}
//获取视频参数  返回的空间需要清理  avcodec_parameters_free
AVCodecParameters *TPDemuxer::CopyVPara()
{
	m_demuxMux.lock();
	if (!m_demuxIc)
	{
		m_demuxMux.unlock();
		return NULL;
	}
	AVCodecParameters *pa = avcodec_parameters_alloc();
	avcodec_parameters_copy(pa, m_demuxIc->streams[m_videoStream]->codecpar);
	m_demuxMux.unlock();
	return pa;
}

//获取音频参数  返回的空间需要清理 avcodec_parameters_free
AVCodecParameters *TPDemuxer::CopyAPara()
{
	m_demuxMux.lock();
	if (!m_demuxIc)
	{
		m_demuxMux.unlock();
		return NULL;
	}
	AVCodecParameters *pa = avcodec_parameters_alloc();
	avcodec_parameters_copy(pa, m_demuxIc->streams[m_audioStream]->codecpar);
	m_demuxMux.unlock();
	return pa;
}
bool TPDemuxer::IsAudio(AVPacket *pkt)
{
	if (!pkt) return false;
	if (pkt->stream_index == m_videoStream)
		return false;
	return true;

}
AVPacket *TPDemuxer::ReadVideo()
{
	m_demuxMux.lock();
	if (!m_demuxIc) //容错
	{
		m_demuxMux.unlock();
		return 0;
	}
	m_demuxMux.unlock();

	AVPacket *pkt = NULL;
	//防止阻塞
	for (int i = 0; i < 20; i++)
	{
		pkt = Read();
		if (!pkt)break;
		if (pkt->stream_index == m_videoStream)
		{
			break;
		}
		av_packet_free(&pkt);
	}
	return pkt;
}
//空间需要调用者释放 ，释放AVPacket对象空间，和数据空间 av_packet_free
AVPacket *TPDemuxer::Read()
{
	m_demuxMux.lock();
	if (!m_demuxIc) //容错
	{
		m_demuxMux.unlock();
		return 0;
	}
	AVPacket *pkt = av_packet_alloc();
	//读取一帧，并分配空间
	int re = av_read_frame(m_demuxIc, pkt);
	if (re != 0)
	{
		m_demuxMux.unlock();
		av_packet_free(&pkt);
		return 0;
	}
	//pts转换为毫秒
	pkt->pts = pkt->pts*(1000 * (r2d(m_demuxIc->streams[pkt->stream_index]->time_base)));
	pkt->dts = pkt->dts*(1000 * (r2d(m_demuxIc->streams[pkt->stream_index]->time_base)));
	m_demuxMux.unlock();
	//cout << pkt->pts << " "<<flush;
	return pkt;

}
TPDemuxer::TPDemuxer()
{
	static bool isFirst = true;
	static std::mutex dmux;
	dmux.lock();
	if (isFirst)
	{
		//初始化封装库
		av_register_all();

		//初始化网络库 （可以打开rtsp rtmp http 协议的流媒体视频）
		avformat_network_init();
		isFirst = false;
	}
	dmux.unlock();
}


TPDemuxer::~TPDemuxer()
{
}
