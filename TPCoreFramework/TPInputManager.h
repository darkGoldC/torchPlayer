#ifndef TPINPUTMANAGER_H
#define TPINPUTMANAGER_H
#include "ITPDemuxer.h"
#include <memory>
#include <thread>

class TPInputManager
{
public:
    TPInputManager();
    void            start(const std::string strUrl);

private:
    void            inputThread();
private:
    std::shared_ptr<ITPDemuxer> m_pDemuxer;
    std::thread     m_thread;
};

#endif // TPINPUTMANAGER_H
