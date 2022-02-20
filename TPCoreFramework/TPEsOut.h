#ifndef TPESOUT_H
#define TPESOUT_H
#include "TPInputClock.h"
#include "TPInputManager.h"
typedef struct
{
    int nId;
    int nEs;
    bool    bSelected;//当前是否使用
    bool    bScrambled;

    TPInputClock *p_clock;

}es_out_pgrm_t;

class TPEsOut
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
