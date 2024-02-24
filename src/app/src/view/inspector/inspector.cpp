#include "inspector.h"

#include "view/inspector/component/components/test.h"
#include <QErrorMessage>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

Inspector::Inspector(QWidget* pParent)
    : QDockWidget(tr("Inspector"), pParent)
{
    this->setObjectName("inspector");
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setStyleSheet("QDockWidget {border: 0px solid "
                        "rgb(32, 32, 32);}"
                        "QDockWidget::title {text-align: left;"
                        "background: rgb(32, 32, 32);}");

    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_pContent = new QVBoxLayout(this);
    m_pContent->setAlignment(Qt::AlignTop);
    m_pContent->setObjectName("inspector_layout");
    QMargins margins;
    margins.setBottom(4);
    margins.setRight(4);
    margins.setLeft(4);
    margins.setTop(4);
    m_pContent->setContentsMargins(margins);

    //QVBoxLayout* pComponent = new QVBoxLayout(this);
    //pComponent->addWidget(new QPushButton("test"));
    //pComponent->addWidget(new QLabel("test2"));
    //m_pContent->addLayout(pComponent);

    //QWidget* pDockedWidget = new QWidget(this);
    //pDockedWidget->setLayout(m_pContent);
}

void Inspector::addComponent(Component* pComponent)
{
    m_pContent->addWidget(pComponent);
}

void Inspector::update()
{
    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_pScrollArea->setWidgetResizable(false);
    QWidget* pWidget = new QWidget(m_pScrollArea);
    pWidget->setLayout(m_pContent);
    m_pScrollArea->setWidget(pWidget);
    m_pScrollArea->show();
    this->setWidget(m_pScrollArea);
}
