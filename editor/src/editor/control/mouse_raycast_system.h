#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_observer.h"
#include "mouse_raycast.h"


class MouseRaycastSystem {
public: 
	MouseRaycastSystem(MouseRaycast* pMouseRaycast, IInput* pInput);

	void input();
	void addObserver(KeyCode keyCode, MouseRaycastObserver* pObserver);
	void removeObserver(MouseRaycastObserver* pObserver);

private:
	void onAction(KeyCode keyCode, MouseRaycastObserver* pObserver);

	MouseRaycast* m_pMouseRaycast = nullptr;
	IInput* m_pInput = nullptr;

	std::vector<MouseRaycastObserver*> m_observers;
};
