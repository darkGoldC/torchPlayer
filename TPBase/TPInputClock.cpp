#include "TPInputClock.h"
#include <thread>
TPInputClock::TPInputClock(const int nRate)
    :nRate(nRate)
{

}

nTime_t TPInputClock::getWakeup()
{
    nTime_t nWakeUp = INVALID;
    std::lock_guard<std::mutex> locker(m_lock);
    if(bHasReference)
    {
        //nWakeUp
    }

    return nWakeUp;
}

nTime_t TPInputClock::clockStreamToSystem(nTime_t nStream)
{
    std::lock_guard<std::mutex> locker(m_lock);
    if(!bHasReference)
    {
        return INVALID;
    }

    //将流时间转化为真正的系统时间
    return (nStream - this->refPoint.nStream) * nRate /INPUT_RATE_DEFAULT + this->refPoint.nSystem;
}

nTime_t TPInputClock::clockSystemToStream(nTime_t nSystem)
{
    //将系统时间转化为真正的流时间
    std::lock_guard<std::mutex> locker(m_lock);
    return (nSystem - this->refPoint.nSystem) * INPUT_RATE_DEFAULT / this->nRate + this->refPoint.nStream;
}

nTime_t TPInputClock::clockGetTsOffset()
{
    std::lock_guard<std::mutex> locker(m_lock);
    return this->nPtsDelay * (this->nRate - INPUT_RATE_DEFAULT) / INPUT_RATE_DEFAULT;
}

void TPInputClock::inputClockUpdate(bool &bPbLate, bool bCanPaceControl, bool bBufferAllowed, nTime_t nStream, nTime_t nSystem)
{

}
