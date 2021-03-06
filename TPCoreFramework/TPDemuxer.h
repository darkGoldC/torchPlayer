#ifndef TPDemuxer_H
#define TPDemuxer_H

#include "ITPDemuxer.h"
#include <mutex>
#include "TPEsOut.h"
#include "TP_CoreDefine.h"

class  TPCORESHARED_EXPORT TPDemuxer : public ITPDemuxer
{
public:
    bool    init(const std::string strUrl) override;
    bool    control(const int nQuery) override;

private:
    TPEsOut         *m_esOut = nullptr;
    STDemux_info    m_demuxInfo;
    std::string     m_strUrl;
};

#endif
