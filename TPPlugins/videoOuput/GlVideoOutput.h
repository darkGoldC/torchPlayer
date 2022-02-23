#ifndef GLVIDEOOUTPUT_H
#define GLVIDEOOUTPUT_H
#include "TPVideoOutput.h"
#include "ITPPlugin.h"

class GlVideoOutput : public ITPPlugin, public TPVideoOutput
{
public:
    REGISTER(GlVideoOutput)
    GlVideoOutput();

    bool            load() override;
    bool            unload() override;
};

#endif // GLVIDEOOUTPUT_H
