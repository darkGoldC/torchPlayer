#ifndef TPFFMPEGDEMUXER_H
#define TPFFMPEGDEMUXER_H
#include "TPDemuxer.h"
#include "ITPPlugin.h"
#include "TPCommonDefine.h"
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/display.h"
}

typedef  struct _avformat_track_t
{
    es_out_id_t *p_es;
    nTime_t i_pcr;
}avformat_track_t;

class TPFFmpegDemuxer : public ITPPlugin, public TPDemuxer
{
private:
    DECLARE_CLASS(TPFFmpegDemuxer)
public:
    REGISTER(TPFFmpegDemuxer)

    TPFFmpegDemuxer();
    bool    init() override;
    bool    demux() override;

private:
    void    initFfmpeg();
    void    closeDemuxer();

private:
    AVInputFormat       *m_fmt;
    AVFormatContext     *m_ic;
    std::vector<avformat_track_t *> m_vecTracks;

    int64_t             nPcr;
    unsigned            nSsaOrder;
    //input_attachment_t    **attachments;
    //input_title_t         *pTitle;
};

IMPLEMENT_CLASS(TPFFmpegDemuxer)

#endif // TPFFMPEGDEMUXER_H
