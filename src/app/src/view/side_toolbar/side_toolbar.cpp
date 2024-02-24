#include "side_toolbar.h"

#include "tool_button.h"
#include <QMessageBox>

SideToolBar::SideToolBar(EditorModeHandler* pModeHandler)
{
    //this->addAction("Select");
    //this->addAction("Move");
    //this->addAction("Rotate");
    //this->addSeparator();
    //this->addAction("Create brush");
    //this->addAction("Create entity");

    m_pModeHandler = pModeHandler;

    m_pModeHandler->setModeChangeCallback([this](EditorMode mode) {
        for (auto& [buttonMode, button] : this->m_toolButtons) {
            if (mode == buttonMode) {
                button->setChecked(true);
                button->setStyleSheet("QPushButton {background-color: rgb(92, 92, 92);}");
            } else {
                button->setChecked(false);
                button->setStyleSheet("QPushButton {background-color: rgb(48, 48, 48);} "
                                      "QPushButton:hover {background-color: rgb(72, 72, 72);}");
            }
        }
    });

    this->setObjectName("side_toolbar");

    ToolButton* pSelectButton = new ToolButton(this, "selection");
    ToolButton* pMoveButton = new ToolButton(this, "move_xy");
    ToolButton* pCreateEntityButton = new ToolButton(this, "create_object");

    m_toolButtons.emplace(EditorMode::SELECT, pSelectButton);
    m_toolButtons.emplace(EditorMode::MOVE, pMoveButton);
    m_toolButtons.emplace(EditorMode::CREATE_ENTITY, pCreateEntityButton);

    connect(pSelectButton, &ToolButton::clicked, this, &SideToolBar::setToolSelect);
    connect(pMoveButton, &ToolButton::clicked, this, &SideToolBar::setToolMove);
    connect(pCreateEntityButton, &ToolButton::clicked, this, &SideToolBar::setToolCreateEntity);

    this->addWidget(pSelectButton);
    this->addWidget(pMoveButton);
    this->addSeparator();
    this->addWidget(pCreateEntityButton);
}

void SideToolBar::setToolSelect()
{
    m_pModeHandler->setMode(EditorMode::SELECT);
    QMessageBox msgBox;
    msgBox.setText("set mode select");
    //msgBox.exec();
}

void SideToolBar::setToolMove()
{
    m_pModeHandler->setMode(EditorMode::MOVE);
    QMessageBox msgBox;
    msgBox.setText("set mode move");
    //msgBox.exec();
}

void SideToolBar::setToolCreateEntity()
{
    m_pModeHandler->setMode(EditorMode::CREATE_ENTITY);
    QMessageBox msgBox;
    msgBox.setText("set mode create entity");
    //msgBox.exec();
}
