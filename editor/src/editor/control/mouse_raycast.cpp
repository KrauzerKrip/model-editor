#include "mouse_raycast.h"

#include <iostream>

#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "components.h"


MouseRaycast::MouseRaycast(Physics* pPhysics, IInput* pInput, Camera* pCamera,
	entt::registry* pRegistry) {
	m_pInput = pInput;
	m_pRegistry = pRegistry;
	m_pCamera = pCamera;
	m_pPhysics = pPhysics;

	m_windowSize = glm::vec2(1920, 1080);
	m_fov = 90.0f;
	m_aspectRatio = 16.0f / 9.0f;
}