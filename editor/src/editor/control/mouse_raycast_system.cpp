#include "mouse_raycast_system.h"



MouseRaycastSystem::MouseRaycastSystem(MouseRaycast* pMouseRaycast, IInput* pInput) {
	m_pMouseRaycast = pMouseRaycast;
	m_pInput = pInput;
}

void MouseRaycastSystem::input() {
	//result will be acquired in the after the update

	RaycastResult result = m_pMouseRaycast->doMouseRaycast();
	if (result.entityIntersectedWith.has_value()) {
		for (MouseRaycastObserver* pObserver : m_observers) {
			pObserver->onMouseMove(result.entityIntersectedWith.value(), 
				result.intersectionPoint.value(), 
				result.intersectionDistance.value());
		}
	}
}

void MouseRaycastSystem::addObserver(KeyCode keyCode, MouseRaycastObserver* pObserver) { 
	m_observers.push_back(pObserver);

	m_pInput->addMappedKeyCallback(keyCode, [=]() { onAction(keyCode, pObserver); });
}

void MouseRaycastSystem::removeObserver(MouseRaycastObserver* pObserver) { 
	for (auto i = m_observers.begin(); i != m_observers.end(); ++i) {
		if (*i == pObserver) {
			m_observers.erase(i);
		}
	}
}

void MouseRaycastSystem::onAction(KeyCode keyCode, MouseRaycastObserver* pObserver) {
	RaycastResult result = m_pMouseRaycast->doMouseRaycast();

	if (result.entityIntersectedWith.has_value()) {
		//for (MouseRaycastObserver* pObserver : m_observers) {
			pObserver->onKey(keyCode, result.entityIntersectedWith.value(), result.intersectionPoint.value(),
				result.intersectionDistance.value());
		//}
	}
}
