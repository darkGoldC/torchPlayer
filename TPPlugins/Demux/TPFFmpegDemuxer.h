#ifndef TPFFMPEGDEMUXER_H
#define TPFFMPEGDEMUXER_H
#include "TPDemuxer.h"
#include "ITPPlugin.h"

class TPFFmpegDemuxer : public ITPPlugin, public TPDemuxer
{
public:
    REGISTER(TPFFmpegDemuxer)

    TPFFmpegDemuxer();
    bool    open(const std::string) override;
    bool    init() override;
    bool    demux() override;
};


#endif // TPFFMPEGDEMUXER_H
