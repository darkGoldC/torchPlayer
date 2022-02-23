#ifndef TPSIGNALDEFCOMMON_H
#define TPSIGNALDEFCOMMON_H

#include "TPEventHeader.h"
#include "TP_BaseDefine.h"
#include "TPUIData.h"

#include <QPair>
//example
TPBASESHARED_EXPORT extern TPSignal<>                   signalStartPlay;
TPBASESHARED_EXPORT extern TPSignal<const EUIEventType> signalUIEventPost;
#endif //
