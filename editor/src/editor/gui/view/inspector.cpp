#include "inspector.h"

#include <imgui.h>
#include <imgui_stdlib.h>


using namespace ImGui;


Inspector::Inspector(Editor* pEditor) { m_pEditor = pEditor; }

void Inspector::frame() {
	ImVec2 size(400, 512);
	auto viewport = GetMainViewport();

	ImVec2 pos(viewport->Size.x - size.x - GetStyle().ItemSpacing.x, viewport->GetCenter().y - size.y + 105);

	SetNextWindowPos(pos);
	SetNextWindowSize(size);

	const char* materialTypes[] = {"SG", "MR"};
	static int currentItem = 0;

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

		InputText("Vertex shader", &m_vertexShader);
		InputText("Fragment shader", &m_fragmentShader);

		End();
	}
}
