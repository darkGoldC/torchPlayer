#include "TPTopFrameController.h"
#include "ITPPlayController.h"
TPTopFrameController::TPTopFrameController(QObject *parent) : QObject(parent)
{

}

void TPTopFrameController::initController()
{
    InterfacePtr<ITPPlayController> playerController;
    playerController->initController();

    //初始化最顶层窗口
    m_topFrameWidget = new TPTopFrameWidget;
    m_topFrameWidget->initUI();


}

QObject *TPTopFrameController::getObject()
{
    return this;
}

QWidget *TPTopFrameController::getTopWidget()
{
    return m_topFrameWidget;
}
