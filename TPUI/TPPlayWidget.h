#ifndef TPPLAYWIDGET_H
#define TPPLAYWIDGET_H

#include <QWidget>
#include "TP_UIDefine.h"
#include <QSlider>
#include <QVBoxLayout>
#include "ITPVideoWidget.h"
#include <QMouseEvent>
class TPUISHARED_EXPORT TPPlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TPPlayWidget(QWidget *parent = nullptr);

        void initUI();

        //窗口尺寸变化
        void resizeEvent(QResizeEvent *e);


        //双击全屏
        void mouseDoubleClickEvent(QMouseEvent *e);
        void SetPause(bool isPause);
        double getSliderValue();
protected:

public slots:
        void    sltTimeout();

private:
        void    initBottomWidget();
signals:
        void sglOpenFile();
        void sglPlayOrPause();
        void sglSliderChange(const double nValue);

private:
        QSlider     *m_slider = Q_NULLPTR;
        QVBoxLayout *m_vMainLyt = Q_NULLPTR;
        bool        m_bSliderPress = false;
};

#endif // TPPLAYWIDGET_H
