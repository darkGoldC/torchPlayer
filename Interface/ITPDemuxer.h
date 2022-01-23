#ifndef ITPDemuxer_H
#define ITPDemuxer_H
#include <iostream>

typedef struct _STDemux_info
{
    int nTitle;
    int nSeekPoint;
}STDemux_info;

class ITPDemuxer
{
public:
    virtual bool    open(const std::string) = 0;
    virtual bool    init() = 0;
    virtual bool    demux() = 0;
    virtual bool    control(const int nQuery) = 0;
};

#endif
