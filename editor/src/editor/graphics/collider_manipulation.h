#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "editor/model/editor.h"


class ColliderManipulation {
public:
	ColliderManipulation(Editor* pEditor, entt::registry* pRegistry);

	void frame(const glm::mat4& view, const glm::mat4& projection);

private:
	Editor* m_pEditor = nullptr;
	entt::registry* m_pRegistry = nullptr;
};