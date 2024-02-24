#include "component.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

Component::Component(QWidget* parent, std::string name)
    : QWidget{parent}
{
    m_pLayout = new QVBoxLayout(this);
    this->setLayout(m_pLayout); //exception
    QSizePolicy sizePolicy;
    sizePolicy.setVerticalStretch(1);
    this->setSizePolicy(sizePolicy);
    this->setObjectName("inspector_component");
    QMargins margins;
    margins.setTop(0);
    margins.setBottom(4);
    margins.setRight(0);
    margins.setLeft(0);
    m_pLayout->setContentsMargins(margins);

    QWidget* pBarWidget = new QWidget(this);
    pBarWidget->setObjectName("inspector_component_bar");
    QHBoxLayout* pBar = new QHBoxLayout(pBarWidget);
    QMargins marginsBar;
    marginsBar.setBottom(14);
    marginsBar.setTop(12);
    pBar->setContentsMargins(marginsBar);
    QLabel* pTitle = new QLabel(pBarWidget);
    pTitle->setMargin(4);
    pTitle->setText(name.c_str());
    pTitle->setAlignment(Qt::AlignLeft);
    pBarWidget->setLayout(pBar);

    m_pLayout->addWidget(pBarWidget, Qt::AlignTop);
}

void Component::addComponentWidget(QWidget* pWidget)
{
    m_pLayout->addWidget(pWidget, Qt::AlignTop);
}
