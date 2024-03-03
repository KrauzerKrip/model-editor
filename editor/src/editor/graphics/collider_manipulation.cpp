#include "collider_manipulation.h"

#include <iostream>

#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "editor/model/components.h"
#include "editor/control/components.h"


ColliderManipulation::ColliderManipulation(Editor* pEditor, entt::registry* pRegistry) { 
	m_pEditor = pEditor;
	m_pRegistry = pRegistry; 
}

void ColliderManipulation::frame(const glm::mat4& view, const glm::mat4& projection) {
	auto selectedColliders = m_pRegistry->view<Manipulable, Selected, Transform, BoxCollider>();
	 
	for (auto&& [entity, transform] : selectedColliders.each()) {
		glm::mat4 model(1.0);
		model = glm::translate(model, transform.position);

		//model = glm::translate(model, transform.position);
		// model *= glm::mat4_cast(transform.rotation);
		// model = glm::scale(model, transform.scale);

		if (m_pEditor->getToolMode() == ToolMode::MOVE) {
			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::OPERATION::TRANSLATE,
				ImGuizmo::MODE::WORLD, glm::value_ptr(model));

			transform.position = model[3];
		}
		else if (m_pEditor->getToolMode() == ToolMode::ROTATE) {
			model *= glm::mat4_cast(transform.rotation);

			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::OPERATION::ROTATE,
				ImGuizmo::MODE::LOCAL, glm::value_ptr(model));

			transform.rotation = model;
		}
		else if (m_pEditor->getToolMode() == ToolMode::SCALE) {
			model = glm::scale(model, transform.scale);
			ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection), ImGuizmo::OPERATION::SCALE,
				ImGuizmo::MODE::WORLD, glm::value_ptr(model));
			transform.scale.x = glm::length(glm::vec3(model[0]));
			transform.scale.y = glm::length(glm::vec3(model[1]));
			transform.scale.z = glm::length(glm::vec3(model[2]));
		}

	}
}
