#include "TPGlobalInfoMgr.h"
#include "TPLog.h"
#include "TPApplication.h"

int main(int argc, char *argv[])
{
    TPApplication a(argc, argv);

    g_log.initLog(true, "/log/Player");
    qTPInfo() << "begin";
    TPGlobalInfoMgr::getInstance()->initPath();

    a.initCore();
    a.initController();
    a.initUI();

    return a.exec();
}
