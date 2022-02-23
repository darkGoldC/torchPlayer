#ifndef BLOCKDATAQUEUE_H
#define BLOCKDATAQUEUE_H
#include "BlockData.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <memory>
#include "TP_BaseDefine.h"

class TPBASESHARED_EXPORT BlockDataQueue
{
public:
    BlockDataQueue();
    //唤醒队列
    void    awakeQueue();
    //队列等待数据
    void    queueWait();
    //队列超时等待
    bool    queueWait(const long long nTime);
    //清空队列
    void    flushClearQueue();

    //往队列里压入数据
    void    pushBlock(const std::shared_ptr<Block_t> block);
    void    pushBlock(const std::vector<std::shared_ptr<Block_t>> &vecBlock);

    //往队列里取数据
    std::shared_ptr<Block_t> popBlock();
    std::shared_ptr<Block_t> topBlock();
private:
    std::mutex m_mutex;
    std::condition_variable m_waitCond;//等待数据
    std::queue<std::shared_ptr<Block_t>>     m_blockQueue;//块数据队列
};

#endif // BLOCKDATAFIFO_H
