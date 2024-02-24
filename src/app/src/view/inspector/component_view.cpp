#include "component_view.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ComponentView::ComponentView()
{
    QWidget* pWidget1 = new QWidget();
    QVBoxLayout* pLayout1 = new QVBoxLayout(pWidget1);
    pWidget1->setLayout(pLayout1);
    pLayout1->addWidget(new QPushButton("Test"));
    pLayout1->addWidget(new QLabel("Test"));
    this->addChildWidget(pWidget1);
}
