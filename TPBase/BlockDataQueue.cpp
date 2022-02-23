#include "BlockDataQueue.h"
#include <chrono>
#include <ctime>
using namespace std::chrono;

BlockDataQueue::BlockDataQueue()
{

}

void BlockDataQueue::awakeQueue()
{
    m_waitCond.notify_one();
}

void BlockDataQueue::queueWait()
{
    std::unique_lock<std::mutex> lck (m_mutex);
    m_waitCond.wait(lck);
}

bool BlockDataQueue::queueWait(const long long nTime)
{
    std::unique_lock<std::mutex> lck (m_mutex);
    bool bRet = false;
    //大括号赋值需要注意
    time_point<system_clock,microseconds> tp_mseconds(microseconds{nTime});

    bRet = m_waitCond.wait_until(lck, tp_mseconds) == std::cv_status::timeout;

    return bRet;
}

void BlockDataQueue::flushClearQueue()
{
    std::unique_lock<std::mutex> lck (m_mutex);

    std::queue<std::shared_ptr<Block_t>> tempQueue;
    m_blockQueue.swap(tempQueue);
    m_waitCond.notify_one();
}

void BlockDataQueue::pushBlock(const std::shared_ptr<Block_t> block)
{
    std::unique_lock<std::mutex> lck (m_mutex);
    m_blockQueue.push(block);

    m_waitCond.notify_one();
}

void BlockDataQueue::pushBlock(const std::vector<std::shared_ptr<Block_t> > &vecBlock)
{
    std::unique_lock<std::mutex> lck (m_mutex);
    for(auto iter : vecBlock)
    {
        m_blockQueue.push(iter);
    }

    m_waitCond.notify_one();
}

std::shared_ptr<Block_t> BlockDataQueue::popBlock()
{
    std::unique_lock<std::mutex> lck (m_mutex);
    std::shared_ptr<Block_t> pBlock;

    if(!m_blockQueue.empty())
    {
        pBlock = m_blockQueue.front();
        m_blockQueue.pop();
    }

    return pBlock;
}

std::shared_ptr<Block_t> BlockDataQueue::topBlock()
{
    std::unique_lock<std::mutex> lck (m_mutex);
    std::shared_ptr<Block_t> pBlock;

    if(!m_blockQueue.empty())
    {
        pBlock = m_blockQueue.front();
    }

    return pBlock;
}
