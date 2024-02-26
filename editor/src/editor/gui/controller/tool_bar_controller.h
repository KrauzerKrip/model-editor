#pragma once

#include "editor/gui/view/tool_bar.h"


class ToolBarController {
public:
	ToolBarController(ToolBar& taskBar);

	void update();

private:
	ToolBar& m_taskBar;
};