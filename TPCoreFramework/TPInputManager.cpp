#include "TPInputManager.h"
#include "ITPPluginsManager.h"
#include<iostream>
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


    m_thread = std::thread(&TPInputManager::inputThread, this);
}

void TPInputManager::inputThread()
{
    while(true)
    {

    }
}
