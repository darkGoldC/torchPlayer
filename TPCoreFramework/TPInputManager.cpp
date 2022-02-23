#include "TPInputManager.h"
#include "ITPPluginsManager.h"
#include<iostream>
#include "TPEventNotify/TPSignalDefCommon.h"
#include "ITPValueMgr.h"

TPInputManager::TPInputManager()
{

}

void TPInputManager::start(const std::string strUrl)
{
    if(!m_pDemuxer)
    {
        InterfacePtr<ITPPluginsManager> pluginsManager;
        ITPDemuxer *pDemuxer =  dynamic_cast<ITPDemuxer *>(pluginsManager->getInstance("TPFFmpegDemuxer"));
        if(pDemuxer)
        {

            InterfacePtr<ITPValueMgr> tpValueMgr;
            tpValueMgr->setValue("inputPlayUrl", strUrl);
            m_pDemuxer.reset(pDemuxer);
            dynamic_cast<ITPPlugin *>(m_pDemuxer.get())->load();
        }
    }

    //test
    //TPEventBindWithNone(signalStartPlay, this, &TPInputManager::inputThread);

    m_thread = std::thread(&TPInputManager::inputThread, this);
}

void TPInputManager::inputThread()
{
    while(true)
    {
        bool bPause = m_bState;
        if(!bPause)
        {

        }

    }
}
