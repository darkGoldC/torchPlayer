#ifndef TPINPUTMANAGER_H
#define TPINPUTMANAGER_H
#include "ITPDemuxer.h"
#include <memory>
#include <thread>
#include <QObject>

typedef enum input_state_e
{
    INIT_S = 0,
    OPENING_S,
    PLAYING_S,
    PAUSE_S,
    END_S,
    ERROR_S,
} input_state_e;

class TPInputManager : public QObject
{
public:
    TPInputManager();
    void            start(const std::string strUrl);

private:
    void            inputThread();
private:
    std::shared_ptr<ITPDemuxer> m_pDemuxer;
    std::thread     m_thread;

    bool            m_bState = false;
};

#endif // TPINPUTMANAGER_H
