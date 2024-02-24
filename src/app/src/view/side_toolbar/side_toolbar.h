#pragma once

#include <unordered_map>

#include <QDockWidget>
#include <QLabel>
#include <QPushButton>
#include <QStyleFactory>
#include <QTimer>
#include <QToolBar>

#include "tool_button.h"

#include "model/editor_mode_handler.h"

class SideToolBar : public QToolBar
{
    Q_OBJECT
public:
    SideToolBar(EditorModeHandler* pModeHandler);

public slots:
    void setToolSelect();
    void setToolMove();
    void setToolCreateEntity();

private:
    std::unordered_map<EditorMode, ToolButton*> m_toolButtons;
    EditorModeHandler* m_pModeHandler;
};
