
#include "TPDecoder.h"
extern "C"
{
#include<libavcodec/avcodec.h>
}
#include <iostream>
using namespace std;

void XFreePacket(AVPacket **pkt)
{
	if (!pkt || !(*pkt))return;
	av_packet_free(pkt);
}
void XFreeFrame(AVFrame **frame)
{
	if (!frame || !(*frame))return;
	av_frame_free(frame);
}
void TPDecoder::Close()
{
	m_decodeMux.lock();
	if (m_codec)
	{
		avcodec_close(m_codec);
		avcodec_free_context(&m_codec);
	}
	pts = 0;
	m_decodeMux.unlock();
}

void TPDecoder::Clear()
{
	m_decodeMux.lock();
	//清理解码缓冲
	if (m_codec)
		avcodec_flush_buffers(m_codec);

	m_decodeMux.unlock();
}

//打开解码器
bool TPDecoder::Open(AVCodecParameters *para)
{
	if (!para) return false;
	Close();
	//////////////////////////////////////////////////////////
	///解码器打开
	///找到解码器
	AVCodec *vcodec = avcodec_find_decoder(para->codec_id);
	if (!vcodec)
	{
		avcodec_parameters_free(&para);
		cout << "can't find the codec id " << para->codec_id << endl;
		return false;
	}
	cout << "find the AVCodec " << para->codec_id << endl;

	m_decodeMux.lock();
	m_codec = avcodec_alloc_context3(vcodec);

	///配置解码器上下文参数
	avcodec_parameters_to_context(m_codec, para);
	avcodec_parameters_free(&para);

	//八线程解码
	m_codec->thread_count = 8;

	///打开解码器上下文
	int re = avcodec_open2(m_codec, 0, 0);
	if (re != 0)
	{
		avcodec_free_context(&m_codec);
		m_decodeMux.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "avcodec_open2  failed! :" << buf << endl;
		return false;
	}
	m_decodeMux.unlock();
	cout << " avcodec_open2 success!" << endl;
	return true;
}
//发送到解码线程，不管成功与否都释放pkt空间（对象和媒体内容）
bool TPDecoder::Send(AVPacket *pkt)
{
	//容错处理
	if (!pkt || pkt->size <= 0 || !pkt->data)return false;
	m_decodeMux.lock();
	if (!m_codec)
	{
		m_decodeMux.unlock();
		return false;
	}
	int re = avcodec_send_packet(m_codec, pkt);
	m_decodeMux.unlock();
	av_packet_free(&pkt);
	if (re != 0)return false;
	return true;
}

//获取解码数据，一次send可能需要多次Recv，获取缓冲中的数据Send NULL在Recv多次
//每次复制一份，由调用者释放 av_frame_free
AVFrame* TPDecoder::Recv()
{
	m_decodeMux.lock();
	if (!m_codec)
	{
		m_decodeMux.unlock();
		return NULL;
	}
	AVFrame *frame = av_frame_alloc();
	int re = avcodec_receive_frame(m_codec, frame);
	m_decodeMux.unlock();
	if (re != 0)
	{
		av_frame_free(&frame);
		return NULL;
	}
	//cout << "["<<frame->linesize[0] << "] " << flush;
	pts = frame->pts;
	return frame;
}

TPDecoder::TPDecoder()
{
}


TPDecoder::~TPDecoder()
{
}
