#include "TPFFmpegDemuxer.h"
#include <thread>
#include "ITPValueMgr.h"

TPFFmpegDemuxer::TPFFmpegDemuxer()
{

}

bool            TPFFmpegDemuxer::load()
{
    //关闭先前一次的资源
    closeDemuxer();

    bool bRet = false;
    //参数设置, 后期使用配置读取配置
    AVDictionary *opts = NULL;
    //设置rtsp流已tcp协议打开
    av_dict_set(&opts, "rtsp_transport", "tcp", 0);
    //网络延时时间
    av_dict_set(&opts, "max_delay", "500", 0);

    InterfacePtr<ITPValueMgr> tpValueMgr;
    std::any valueAny = tpValueMgr->getValue("inputPlayUrl");

    std::string strInputUrl = std::any_cast<std::string>(valueAny);
    if(valueAny.has_value() || strInputUrl.empty())
    {
        closeDemuxer();
        return false;
    }

    {
        std::lock_guard<std::mutex> locker(m_demuxMux);
        int re = avformat_open_input(
            &m_ic,
            strInputUrl.c_str(),
            0,  // 0表示自动选择解封器
            &opts //参数设置，比如rtsp的延时时间
        );
        if (re != 0)
        {
            closeDemuxer();
            return false;
        }

        re = avformat_find_stream_info(m_ic, 0);
        //opts内存释放
    }

    //初始化流
    int nNumStreams = m_ic->nb_streams;
    if(! nNumStreams )
    {
        closeDemuxer();
        return false;
    }

    for(int nIndex = 0; nIndex < nNumStreams; nIndex++)
    {
        std::shared_ptr<avformat_track_t> trackPtr = std::make_shared<avformat_track_t>();
        AVStream    *pStream = m_ic->streams[nIndex];
        const AVCodecParameters *cp = pStream->codecpar;
        es_format_t esFmt;

        //艺术字体不作为一个流
        if(pStream->disposition == AV_DISPOSITION_ATTACHED_PIC)
        {
            continue;
        }
        switch (cp->codec_type)
        {
            case AVMEDIA_TYPE_AUDIO:
            {
                //CHJ 后期改成自定义类型
                esFmt.init(AUDIO_ES, cp->codec_id);
                esFmt.nOriginalCodeType = cp->codec_tag;
                esFmt.nBitrate = cp->bit_rate;
                esFmt.audioFormat.nChannels = cp->channels;
                esFmt.audioFormat.nSampleRate = cp->sample_rate;
                esFmt.audioFormat.nBitspersample = cp->bits_per_coded_sample;
                esFmt.audioFormat.nBlockalign = cp->block_align;

                if(cp->codec_id == AV_CODEC_ID_AAC_LATM)
                {
                    esFmt.bPacketized = false;
                }
                break;
            }
            case AVMEDIA_TYPE_VIDEO:
            {
                esFmt.init(VIDEO_ES, cp->codec_id);
                esFmt.nOriginalCodeType = cp->codec_tag;
                esFmt.videoFormat.nBitsPerPixel = cp->bits_per_coded_sample;
                if(cp->codec_id == AV_CODEC_ID_RAWVIDEO)
                {
                    esFmt.nCodeType = esFmt.videoFormat.nChroma;
                }

                esFmt.videoFormat.nWidth = cp->width;
                esFmt.videoFormat.nHeight = cp->height;
                esFmt.videoFormat.nVisibleWidth = esFmt.videoFormat.nWidth;
                esFmt.videoFormat.nVisibleHeight = esFmt.videoFormat.nHeight;

                //CHJ 翻转的一些数据也需要设置

                //帧率
                AVRational rate;
                rate = av_guess_frame_rate(m_ic, pStream, NULL);
                if(rate.den && rate.num)
                {
                    esFmt.videoFormat.nFrameRateNum = rate.num;
                    esFmt.videoFormat.nFrameRateBase = rate.den;
                }

                esFmt.videoFormat.nSarNum = pStream->sample_aspect_ratio.num;
                if(pStream->sample_aspect_ratio.num > 0)
                {
                    esFmt.videoFormat.nSarDen = pStream->sample_aspect_ratio.den;
                }
                else
                {
                    esFmt.videoFormat.nSarDen = 0;
                }
                break;
            }
            default:
            {
                //CHJ 字幕和附件后期处理
                qTPInfo() << "there is not handle";
                break;
            }
        }

        //初始化track信息
        //trackPtr->p_es =
    }

    int nStartTime = 0;
    if(m_ic->start_time != (int64_t)AV_NOPTS_VALUE)
    {
        nStartTime = m_ic->start_time * 1000000 / AV_TIME_BASE;
    }


    bRet = true;
    return bRet;
}

bool TPFFmpegDemuxer::unload()
{
    return true;
}

bool TPFFmpegDemuxer::demux()
{
    bool bRet = false;



    return bRet;
}

void TPFFmpegDemuxer::initFfmpeg()
{
    //初始化网络
    avformat_network_init();
    //注册所有格式
    av_register_all();
}

void TPFFmpegDemuxer::closeDemuxer()
{
    if(m_ic)
    {
        if(m_ic->pb)
        {
            av_free(m_ic->pb->buffer);
            av_free(m_ic->pb);
        }
        avformat_close_input(&m_ic);
        m_ic = nullptr;
    }

    //内存情况后续再完善
    m_vecTracks.clear();
}


void TPFFmpegDemuxer::resetTime(int64_t nTime)
{
    if(m_ic->start_time == (int64_t)AV_NOPTS_VALUE || nTime < 0)
    {
        nTime = 0;
    }
    else
    {
        nTime = 1;
    }

    nPcr = nTime;

}
