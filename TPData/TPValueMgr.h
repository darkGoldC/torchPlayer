#ifndef TPVALUEMGR_H
#define TPVALUEMGR_H

#include <QObject>
#include <map>
#include <mutex>
#include "ITPValueMgr.h"

class TPValueMgr : public QObject, public ITPValueMgr
{
    Q_OBJECT
public:
    TPValueMgr();

    QObject *getObject() override;
    void    setValue(const std::string &strName, const std::any &value);
    std::any getValue(const std::string &strName);
private:
    std::map<std::string, std::any> m_mapValue;
    std::mutex  m_mutex;
};

#endif // TPVALUEMGR_H
