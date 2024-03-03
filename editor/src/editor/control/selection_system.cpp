#include "selection_system.h"

#include <iostream>

#include "components.h"


SelectionSystem::SelectionSystem(Editor* pEditor, entt::registry* pRegistry) {
	m_pEditor = pEditor;
	m_pRegistry = pRegistry;
}

void SelectionSystem::onKey(KeyCode keyCode, entt::entity entity, glm::vec3 position, float distance) {
	if (keyCode == KeyCode::MOUSE_BUTTON_LEFT && m_pEditor->getToolMode() == ToolMode::SELECT) {
		if (m_pRegistry->all_of<Selectable>(entity)) {
			if (m_pRegistry->all_of<Selected>(entity)) {
				unselectEntity(entity);
			}
			else {
				selectEntity(entity);
			}
		}
	}
}

void SelectionSystem::onMouseMove(entt::entity entity, glm::vec3 position, float distance) {}

void SelectionSystem::selectEntity(entt::entity entity) {
	m_pRegistry->emplace<Selected>(entity);

	auto selectedEntities = m_pRegistry->view<Selectable, Selected>();
	for (auto&& [ent] : selectedEntities.each()) {
		if (ent != entity) {
			unselectEntity(ent);
		}
	}
}

void SelectionSystem::unselectEntity(entt::entity entity) {
	m_pRegistry->remove<Selected>(entity);
}
