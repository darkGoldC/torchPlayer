
#include "TPDemuxer.h"
#include <iostream>


bool TPDemuxer::open(const std::string strUrl)
{
    bool bRet = false;
    m_strUrl = strUrl;

    init();
    return bRet;
}

bool TPDemuxer::control(const int nQuery)
{
    bool bRet = false;

    return bRet;
}
