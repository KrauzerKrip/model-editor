#pragma once

#include "lc_client/tier1/texture_manager.h"

enum class ButtonType { SELECT, MOVE, ROTATE, SCALE, CREATE_BOX_COLLIDER };


class ToolBar {
public:
	ToolBar(TextureManager* pTextureManager);

	void frame();

	void setActiveToolbarTool(ButtonType type);
	ButtonType getActive();

private:
	ButtonType m_activeButton;
	ButtonType m_activeToolbarTool;
	
	unsigned int m_selectionTexture;
	unsigned int m_moveTexture;
	unsigned int m_rotateTexture;
	unsigned int m_scaleTexture;
	unsigned int m_boxColliderTexture;
};