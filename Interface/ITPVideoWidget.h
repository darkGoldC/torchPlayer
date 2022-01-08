#pragma once

#include <QObject>
#include "TP_CoreDefine.h"
struct AVFrame;


class ITPVideoWidget
{
public:
    /**
    * @brief                设置宽高
    * @author               chj
    * @date                 2021-07-25
    * @param
    * @return
    */
    virtual void    Init(int width, int height) = 0;

    /**
    * @brief                刷新视频界面
    * @author               chj
    * @date                 2021-07-25
    * @param
    * @return
    */
    virtual void    Repaint(AVFrame *frame) = 0;

    /**
    * @brief                返回视频窗口
    * @author               chj
    * @date                 2021-07-25
    * @param
    * @return
    */
    virtual QWidget *getVideoWidget() = 0;

};

extern TPCORESHARED_EXPORT ITPVideoWidget *g_pVideoWidget;
