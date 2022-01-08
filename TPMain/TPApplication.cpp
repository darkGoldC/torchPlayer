#include "TPApplication.h"
#include "ITPTopFrameController.h"
#include "TPCoreFramework.h"
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
    topFrameController->getTopWidget()->show();
}

void TPApplication::initCore()
{
    TP_ADDOBJECT_CLASS(ITPCoreFramework, TPCoreFramework);

    InterfacePtr<ITPCoreFramework> coreFramework;
    coreFramework->initWork();
    coreFramework->startWork();
}
