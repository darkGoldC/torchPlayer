#ifndef TPPLAYCONTROLLER_H
#define TPPLAYCONTROLLER_H

#include <QWidget>
#include "TPPlayWidget.h"
#include "ITPPlayController.h"
#include "TP_ControllerDefine.h"
#include "TPPlayWidget.h"

class TPCONTROLLERSHARED_EXPORT TPPlayController : public QWidget, public ITPPlayController
{
    Q_OBJECT
public:
    explicit TPPlayController(QWidget *parent = nullptr);

    QObject *getObject() override;
    void    initController() override;
    QWidget *getWidget() override;
signals:

public slots:
    void    sltOpenFile();
    void    sltPlayOrPause();
    void    sltSliderChange(const double value);

private:
    TPPlayWidget    *m_playWidget = Q_NULLPTR;
};

#endif // TPPLAYCONTROLLER_H
