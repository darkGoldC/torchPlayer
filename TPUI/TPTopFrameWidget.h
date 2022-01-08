#ifndef TPTopFrameWidget_H
#define TPTopFrameWidget_H

#include <QWidget>
#include <QStackedWidget>
#include "TPParentWindowWidget.h"
#include "TP_UIDefine.h"

/**
    * @brief                最顶层窗口
    * @author
    * @date                 2021-07-25
    * @param
    * @return
    */

class TPUISHARED_EXPORT TPTopFrameWidget : public QWidget
{
    Q_OBJECT

public:
    TPTopFrameWidget(QWidget *parent = nullptr);
    ~TPTopFrameWidget();

    void    initUI();

private:

    TPParentWindowWidget   *m_windowWidget =  Q_NULLPTR;//所有子控件的父窗口
    QStackedWidget          *m_stackWidget = Q_NULLPTR;//为后续增加别的同级界面做扩展
};
#endif // WIDGET_H
