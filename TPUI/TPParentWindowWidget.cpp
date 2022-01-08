#include "TPParentWindowWidget.h"
#include "ITPPlayController.h"
#include "TPInterfacePtr.h"
#include <QHBoxLayout>
TPParentWindowWidget::TPParentWindowWidget(QWidget *parent) : QWidget(parent)
{

}

void TPParentWindowWidget::initUI()
{
    QHBoxLayout *mainLyt = new QHBoxLayout;
    if(m_stackWidget == Q_NULLPTR)
    {
        m_stackWidget = new QStackedWidget(this);
        mainLyt->addWidget(m_stackWidget);
    }


    {
        InterfacePtr<ITPPlayController> playController;
        QWidget *playWidget = playController->getWidget();

        m_stackWidget->addWidget(playWidget);
        m_stackWidget->setCurrentWidget(playWidget);
    }

    this->setLayout(mainLyt);
}
