
#include "TPResampler.h"
extern "C" {
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
}
#pragma comment(lib,"swresample.lib")
#include <iostream>
using namespace std;

void TPResampler::Close()
{
	m_resampleMux.lock();
	if (m_actx)
		swr_free(&m_actx);

	m_resampleMux.unlock();
}

//输出参数和输入参数一致除了采样格式，输出为S16
bool TPResampler::Open(AVCodecParameters *para,bool isClearPara)
{
	if (!para)return false;
	m_resampleMux.lock();
	//音频重采样 上下文初始化
	//if(!actx)
	//	actx = swr_alloc();

	//如果actx为NULL会分配空间
	m_actx = swr_alloc_set_opts(m_actx,
		av_get_default_channel_layout(2),	//输出格式
		(AVSampleFormat)outFormat,			//输出样本格式 1 AV_SAMPLE_FMT_S16
		para->sample_rate,					//输出采样率
		av_get_default_channel_layout(para->channels),//输入格式
		(AVSampleFormat)para->format,
		para->sample_rate,
		0, 0
	);
	if(isClearPara)
		avcodec_parameters_free(&para);
	int re = swr_init(m_actx);
	m_resampleMux.unlock();
	if (re != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "swr_init  failed! :" << buf << endl;
		return false;
	}
	//unsigned char *pcm = NULL;
	return true;
}

//返回重采样后大小,不管成功与否都释放indata空间
int TPResampler::Resample(AVFrame *indata, unsigned char *d)
{
	if (!indata) return 0;
	if (!d)
	{
		av_frame_free(&indata);
		return 0;
	}
	uint8_t *data[2] = { 0 };
	data[0] = d;
	int re = swr_convert(m_actx,
		data, indata->nb_samples,		//输出
		(const uint8_t**)indata->data, indata->nb_samples	//输入
	);
	int outSize = re * indata->channels * av_get_bytes_per_sample((AVSampleFormat)outFormat);
	av_frame_free(&indata);
	if (re <= 0)return re;
	
	return outSize;
}
TPResampler::TPResampler()
{
}


TPResampler::~TPResampler()
{
}
