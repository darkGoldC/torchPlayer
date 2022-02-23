
#include "TPDemuxer.h"
#include <iostream>

bool TPDemuxer::init(const std::string strUrl)
{
    bool bRet = false;
    m_strUrl = strUrl;

    return true;
}

bool TPDemuxer::control(const int nQuery)
{
    bool bRet = false;

    return bRet;
}
