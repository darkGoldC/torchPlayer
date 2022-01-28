#include "TPDataMain.h"
#include "TPValueMgr.h"

TPDataMain::TPDataMain(QObject *parent) : QObject(parent)
{

}

QObject *TPDataMain::getObject()
{
    return this;
}

void TPDataMain::registerObject()
{
    TP_ADDOBJECT_CLASS(ITPValueMgr, TPValueMgr);
}
