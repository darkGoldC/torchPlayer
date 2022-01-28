#include "TPApplication.h"
#include "ITPTopFrameController.h"
#include "TPCoreFramework.h"
#include "TPPluginsManager.h"
bool TPApplication::notify(QObject *reciver, QEvent *e)
{
    return QApplication::notify(reciver, e);
}

TPApplication::TPApplication(int &argc, char **argv) : QApplication(argc, argv)
{

}

void TPApplication::initController()
{
    TPMainController   *mainController = new TPMainController;
    mainController->install();
}

void TPApplication::initUI()
{
    InterfacePtr<ITPTopFrameController> topFrameController;
    topFrameController->initController();
    //topFrameController->getTopWidget()->show();
}

void TPApplication::initCore()
{
    TP_ADDOBJECT_CLASS(ITPCoreFramework, TPCoreFramework);

    InterfacePtr<ITPCoreFramework> coreFramework;
    coreFramework->initWork();
    coreFramework->startWork();

    //插件初始化
    TP_ADDOBJECT_CLASS(ITPPluginsManager, TPPluginsManager);
    InterfacePtr<ITPPluginsManager> pluginsManager;
    pluginsManager->loadAllPlugins("");
}
