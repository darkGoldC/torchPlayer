#ifndef TPFFMPEGDEMUXER_H
#define TPFFMPEGDEMUXER_H
#include "TPDemuxer.h"
#include "ITPPlugin.h"

class TPFFmpegDemuxer : public ITPPlugin, public TPDemuxer
{
private:
    DECLARE_CLASS(TPFFmpegDemuxer)
public:
    REGISTER(TPFFmpegDemuxer)

    TPFFmpegDemuxer();
    bool    init() override;
    bool    demux() override;
};

IMPLEMENT_CLASS(TPFFmpegDemuxer)

#endif // TPFFMPEGDEMUXER_H
