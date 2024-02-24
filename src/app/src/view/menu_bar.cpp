#include "menu_bar.h"

#include <QApplication>

MenuBar::MenuBar()
{
    m_pFileMenu = addMenu("File");
    m_pHelpMenu = addMenu("Help");
    QAction* actNew = m_pFileMenu->addAction("New");
    QAction* actOpen = m_pFileMenu->addAction("Open");
    QAction* actSave = m_pFileMenu->addAction("Save");
    QAction* actSaveAs = m_pFileMenu->addAction("Save as");
    m_pFileMenu->addSeparator();
    QAction* actExit = m_pFileMenu->addAction("Exit");

    m_pHelpMenu->addAction("About");
    m_pHelpMenu->addAction("Docs");

    actSave->setShortcut(tr("CTRL+S"));

    connect(actExit, &QAction::triggered, this, &QApplication::quit);
}
