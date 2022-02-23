#include "TPEsOut.h"

TPEsOut::TPEsOut()
{

}

void TPEsOut::createEsOut(TPInputManager *pInput)
{
    m_pInput = pInput;

}

es_out_id_t *TPEsOut::esOutAddSlave(const es_format_t *pFmt, es_out_id_t *pMaster)
{
    es_out_id_t *pRetId;

    return pRetId;
}

void TPEsOut::esOutProgramSelect(std::shared_ptr<es_out_pgrm_t> pgrmPtr)
{
    if(m_masterPgrmPtr == pgrmPtr)
    {
        return;
    }

    if(m_masterPgrmPtr)
    {
        qTPDebug() << "unselect pgrm:" << m_masterPgrmPtr->nId;
        for(int nIndex = 0; nIndex < m_vecEs.size(); nIndex++)
        {
            //CHJ 先不考虑es的字幕部分
            if(m_vecEs[nIndex]->pPgrm == m_masterPgrmPtr.get() &&
                    m_vecEs[nIndex]->pDec != NULL && m_nMode != ES_OUT_MODE_ALL)
            {
                m_vecEs[nIndex]->pDec->inputDecoderDelete();
            }
        }
    }
}
