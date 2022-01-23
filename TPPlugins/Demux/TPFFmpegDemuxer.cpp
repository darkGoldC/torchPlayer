#include "TPFFmpegDemuxer.h"



TPFFmpegDemuxer::TPFFmpegDemuxer()
{
    insertClassName("TPFFmpegDemuxer", RegisterTPFFmpegDemuxer::instance());
}

bool TPFFmpegDemuxer::open(const std::string)
{
    return true;
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
