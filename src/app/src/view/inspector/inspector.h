#pragma once

#include "component/component.h"
#include <QDockWidget>
#include <QScrollArea>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>

class Inspector : public QDockWidget
{
public:
    Inspector(QWidget* pParent = nullptr);

    void addComponent(Component* pComponent);
    void update();

private:
    QVBoxLayout* m_pContent;
    QScrollArea* m_pScrollArea = nullptr;
    QWidget* m_pScrollWidget = nullptr;
};
