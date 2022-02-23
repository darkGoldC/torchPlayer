#ifndef TPESOUT_H
#define TPESOUT_H
#include "TPInputClock.h"
#include "TPInputManager.h"
#include "ITPEs_out.h"
#include "TPDecoder.h"
#include "TP_CoreDefine.h"

enum es_out_mode_e
{
    ES_OUT_MODE_NONE,   /* don't select anything */
    ES_OUT_MODE_ALL,    /* eg for stream output */
    ES_OUT_MODE_AUTO,   /* best audio/video or for input follow audio-track, sub-track */
    ES_OUT_MODE_PARTIAL,/* select programs given after --programs */
    ES_OUT_MODE_END     /* mark the es_out as dead */
};

typedef struct _es_out_pgrm_t
{
    int nId;
    int nEs;
    bool    bSelected;//当前是否使用
    bool    bScrambled;//攀登

    TPInputClock *p_clock;
    //元信息，暂时不处理
}es_out_pgrm_t;

typedef struct _es_out_id_t
{
    int nId;//es id
    es_out_pgrm_t *pPgrm;

    bool            bScrambled;//攀登
    int             nChannel;//第几个通道
    es_format_t     fmt;//es格式
    std::string     language;//

    TPDecoder       *pDec;
    TPDecoder       *pDecRecord;

    //字幕部分
    struct{
       int  nType;
       int  nBitmap;
       _es_out_id_t  *pp_es[64];
    }cc;
    _es_out_id_t      *pMaster;
    int               nMetaId;//元属性id
}es_out_id_t;

enum es_out_policy_e
{
    ES_OUT_ES_POLICY_EXCLUSIVE = 0,/* Enforces single ES selection only */
    ES_OUT_ES_POLICY_SIMULTANEOUS, /* Allows multiple ES per cat */
};

typedef struct
{
    int         i_count;    /* es count */
    es_out_id_t *p_main_es; /* current main es */
    enum es_out_policy_e e_policy;

    /* Parameters used for es selection */
    bool        b_autoselect; /* if we want to select an es when no user prefs */
    int         i_id;       /* es id as set by es fmt.id */
    int         i_demux_id; /* same as previous, demuxer set default value */
    int         i_channel;  //es 创建的顺序数
    std::vector<std::string> sz_language;
} es_out_es_props_t;

class TPCORESHARED_EXPORT TPEsOut
{
public:
    TPEsOut();
    void  createEsOut(TPInputManager *pInput);
    //创建一个新的esid
    es_out_id_t *esOutAddSlave(const es_format_t *pFmt, es_out_id_t *pMaster);
    //es选择节目单
    void        esOutProgramSelect(std::shared_ptr<es_out_pgrm_t> pgrmPtr);
private:
    TPInputManager  *m_pInput = Q_NULLPTR;
    /* all programs */
    std::vector<std::shared_ptr<es_out_pgrm_t>> m_vecPgrm;
    std::shared_ptr<es_out_pgrm_t>              m_masterPgrmPtr;  /* Master program */

    //all es
    int                         m_nId;
    std::vector<es_out_id_t *>  m_vecEs;

    //mode
    bool                        m_bActive;
    int                         m_nMode;

    es_out_es_props_t           m_video, m_audio, m_sub;
    int                         m_nGroupId;//es/group to select;

    //delay
    int                         m_nAudioDelay;//音频延迟
    int                         m_nSpuDelay;//字幕延迟


    /* Clock configuration */
    nTime_t     m_nPts_delay;
    nTime_t     m_nPts_jitter;
    int         m_nCr_average;
    int         m_nRate;

    /* */
    bool        m_bPaused;
    nTime_t     m_nPause_date;

    /* Current preroll */
    nTime_t     m_nPreroll_end;

    /* Used for buffering */
    bool        m_bBuffering;
    nTime_t     m_nBuffering_extra_initial;
    nTime_t     m_nBuffering_extra_stream;
    nTime_t     m_nBuffering_extra_system;
private:

};

#endif // TPESOUT_H
