#include "TPInputClock.h"
#include <thread>
#include "TPCommonDefine.h"
TPInputClock::TPInputClock(const int nRate)
    :m_nRate(nRate)
{

}

nTime_t TPInputClock::getWakeup()
{
    nTime_t nWakeUp = INVALID;
    std::lock_guard<std::mutex> locker(m_lock);
    if(m_bHasReference)
    {
        //nWakeUp
    }

    return nWakeUp;
}

nTime_t TPInputClock::clockStreamToSystem(nTime_t nStream)
{
    std::lock_guard<std::mutex> locker(m_lock);
    if(!m_bHasReference)
    {
        return INVALID;
    }

    //将流时间转化为真正的系统时间
    return (nStream - this->m_refPoint.nStream) * m_nRate /INPUT_RATE_DEFAULT + this->m_refPoint.nSystem;
}

nTime_t TPInputClock::clockSystemToStream(nTime_t nSystem)
{
    //将系统时间转化为真正的流时间
    std::lock_guard<std::mutex> locker(m_lock);
    return (nSystem - this->m_refPoint.nSystem) * INPUT_RATE_DEFAULT / this->m_nRate + this->m_refPoint.nStream;
}

nTime_t TPInputClock::clockGetTsOffset()
{
    std::lock_guard<std::mutex> locker(m_lock);
    return this->m_nPtsDelay * (this->m_nRate - INPUT_RATE_DEFAULT) / INPUT_RATE_DEFAULT;
}

STclockPoint TPInputClock::clockPointCreate( nTime_t nStream, nTime_t nSystem )
{
    STclockPoint p = { nStream, nSystem };
    return p;
}

void TPInputClock::inputClockUpdate(bool &bPbLate, bool bCanPaceControl, bool bBufferAllowed, nTime_t nStream, nTime_t nSystem)
{
    bool b_reset_reference = false;

    assert( nStream > INVALID && nSystem > INVALID );

    std::lock_guard<std::mutex> locker(m_lock);

    if(!m_bHasReference)
    {
        b_reset_reference= true;
    }
    else if( m_lastPoint.nStream > INVALID &&
             ( (m_lastPoint.nStream - nStream) > CR_MAX_GAP ||
               (m_lastPoint.nStream - nStream) < -CR_MAX_GAP ) )
    {

        qTPWarning() << "clock gap, unexpected stream discontinuity" ;
        m_nTsMax = INVALID;

        /* */
        qTPWarning() << "feeding synchro with a new reference point trying to recover from clock gap";
        b_reset_reference= true;
    }

    /* */
    if( b_reset_reference )
    {
        m_nextDriftUpdate = INVALID;
        //重置diff
        m_drift.reset();

        m_bHasReference = true;
        m_refPoint = clockPointCreate( nStream,
                                      __MAX( m_nTsMax + CR_MEAN_PTS_GAP, nSystem ) );
        m_bHasExternalClock = false;
    }

    if( !bCanPaceControl && m_nextDriftUpdate < nSystem )
    {
        const nTime_t i_converted = clockSystemToStream(nSystem);

        m_drift.avgUpdate(i_converted - nStream);

        m_nextDriftUpdate = nSystem + CLOCK_FREQ/5; /* FIXME why that */
    }

    if( !bCanPaceControl || b_reset_reference )
    {
        m_nBuffering_duration = 0;
    }
    else if( bBufferAllowed )
    {
        /* Try to bufferize more than necessary by reading
         * CR_BUFFERING_RATE/256 faster until we have CR_BUFFERING_TARGET.
         */
        const nTime_t i_duration = __MAX( nStream - m_lastPoint.nStream, 0 );

        m_nBuffering_duration += ( i_duration * CR_BUFFERING_RATE + 255 ) / 256;
        if( m_nBuffering_duration > CR_BUFFERING_TARGET )
            m_nBuffering_duration = CR_BUFFERING_TARGET;
    }
    //fprintf( stderr, "input_clock_Update: %d :: %lld\n", b_buffering_allowed, cl->i_buffering_duration/1000 );

    /* */
    m_lastPoint = clockPointCreate(nStream, nSystem);

    const nTime_t i_system_expected = clockStreamToSystem(nStream + m_drift.nValue );
    const nTime_t i_late = ( nSystem - m_nPtsDelay ) - i_system_expected;
    bPbLate = i_late > 0;
    if( i_late > 0 )
    {
        late.pi_value[late.nIndex] = i_late;
        late.nIndex = ( late.nIndex + 1 ) % INPUT_CLOCK_LATE_COUNT;
    }
}
