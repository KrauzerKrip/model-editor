#pragma once

#include <QWidget>
#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar();

private:
    QMenu* m_pFileMenu;
    QMenu* m_pHelpMenu;
};

