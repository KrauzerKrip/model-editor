#pragma once

#include <entt/entt.hpp>

#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_input/i_input.h"
#include "editor/control/action_control.h"

class Gui {
public:
	Gui(Tier0* pTier0, IInput* pInput, entt::registry* pRegistry);
	
	void frame();

private:
};
