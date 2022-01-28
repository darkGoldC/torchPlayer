#ifndef TPINPUTCLOCK_H
#define TPINPUTCLOCK_H
#include <iostream>
#include <mutex>
#include "TPCommonDefine.h"

#define INPUT_CLOCK_LATE_COUNT 3
#define INPUT_RATE_DEFAULT  1000

typedef struct
{
    nTime_t nStream = INVALID;
    nTime_t nSystem = INVALID;
}STclockPoint;

typedef struct
{
    nTime_t nValue      = INVALID;
    int     nResidue    = INVALID;//剩余数
    int     nCount      = INVALID;
    int     nDivider    = 10;//除法

    void    reset()
    {
        nValue = 0;
        nResidue = 0;
        nCount = 0;
    }

    void avgUpdate(nTime_t i_value )
    {
        const int i_f0 = __MIN( nDivider - 1, nCount );
        const int i_f1 = nDivider - i_f0;

        const nTime_t i_tmp = i_f0 * nValue + i_f1 * i_value + nResidue;

        nValue   = i_tmp / nDivider;
        nResidue = i_tmp % nDivider;

        nCount++;
    }

}STAverage;

class TPInputClock
{
public:
    TPInputClock(const int m_nRate);

    nTime_t getWakeup();
    //将流时间转化为真正的系统时间
    nTime_t clockStreamToSystem(nTime_t nStream);
    //将系统时间转化为真正的流时间
    nTime_t clockSystemToStream(nTime_t nSystem);

    //获取流偏移位置
    nTime_t clockGetTsOffset();

    //时间更新
    void    inputClockUpdate(bool &bPbLate, bool bCanPaceControl, bool bBufferAllowed,
                             nTime_t nStream, nTime_t nSystem);
private:
    STclockPoint clockPointCreate(nTime_t nStream, nTime_t nSystem);

private:
    std::mutex      m_lock;
    //最后的输入时间
    STclockPoint    m_lastPoint;
    nTime_t         m_nTsMax = INVALID;
    //总共的额外缓冲时间
    nTime_t         m_nBuffering_duration = INVALID;
    //下一次更新时间
    nTime_t         m_nextDriftUpdate = INVALID;
    STAverage       m_drift;

    struct
    {
        nTime_t     pi_value[INPUT_CLOCK_LATE_COUNT] = {INVALID};
        unsigned    nIndex = INVALID;
    }late;

    //最新的参考时间
    STclockPoint    m_refPoint;
    //是否重置
    bool            m_bHasReference = false;

    //外部的时间
    nTime_t         m_nExternalClock      = INVALID;
    bool            m_bHasExternalClock   = false;

    //当前修改
    bool            m_bPaused = false;
    int             m_nRate;
    nTime_t         m_nPtsDelay   = INVALID;
    nTime_t         m_nPauseDate  = INVALID;

};

#endif // TPINPUTCLOCK_H
