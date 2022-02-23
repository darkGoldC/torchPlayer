#include <thread>
#include "TPValueMgr.h"

TPValueMgr::TPValueMgr()
{

}

QObject *TPValueMgr::getObject()
{
    return this;
}

void TPValueMgr::setValue(const std::string &strName, const std::any &value)
{
    std::lock_guard lock(m_mutex);
    m_mapValue.insert(std::make_pair(strName, value));
}

std::any TPValueMgr::getValue(const std::string &strName)
{
    std::lock_guard lock(m_mutex);
    std::any retAny;
    auto iter = m_mapValue.find(strName);
    if(iter != m_mapValue.end())
    {
        retAny = iter->second;
    }

    return retAny;
}
