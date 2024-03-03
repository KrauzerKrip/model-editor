#include "control_system.h"

#include "editor/camera/orbital_camera_controller.h"


ControlSystem::ControlSystem(
	IInput* pInput, Camera* pCamera, Physics* pPhysics, Editor* pEditor, entt::registry* pRegistry)
	: m_mouseRaycast(pPhysics, pInput, pCamera, pRegistry),
	m_selectionSystem(pEditor, pRegistry),
	  m_characterControlSystem(pRegistry),
	  m_mouseRaycastSystem(&m_mouseRaycast, pInput) {

	m_pCameraController = new OrbitalCameraController(pCamera, pInput);

	m_mouseRaycastSystem.addObserver(KeyCode::MOUSE_BUTTON_LEFT, &m_selectionSystem);
	m_mouseRaycastSystem.addObserver(KeyCode::MOUSE_BUTTON_LEFT, &m_characterControlSystem);
}

ControlSystem::~ControlSystem() {
	delete m_pCameraController;
}

void ControlSystem::input() { 
	m_pCameraController->input();
	m_mouseRaycastSystem.input();
}

void ControlSystem::update() {}
