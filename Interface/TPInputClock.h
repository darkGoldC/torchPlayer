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
}STAverage;

class TPInputClock
{
public:
    TPInputClock(const int nRate);

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
    std::mutex      m_lock;
    //最后的输入时间
    STclockPoint    lastPoint;
    nTime_t         nTsMax = INVALID;
    //总共的额外缓冲时间
    nTime_t         nBuffering_duration = INVALID;
    //下一次更新时间
    nTime_t         m_nextDriftUpdate = INVALID;
    STAverage       drift;

    struct
    {
        nTime_t     pi_value[INPUT_CLOCK_LATE_COUNT] = {INVALID};
        unsigned    nIndex = INVALID;
    }late;

    //最新的参考时间
    STclockPoint    refPoint;
    //是否重置
    bool            bHasReference = false;

    //外部的时间
    nTime_t         nExternalClock      = INVALID;
    bool            bHasExternalClock   = false;

    //当前修改
    bool            bPaused = false;
    int             nRate;
    nTime_t         nPtsDelay   = INVALID;
    nTime_t         nPauseDate  = INVALID;
};

#endif // TPINPUTCLOCK_H
