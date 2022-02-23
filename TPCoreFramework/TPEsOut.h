#ifndef TPESOUT_H
#define TPESOUT_H
#include "TPInputClock.h"
#include "TPInputManager.h"
#include "ITPEs_out.h"
#include "TPDecoder.h"
#include "TP_CoreDefine.h"

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

private:
    TPInputManager  *m_pInput = Q_NULLPTR;
    /* all programs */
    int           i_pgrm;
    es_out_pgrm_t **pgrm;
    es_out_pgrm_t *p_pgrm;  /* Master program */

    //all es
    int                         nId;
    int                         nEs;
    std::vector<es_out_id_t *>  vecEs;

    //mode
    bool                        bActive;
    int                         nMode;

    es_out_es_props_t           video, audio, sub;
    int                         nGroupId;//es/group to select;

    //delay
    int                         nAudioDelay;//音频延迟
    int                         nSpuDelay;//字幕延迟


    /* Clock configuration */
    nTime_t     i_pts_delay;
    nTime_t     i_pts_jitter;
    int         i_cr_average;
    int         i_rate;

    /* */
    bool        b_paused;
    nTime_t     i_pause_date;

    /* Current preroll */
    nTime_t     i_preroll_end;

    /* Used for buffering */
    bool        b_buffering;
    nTime_t     i_buffering_extra_initial;
    nTime_t     i_buffering_extra_stream;
    nTime_t     i_buffering_extra_system;
private:

};

#endif // TPESOUT_H
