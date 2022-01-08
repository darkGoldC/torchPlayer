#include "TPGlobalInfoMgr.h"
#include <QDir>
#include <QApplication>
#include "TPCommonUtils.h"

TPGlobalInfoMgr::TPGlobalInfoMgr(QObject *parent) : QObject(parent)
{

}

TPGlobalInfoMgr *TPGlobalInfoMgr::getInstance()
{
       static TPGlobalInfoMgr pathMgr;
       return &pathMgr;
}

void TPGlobalInfoMgr::initPath()
{
    QString strCurPath = QApplication::applicationDirPath();

    m_strLogPath = strCurPath + "/log";
    TPCommonUtils::makeDir(m_strLogPath);
}

QString TPGlobalInfoMgr::getLongPath()
{
    return m_strLogPath;
}

TPInterfaceMgr *TPGlobalInfoMgr::getObjectMgr()
{
    static TPInterfaceMgr    objectMgr;
    return &objectMgr;
}
