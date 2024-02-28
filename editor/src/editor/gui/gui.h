#pragma once

#include <entt/entt.hpp>

#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_input/i_input.h"
#include "editor/control/action_control.h"
#include "view/menu.h"
#include "view/tool_bar.h"
#include "controller/tool_bar_controller.h"
#include "editor/model/editor.h"


class Gui {
public:
	Gui(Tier0* pTier0, IInput* pInput, Editor* pEditor, TextureManager* pTextureManager, entt::registry* pRegistry);
	
	void frame();

private:
	Menu m_menu;
	ToolBar m_taskBar;
	ToolBarController m_taskBarController;
};
