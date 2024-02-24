#include "top_toolbar.h"

#include "tool_button.h"

TopToolbar::TopToolbar()
{
    ToolButtonTop* pSelectButton = new ToolButtonTop(this, "selection");
    ToolButtonTop* pMoveButton = new ToolButtonTop(this, "move_xy");
    ToolButtonTop* pCreateEntityButton = new ToolButtonTop(this, "create_object");

    //connect(pSelectButton, &ToolButton::clicked, this, &SideToolBar::setToolSelect);
    //connect(pMoveButton, &ToolButton::clicked, this, &SideToolBar::setToolMove);
    //connect(pCreateEntityButton, &ToolButton::clicked, this, &SideToolBar::setToolCreateEntity);

    this->addWidget(pSelectButton);
    this->addWidget(pMoveButton);
    this->addSeparator();
    this->addWidget(pCreateEntityButton);
}
