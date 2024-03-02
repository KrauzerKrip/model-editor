#include "tool_bar.h"

#include <imgui.h>
#include <glad/glad.h>


#include "lc_client/eng_graphics/openGL/gl_texture.h"


using namespace ImGui;


ToolBar::ToolBar(TextureManager* pTextureManager) {
	TextureGL* pSelectionTexture = dynamic_cast<TextureGL*>(pTextureManager->getTexture("sdk/icons/selection"));
	pSelectionTexture->setTextureType(TextureType::DIFFUSE);
	pSelectionTexture->load();
	m_selectionTexture = pSelectionTexture->getId();

	TextureGL* pMoveTexture = dynamic_cast<TextureGL*>(pTextureManager->getTexture("sdk/icons/move"));
	pMoveTexture->setTextureType(TextureType::DIFFUSE);
	pMoveTexture->load();
	m_moveTexture = pMoveTexture->getId();

	TextureGL* pRotateTexture = dynamic_cast<TextureGL*>(pTextureManager->getTexture("sdk/icons/rotate"));
	pRotateTexture->setTextureType(TextureType::DIFFUSE);
	pRotateTexture->load();
	m_rotateTexture = pRotateTexture->getId();

	TextureGL* pScaleTexture = dynamic_cast<TextureGL*>(pTextureManager->getTexture("sdk/icons/scale"));
	pScaleTexture->setTextureType(TextureType::DIFFUSE);
	pScaleTexture->load();
	m_scaleTexture = pScaleTexture->getId();

	TextureGL* pBoxColliderTexture = dynamic_cast<TextureGL*>(pTextureManager->getTexture("sdk/icons/create_box_collider"));
	pBoxColliderTexture->setTextureType(TextureType::DIFFUSE);
	pBoxColliderTexture->load();
	m_boxColliderTexture = pBoxColliderTexture->getId();
}

void ToolBar::frame() {
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + 4, viewport->Pos.y + 120));
	ImGui::SetNextWindowSize(ImVec2(81, 360));
	//ImGui::SetNextWindowViewport(viewport->ID);
	 
	ImGuiWindowFlags window_flags = 0 | ImGuiWindowFlags_NoTitleBar |
									ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("TOOLBAR", NULL, window_flags);
	ImGui::PopStyleVar(); 

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 color = style.Colors[ImGuiCol_Button];
	color =
		m_activeToolbarTool == ButtonType::SELECT ? style.Colors[ImGuiCol_ButtonActive] : style.Colors[ImGuiCol_Button];
	if (ImGui::ImageButton(
			(void*)(intptr_t)m_selectionTexture, ImVec2(56, 56), ImVec2(0, 0), ImVec2(1, 1), -1, color)) {
		m_activeButton = ButtonType::SELECT;
	};

	color =
		m_activeToolbarTool == ButtonType::MOVE ? style.Colors[ImGuiCol_ButtonActive] : style.Colors[ImGuiCol_Button];
	if (ImGui::ImageButton(
			(void*)(intptr_t)m_moveTexture, ImVec2(56, 56), ImVec2(0, 0), ImVec2(1, 1), -1, color)) {
		m_activeButton = ButtonType::MOVE;
	};

	color =
		m_activeToolbarTool == ButtonType::ROTATE ? style.Colors[ImGuiCol_ButtonActive] : style.Colors[ImGuiCol_Button];
	if (ImGui::ImageButton(
			(void*)(intptr_t)m_rotateTexture, ImVec2(56, 56), ImVec2(0, 0), ImVec2(1, 1), -1, color)) {
		m_activeButton = ButtonType::ROTATE;
	};

	color =
		m_activeToolbarTool == ButtonType::SCALE ? style.Colors[ImGuiCol_ButtonActive] : style.Colors[ImGuiCol_Button];
	if (ImGui::ImageButton(
			(void*)(intptr_t)m_scaleTexture, ImVec2(56, 56), ImVec2(0, 0), ImVec2(1, 1), -1, color)) {
		m_activeButton = ButtonType::SCALE;
	};

	ImGui::Separator();

	if (ImGui::ImageButton((void*)(intptr_t)m_boxColliderTexture, ImVec2(56, 56))) {
		m_activeButton = ButtonType::CREATE_BOX_COLLIDER;
	};

	ImGui::End();

}

void ToolBar::setActiveToolbarTool(ButtonType type) { m_activeToolbarTool = type; }
