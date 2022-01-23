#ifndef GLVIDEOOUTPUT_H
#define GLVIDEOOUTPUT_H
#include "TPDemuxer.h"
#include "ITPPlugin.h"

class GlVideoOutput : public ITPPlugin, public TPDemuxer
{
public:
    REGISTER(GlVideoOutput)
    GlVideoOutput();

    bool    init() override;
    bool    demux() override;
};

#endif // GLVIDEOOUTPUT_H
