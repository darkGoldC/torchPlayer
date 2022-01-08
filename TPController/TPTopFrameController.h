#ifndef TPTOPFRAMECONTROLLER_H
#define TPTOPFRAMECONTROLLER_H

#include <QObject>
#include "ITPTopFrameController.h"
#include "TPParentWindowWidget.h"
#include "TPTopFrameWidget.h"
#include "TP_ControllerDefine.h"

class TPCONTROLLERSHARED_EXPORT TPTopFrameController : public QObject, public ITPTopFrameController
{
    Q_OBJECT
public:
    explicit TPTopFrameController(QObject *parent = nullptr);

    void    initController() override;
    QObject *getObject() override;
    QWidget  *getTopWidget() override;
signals:

private:
    TPTopFrameWidget       *m_topFrameWidget = Q_NULLPTR;
};

#endif // TPTOPFRAMECONTROLLER_H
