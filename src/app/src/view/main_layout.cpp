#include "main_layout.h"

#include <QLayout>
#include <QPushButton>

MainLayout::MainLayout()
{
    //QHBoxLayout* hBox = new QHBoxLayout();
    //setLayout(hBox);

    QVBoxLayout* toolBar = new QVBoxLayout();

    QPushButton* add = new QPushButton("Add");
    QPushButton* rename = new QPushButton("Rename");
    QPushButton* remove = new QPushButton("Remove");
    QPushButton* removeall = new QPushButton("Remove All");

    toolBar->setSpacing(3);
    toolBar->addStretch(1);
    toolBar->addWidget(add);
    toolBar->addWidget(rename);
    toolBar->addWidget(remove);
    toolBar->addWidget(removeall);
    toolBar->addStretch(1);

    addLayout(toolBar);
}
