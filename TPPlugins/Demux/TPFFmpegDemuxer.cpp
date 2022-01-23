#include "TPFFmpegDemuxer.h"



TPFFmpegDemuxer::TPFFmpegDemuxer()
{
    insertClassName("TPFFmpegDemuxer", RegisterTPFFmpegDemuxer::instance());
}

bool TPFFmpegDemuxer::init()
{
    bool bRet = false;

    bRet = true;
    return bRet;
}

bool TPFFmpegDemuxer::demux()
{
    bool bRet = false;

    return bRet;
}
