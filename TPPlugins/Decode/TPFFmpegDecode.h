#ifndef TPFFMPEGDECODE_H
#define TPFFMPEGDECODE_H
#include "TPDemuxer.h"
#include "ITPPlugin.h"

class TPFFmpegDecode : public ITPPlugin, public TPDemuxer
{
public:
    REGISTER(TPFFmpegDecode)

    TPFFmpegDecode();
    bool    init() override;
    bool    demux() override;
};

#endif // TPFFMPEGDECODE_H
