#pragma once

#include "lc_client/eng_graphics/shader_work.h"

#include <vector>

#include "lc_client/tier1/i_shaders.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "lc_client/eng_graphics/openGL/gl_skybox_render.h"
#include "lc_client/tier0/console/i_console.h"


class ShaderWorkGl : public ShaderWork {
	friend class RenderGL; 
	friend class SkyboxRenderGl;

public:
	ShaderWorkGl(IShaderManager* pShaderManager, entt::registry* pRegistry, IConsole* pConsole)
		: ShaderWork(pRegistry),
		  m_pShaderManager(pShaderManager),
		  m_pConsole(pConsole) {};

	void loadShaders(entt::entity entity, const std::string vertexShaderName, const std::string fragmentShaderName);

private:
	IShaderManager* m_pShaderManager;
	IConsole* m_pConsole;

	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
};
