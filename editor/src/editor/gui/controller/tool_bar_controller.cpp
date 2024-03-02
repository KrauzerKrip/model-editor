#include "tool_bar_controller.h"

#include <iostream>


ToolBarController::ToolBarController(ToolBar& taskBar, Editor* pEditor) : m_taskBar(taskBar) { 
	m_pEditor = pEditor; 
	m_taskBar.setActiveToolbarTool(ButtonType::SELECT);
}

void ToolBarController::update() { 
	ButtonType type = m_taskBar.m_activeButton; 
	if (type == ButtonType::SELECT) {
		m_pEditor->setToolMode(ToolMode::SELECT);
		m_taskBar.setActiveToolbarTool(ButtonType::SELECT);
	}
	else if (type == ButtonType::MOVE) {
		m_pEditor->setToolMode(ToolMode::MOVE);
		m_taskBar.setActiveToolbarTool(ButtonType::MOVE);
	}
	else if (type == ButtonType::ROTATE) {
		m_pEditor->setToolMode(ToolMode::ROTATE);
		m_taskBar.setActiveToolbarTool(ButtonType::ROTATE);
	}
	else if (type == ButtonType::SCALE) {
		m_pEditor->setToolMode(ToolMode::SCALE);
		m_taskBar.setActiveToolbarTool(ButtonType::SCALE);
	}
	else if (type == ButtonType::CREATE_BOX_COLLIDER) {
		m_taskBar.setActiveToolbarTool(ButtonType::SELECT);
		m_taskBar.m_activeButton = ButtonType::SELECT;
		m_pEditor->createCollider(ColliderType::BOX);
	}
}

