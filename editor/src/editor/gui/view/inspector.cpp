#include "inspector.h"

#include <imgui.h>
#include <imgui_stdlib.h>


using namespace ImGui;


Inspector::Inspector(Editor* pEditor) { 
	m_pEditor = pEditor;

	m_pEditor->getProject().addLoadingCallback([this]() { 
		const Project& project = m_pEditor->getProject();

		m_modelFile = project.m_modelFile;
		m_materialType = project.m_materialType;
		m_vertexShader = project.m_vertexShader;
		m_fragmentShader = project.m_fragmentShader;
	});
}

void Inspector::frame() {
	ImVec2 size(400, 512);
	auto viewport = GetMainViewport();

	ImVec2 pos(viewport->Size.x - size.x - GetStyle().ItemSpacing.x, viewport->GetCenter().y - size.y + 105);

	SetNextWindowPos(pos);
	SetNextWindowSize(size);

	const char* materialTypes[] = {"SG", "MR"};
	
	int currentItem = 0;
	if (m_materialType == "mr") {
		currentItem = 1;
	}

	if (Begin("Inspector", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
		PushItemWidth(140);
		InputText("Model file", &m_modelFile);
		
		if (ImGui::BeginCombo("Material type", materialTypes[currentItem])) {
			for (int i = 0; i < 2; i++) {
				const bool isSelected = (currentItem == i);
				if (ImGui::Selectable(materialTypes[i], isSelected))
					currentItem = i;

				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		m_materialType = std::string(materialTypes[currentItem]);
		
		std::transform(m_materialType.begin(), m_materialType.end(), m_materialType.begin(),
			[](unsigned char c) { return std::tolower(c); });

		InputText("Vertex shader", &m_vertexShader);
		InputText("Fragment shader", &m_fragmentShader);

		m_pEditor->getProject().m_modelFile = m_modelFile;
		m_pEditor->getProject().m_materialType = m_materialType;
		m_pEditor->getProject().m_vertexShader = m_vertexShader;
		m_pEditor->getProject().m_fragmentShader = m_fragmentShader;

		End();
	}
}
