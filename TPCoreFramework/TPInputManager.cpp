#include "TPInputManager.h"
#include "ITPPluginsManager.h"
#include<iostream>
#include "TPEventNotify/TPSignalDefCommon.h"
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
            m_pDemuxer.reset(pDemuxer);
            m_pDemuxer->open(strUrl);
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
