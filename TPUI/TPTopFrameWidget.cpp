#include "TPTopFrameWidget.h"
#include <QHBoxLayout>

TPTopFrameWidget::TPTopFrameWidget(QWidget *parent)
    : QWidget(parent)
{
}

TPTopFrameWidget::~TPTopFrameWidget()
{
}

void TPTopFrameWidget::initUI()
{
    QHBoxLayout *mainLyt = new QHBoxLayout;
    m_windowWidget = new TPParentWindowWidget;
    m_windowWidget->initUI();

    m_stackWidget = new QStackedWidget;

    m_stackWidget->addWidget(m_windowWidget);
    mainLyt->addWidget(m_stackWidget);
    m_stackWidget->setCurrentWidget(m_windowWidget);

    this->setLayout(mainLyt);
}

