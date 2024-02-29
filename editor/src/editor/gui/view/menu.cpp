#include "menu.h"

#include <imgui.h>
#include <imgui_stdlib.h>


using namespace ImGui;


Menu::Menu(Editor* pEditor) { 
	m_pEditor = pEditor;
	m_windowNew = false; 
	m_windowNoProject = false;
	m_windowProjectList = false;
}

void Menu::frame() {
	SetNextWindowPos(ImVec2(-1, 0));
	SetNextWindowSize(ImVec2(1922, 54));

	if (BeginMainMenuBar()) {
		if (BeginMenu("File")) {
			if (MenuItem("New")) {
				m_windowNew = true;
				m_windowProjectList = false;
				m_windowNoProject = false;
			}
			if (MenuItem("Open")) {
				m_models = m_pEditor->getPackModels("game");
				m_selectedModel = -1;
				m_selectedModelName = "";
				m_windowProjectList = true;
				m_windowNew = false;
				m_windowNoProject = false;
			}
			Separator();
			if (MenuItem("Save")) {
				try {
					m_pEditor->getProject().save();
				}
				catch (NoProjectException& exception) {
					m_windowNoProject = true;
				}
			}
			if (MenuItem("Save as")) {}

			EndMenu();
		}

		if (BeginMenu("Editor")) {
			if (MenuItem("Load model")) {
				m_pEditor->loadModel();
			}

			EndMenu();
		}


		EndMainMenuBar();
	}

	if (m_windowNoProject) {
		this->showNoProject();
	}
	if (m_windowProjectList) {
		this->showProjectList();
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

void Menu::showNoProject() { 
	SetNextWindowPos(ImVec2(GetMainViewport()->GetCenter().x - 256, GetMainViewport()->GetCenter().y - 75));
	SetNextWindowSize(ImVec2(512, 150));
	if (Begin("Exception", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
		Text("No project loaded.");

		if (Button("Ok")) {
			m_windowNoProject = false;
		}

		End();
	}
}

void Menu::showProjectList() {
	SetNextWindowPos(ImVec2(GetMainViewport()->GetCenter().x - 360, GetMainViewport()->GetCenter().y - 256));
	SetNextWindowSize(ImVec2(720, 512));

	if (Begin("Project list", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
		if (BeginChild("project_list", ImVec2(512, 512), false,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar)) {
			int i = 0;
			for (auto&& [name, dir] : m_models) {
				i++;
				if (ImGui::Selectable(name.c_str(), m_selectedModel == i)) {
					m_selectedModel = i;
					m_selectedModelName = name;
				}
			}

			EndChild();
		}

		SameLine();

		SetCursorPosY(GetCursorPosY() + 512 - 140 - ImGui::GetStyle().ItemSpacing.y);

		if (Button("Load", ImVec2(180, 80))) {
			if (m_selectedModel != -1) {
				m_pEditor->getProject().load("game", m_selectedModelName);
				m_pEditor->loadModel();
				m_windowProjectList = false;
			}
		}

		End();
	}
}

void Menu::createProject() {
	if (!m_modelName.empty()) {
		m_pEditor->getProject().create("game", m_modelName, m_createPhysicsFile);
		m_windowNew = false;
	}
}
