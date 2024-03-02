#pragma once

#include "editor/gui/view/tool_bar.h"
#include "editor/model/editor.h"


class ToolBarController {
public:
	ToolBarController(ToolBar& taskBar, Editor* pEditor);

	void update();

private:
	ToolBar& m_taskBar;
	Editor* m_pEditor = nullptr;
};