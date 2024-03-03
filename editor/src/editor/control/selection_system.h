#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_system.h"
#include "mouse_raycast_observer.h"

#include "editor/model/editor.h"


class SelectionSystem : public MouseRaycastObserver {
public:
	SelectionSystem(Editor* pEditor, entt::registry* pRegistry);

	void onKey(KeyCode keyCode, entt::entity entity, glm::vec3 position, float distance) override;
	void onMouseMove(entt::entity entity, glm::vec3 position, float distance);

private:
	void selectEntity(entt::entity entity);
	void unselectEntity(entt::entity entity);

	Editor* m_pEditor = nullptr;
	entt::registry* m_pRegistry = nullptr;
};
