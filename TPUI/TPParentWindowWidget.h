#ifndef TPPARENTWINDOWWIDGET_H
#define TPPARENTWINDOWWIDGET_H

#include <QWidget>
#include "TP_UIDefine.h"
#include "TPPlayWidget.h"
#include <QStackedWidget>
class TPUISHARED_EXPORT TPParentWindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TPParentWindowWidget(QWidget *parent = nullptr);
    void    initUI();
signals:

private:
    QStackedWidget  *m_stackWidget = Q_NULLPTR;
};

#endif // TPPARENTWINDOWWIDGET_H
