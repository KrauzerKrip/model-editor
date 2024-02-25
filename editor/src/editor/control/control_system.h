#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_system.h"
#include "selection_system.h"
#include "lc_client/eng_input/i_input.h"
#include "editor/control/action_control.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "character_control_system.h"
#include "editor/camera/camera_controller.h"
#include "lc_client/eng_physics/physics.h"
#include "mouse_raycast.h"


class ControlSystem {
public:
	ControlSystem(IInput* pInput, Camera* pCamera,
		Physics* pPhysics, 
		entt::registry* pRegistry);
	~ControlSystem();

	void input();
	void update();

private:
	MouseRaycast m_mouseRaycast;
	SelectionSystem m_selectionSystem;
	CharacterControlSystem m_characterControlSystem;
	MouseRaycastSystem m_mouseRaycastSystem;

	CameraController* m_pCameraController = nullptr;
};
