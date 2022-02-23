#include "TPFFmpegDemuxer.h"



TPFFmpegDemuxer::TPFFmpegDemuxer()
{

}

bool TPFFmpegDemuxer::init()
{
    bool bRet = false;

    m_ic = avformat_alloc_context();
    if(!m_ic)
    {
        closeDemuxer();
        return false;
    }

    bRet = true;
    return bRet;
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
    }

    //内存情况后续再完善
    m_vecTracks.clear();
}
