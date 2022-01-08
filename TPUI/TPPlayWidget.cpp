#include "TPPlayWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include "ITPVideoWidget.h"
#include "TPInterfacePtr.h"
#include "ITPCoreFramework.h"

TPPlayWidget::TPPlayWidget(QWidget *parent) : QWidget(parent)
{

}

void TPPlayWidget::initUI()
{
    m_vMainLyt = new QVBoxLayout;
    m_vMainLyt->setMargin(0);
    m_vMainLyt->setSpacing(0);

    QWidget *titleWidget = new QWidget;
    titleWidget->setObjectName("titleWidget");
    titleWidget->setFixedHeight(60);
    m_vMainLyt->addWidget(titleWidget);

    QWidget *videoWidget = g_pVideoWidget->getVideoWidget();
    m_vMainLyt->addWidget(videoWidget);

    //初始化底部控件
    initBottomWidget();

    this->setLayout(m_vMainLyt);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TPPlayWidget::sltTimeout);

    timer->start(40);
}


//双击全屏
void TPPlayWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (isFullScreen())
        this->showNormal();
    else
        this->showFullScreen();
}

double TPPlayWidget::getSliderValue()
{
    double pos = 0.0;
    pos = (double)m_slider->value() / (double)m_slider->maximum();
    return pos;
}

void TPPlayWidget::sltTimeout()
{
    if(m_bSliderPress)
    {
        return;
    }
    InterfacePtr<ITPCoreFramework> coreFramework;

    double nvalue = coreFramework->getProcess();
    if(nvalue > 0.0)
    {
        m_slider->setValue(nvalue * m_slider->maximum());
    }

}
//窗口尺寸变化
void TPPlayWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void TPPlayWidget::initBottomWidget()
{
    m_slider = new QSlider;
    m_slider->setMaximum(1000);
    connect(m_slider, &QSlider::sliderPressed, [this](){
       m_bSliderPress = true;
    });

    connect(m_slider, &QSlider::sliderReleased, [this](){
       m_bSliderPress = false;
       emit sglSliderChange(m_slider->value()/1000.0);
    });

    m_slider->setOrientation(Qt::Orientation::Horizontal);
    m_vMainLyt->addWidget(m_slider);

    QWidget *bottomWidget = new QWidget;
    bottomWidget->setObjectName("bottomWidget");

    QHBoxLayout *hBottomLyt = new QHBoxLayout;
    hBottomLyt->setMargin(0);
    hBottomLyt->setSpacing(0);

    QPushButton *openBtn = new QPushButton;
    openBtn->setText("打开");
    openBtn->setObjectName("openFileBtn");
    connect(openBtn, &QPushButton::clicked, this, &TPPlayWidget::sglOpenFile);

    QPushButton *playPauseBtn = new QPushButton;
    playPauseBtn->setText("暂停");
    playPauseBtn->setObjectName("playPauseBtn");
    connect(playPauseBtn, &QPushButton::clicked, this, &TPPlayWidget::sglPlayOrPause);

    hBottomLyt->addWidget(openBtn);
    hBottomLyt->addWidget(playPauseBtn);
    bottomWidget->setLayout(hBottomLyt);

    m_vMainLyt->addWidget(bottomWidget);
}
