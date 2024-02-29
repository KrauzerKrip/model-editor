#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_scene/skybox.h"
#include "lc_client/eng_graphics/shader_loader.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer.h"
#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "lc_client/eng_graphics/openGL/renders/gl_render_map.h"
#include "lc_client/eng_graphics/openGL/renders/gl_lighting.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/eng_graphics/gui/text_render.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/openGL/renders/gl_primitive_render.h"
#include "lc_client/eng_graphics/openGL/renders/gl_transparent_render.h"
#include "lc_client/eng_graphics/openGL/renders/gl_mesh_render.h"
#include "lc_client/eng_graphics/openGL/renders/gl_opaque_render.h"
#include "lc_client/eng_graphics/openGL/renders/gl_outline_render.h"

class ShaderLoaderGl;

class EditorRender : public IRender {

	friend class RenderMapGl;

public:
	EditorRender(IWindow* pWindow, Camera* pCamera, ShaderLoaderGl* pShaderWork, World* pWorld);
	~EditorRender();

	void init() override;
	void render() override;
	void clear() override;
	void cleanUp() override;

private:
	void createFramebufferVao();

	const float* mat4toArray(const glm::mat4& mat);

	IWindow* m_pWindow; //mb remove it
	Camera* m_pCamera;
	ShaderLoaderGl* m_pShaderLoader;
	MeshRenderGl* m_pMeshRender = nullptr;
	PrimitiveRender* m_pPrimitiveRender = nullptr;

	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Framebuffer* m_pFramebuffer = nullptr;
	unsigned int m_framebufferTexture = 0;
	unsigned int m_framebufferVao = 0;
	unsigned int m_framebufferShader = 0;
};