#ifndef TPFFMPEGDECODE_H
#define TPFFMPEGDECODE_H
#include "TPDecoder.h"
#include "ITPPlugin.h"

class TPFFmpegDecode : public ITPPlugin, public TPDecoder
{
public:
    REGISTER(TPFFmpegDecode)

    TPFFmpegDecode();
    bool            load() override;
    bool            unload() override;
    int             decode(Block_t *p_block) override;
};

#endif // TPFFMPEGDECODE_H
