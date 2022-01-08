#include "TPPlayController.h"
#include "ITPCoreFramework.h"
#include <QFileDialog>
#include "ITPVideoWidget.h"
TPPlayController::TPPlayController(QWidget *parent) : QWidget(parent)
{

}

QObject *TPPlayController::getObject()
{
    return this;
}

void TPPlayController::initController()
{
    m_playWidget = new TPPlayWidget;
    m_playWidget->initUI();

    connect(m_playWidget, &TPPlayWidget::sglOpenFile, this, &TPPlayController::sltOpenFile);
    connect(m_playWidget, &TPPlayWidget::sglPlayOrPause, this, &TPPlayController::sltPlayOrPause);
    connect(m_playWidget, &TPPlayWidget::sglSliderChange, this, &TPPlayController::sltSliderChange);
}

QWidget *TPPlayController::getWidget()
{
    return m_playWidget;
}

void TPPlayController::sltOpenFile()
{
    QString name = QFileDialog::getOpenFileName(m_playWidget, "选择视频文件");
    if (name.isEmpty())return;
    this->setWindowTitle(name);

    InterfacePtr<ITPCoreFramework> coreFramework;
    if (!coreFramework->openVideo(name, g_pVideoWidget))
    {
        return;
    }
    coreFramework->pauseWork();
}

void TPPlayController::sltPlayOrPause()
{
    InterfacePtr<ITPCoreFramework> coreFramework;
    coreFramework->pauseWork();
}

void TPPlayController::sltSliderChange(const double value)
{
    double pos = 0.0;
    pos = m_playWidget->getSliderValue();
    InterfacePtr<ITPCoreFramework> coreFramework;
    coreFramework->seekProcess(value);
}
