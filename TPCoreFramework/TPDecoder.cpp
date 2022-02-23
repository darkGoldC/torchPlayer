
#include "TPDecoder.h"
#include "ITPPluginsManager.h"
extern "C"
{
#include<libavcodec/avcodec.h>
}
#include <iostream>
using namespace std;


void TPDecoder::decodeThread()
{

}

void TPDecoder::inputDecoderDelete()
{
    m_bThreadRunning.store(true);
    m_dataQueue.awakeQueue();

    //确保没有等待和编码任何数据
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_bWaiting = false;
        m_waitRequest.notify_one();

        //CHJ 停止视频输出线程
    }

    m_thread.join();
}

bool TPDecoder::init()
{
    return true;
}

TPDecoder *TPDecoder::createDecoder(const es_format_t *pFmt)
{
    InterfacePtr<ITPPluginsManager> pluginsManager;
    TPDecoder *pDecoder =  dynamic_cast<TPDecoder *>(pluginsManager->getInstance("TPFFmpegDecode"));
    if(pDecoder)
    {
        pDecoder->m_bFrameDropAllowed = true;
        pDecoder->m_inFormat = *pFmt;
        pDecoder->m_outFormat.init(pFmt->nCat, 0);

    }

    return pDecoder;
}
