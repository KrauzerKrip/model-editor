#include "menu.h"

#include <imgui.h>
#include <imgui_stdlib.h>


using namespace ImGui;


Menu::Menu(Project& project) : m_project(project) { m_windowNew = false; }

void Menu::frame() {
	SetNextWindowPos(ImVec2(-1, 0));
	SetNextWindowSize(ImVec2(1922, 54));

	if (BeginMainMenuBar()) {
		if (BeginMenu("File")) {
			if (MenuItem("New")) {
				m_windowNew = true;
			}
			if (MenuItem("Open")) {}
			Separator();
			if (MenuItem("Save")) {}
			if (MenuItem("Save as")) {}

			EndMenu();
		}


		EndMainMenuBar();
	}

	if (m_windowNew) {
		SetNextWindowPos(ImVec2(GetMainViewport()->GetCenter().x - 256, GetMainViewport()->GetCenter().y - 80));
		SetNextWindowSize(ImVec2(512, 200));
		if (Begin("Create model", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
			InputText("Model name", &m_modelName);
			
			Checkbox("Create physics file", &m_createPhysicsFile);

			ImGui::NextColumn();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - 100 -
								 ImGui::GetStyle().ItemSpacing.x);

			if (Button("Create", ImVec2(100, 40))) {
				this->createProject();
			}
			End();
		}
	}


}

void Menu::createProject() {
	m_project.create(m_modelName, m_createPhysicsFile);
	m_windowNew = false;
}
