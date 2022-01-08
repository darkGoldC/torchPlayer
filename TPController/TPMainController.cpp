#include "TPMainController.h"
#include "TPInterfacePtr.h"
#include "TPTopFrameController.h"
#include "TPPlayController.h"

TPMainController::TPMainController(QObject *parent) : QObject(parent)
{

}

void TPMainController::install()
{
    //顶层窗口
    TP_ADDOBJECT_CLASS(ITPTopFrameController, TPTopFrameController);

    //播放器窗口
    TP_ADDOBJECT_CLASS(ITPPlayController, TPPlayController);
}
