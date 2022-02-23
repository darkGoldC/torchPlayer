#pragma once
#include "ITPDecoder.h"
#include "TP_CoreDefine.h"
#include "BlockDataQueue.h"
#include "TPInputClock.h"
#include "TPAudioOuput.h"
#include "TPVideoOutput.h"
#include <thread>

class TPCORESHARED_EXPORT TPDecoder : public ITPDecoder
{
public:
    void            decodeThread();
    void            inputDecoderDelete();
    bool            init() override;

    static  TPDecoder *createDecoder(const es_format_t *pFmt);
public:
    BlockDataQueue          m_dataQueue;


    es_format_t             m_inFormat;//输入格式
    es_format_t             m_outFormat;//输出格式
    //允许是否掉帧
    bool                    m_bFrameDropAllowed;
protected:
    TPInputClock            *m_inputClock;//时钟
    int                     m_nLastRate;
    std::thread             m_thread;
    std::atomic_bool        m_bThreadRunning = {false};

    TPDecoder               *m_pPpacketizer;
    bool                    m_bPacketizer;

    int                     m_nExtraPictureBuffers = 0;

    //与其他线程同步
    std::mutex              m_mutex;
    std::condition_variable m_waitRequest;
    std::condition_variable m_waitAcknowledge;
    //std::condition_variable m_waitFifo;
    std::condition_variable m_waitTimeCond;

    //输出
    TPAudioOuput            *m_audioOutput = nullptr;
    TPVideoOutput           *m_videoOutput = nullptr;

    //preroll, 需要加锁
    int64_t                 m_nPrerollEnd;

    //停止时间
    nTime_t                 m_nPauseDate;
    unsigned                m_nFramesCountDown;
    bool                    m_bPaused = false;

    bool                    m_bError;

    //等待标识
    bool                    m_bWaiting = false;
    bool                    m_bFirst = false;
    bool                    m_bHasData = false;

    //刷新
    bool                    m_bFlushing = false;
    bool                    m_bDraining = false;
    std::atomic_bool        m_bDrained = {false};
    bool                    m_bIdle;

    //延时
    nTime_t                 m_nTsDelay;
};

