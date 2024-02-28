#include "game.h"

#include <iostream>
#include <chrono>
#include <memory>

#include <entt/entt.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ldk_client/local_engine/time.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "lc_client/util/eng_resource.h"
#include "lc_client/eng_input/glfw_input.h"
#include "lc_client/exceptions/input_exceptions.h"
#include "lc_client/tier1/openGL/gl_tier1.h"
#include "lc_client/eng_graphics/openGL/gl_mesh_loader.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_gui/gui_console.h"
#include "lc_client/eng_scene/skybox.h"
#include "lc_client/util/pack.h"
#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_graphics/gui/openGL/gl_background_render.h"
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_graphics/openGL/gl_skybox_render.h"

#include "lc_client/tier0/console/i_console.h"

#include "lc_client/eng_graphics/openGL/gl_window.h"
#include "lc_client/eng_script/entt/components.h"
#include "lc_client/eng_graphics/gui/openGL/gl_widget_zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_zoffset_calculator.h"
#include "editor/loader_fabric/openGL/gl_loader_fabric.h"
#include "editor/camera/orbital_camera_controller.h"
#include "editor/control/control_system.h"
#include "editor/control/action_control.h"

#include "editor/control/components.h"

#include "lc_client/eng_npc/npc_graph.h"
#include "lc_client/eng_npc/npc_graph_loader/npc_graph_loader.h"
#include "lc_client/eng_npc/components.h"
#include "lc_client/eng_physics/physics.h"
#include "editor/graphics/editor_render.h"
#include "editor/model/file_work/file_writer.h"


Game::Game(IWindow* pWindow, Tier0* pTier0) {
	m_pWindow = pWindow;
	m_pCamera = new Camera();
	m_pResource = new eng::Resource("E:/Industry/industry/res/"); 
	m_pTier0 = pTier0;
	m_pTier1 = new Tier1Gl(m_pResource, pTier0);
	m_pConsoleGui = new ConsoleGui(
		m_pTier0->getConsole(), m_pTier0->getImGuiFonts(), m_pTier1->getTextureManager(), m_pTier0->getParameters());

	m_pInput = m_pWindow->getInput();

	m_pTier1->getShaderManager()->loadShaders();

	LoaderFabricGl* pLoaderFabric =  new LoaderFabricGl(m_pResource, m_pTier0->getConsole(), m_pTier1->getShaderManager());

	Pack pack = Pack::getPack("dev");
	SkyboxRender* pSkyboxRender = new SkyboxRenderGl(pLoaderFabric->getShaderLoaderGl());

	SceneLoading* pSceneLoading = new SceneLoading(m_pResource);
	m_pWorld = new World(m_pResource, pSceneLoading, pSkyboxRender);

	Skybox* pSkybox = m_pWorld->getSkybox();
	pSkybox->setLightColor(255, 255, 200); // 255, 255, 236
	pSkybox->setLightStrength(0.4f);

	ModelManager* pModelManager = new ModelManager(
		m_pResource, m_pTier1->getTextureManager(), m_pWorld->getUtilRegistry(), m_pTier0->getConsole());
	ModelParser* pModelParser = new ModelParser(m_pResource);

	m_pRender = new EditorRender(m_pWindow, m_pCamera, pLoaderFabric->getShaderLoaderGl(), m_pWorld);

	m_pRender->init();

	m_pGraphicsSystems = new GraphicsSystems(m_pTier0, m_pTier1, pLoaderFabric->getShaderLoaderGl(), pLoaderFabric->getMeshLoader(), pLoaderFabric->getCubemapLoader(), m_pWorld, pModelManager, pModelParser);

	Physics* pPhysics = new Physics(&m_pWorld->getRegistry());
	PhysicsLoader* pPhysicsLoader = new PhysicsLoader(new PhysicsParser(m_pResource), &m_pWorld->getRegistry());
	m_pPhysicsSystem = new PhysicsSystem(
		pPhysics, pPhysicsLoader, pTier0->getParameters(), &m_pWorld->getRegistry(), m_pTier0->getConsole());

	m_pControlSystem = new ControlSystem(m_pInput, m_pCamera, pPhysics,
		&m_pWorld->getRegistry());

	Editor* pEditor = new Editor(&m_pWorld->getRegistry(), m_pResource, new FileWriter("E:/Industry/industry/res/"));

	m_pGui = new Gui(m_pTier0, m_pInput, pEditor, m_pTier1->getTextureManager(), &m_pWorld->getRegistry());
}

Game::~Game() {
	delete m_pRender;
	delete m_pResource;
	delete m_pTier1;
	delete m_pCamera;
	delete m_pTier0;
};

void Game::init() {
	m_pWorld->loadMap("dev", "test");
	m_pWorld->loadScene("dev", "test");

	m_pInput->addMappedKeyCallback(KeyCode::GRAVE_ACCENT, [pConsoleGui = this->m_pConsoleGui, pWindow = this->m_pWindow]() {
		if (pConsoleGui->isOpened()) {
			pConsoleGui->close();
		}
		else {
			pConsoleGui->open();
		}
		});

	m_pInput->addMappedKeyCallback(
		KeyCode::F3, [this]() {
			if (m_pWindow->getMode() == WindowMode::CURSOR_DISABLED) {
				m_pWindow->setMode(WindowMode::CURSOR_ENABLED);
				m_guiMode = true;
			}
			else {
				m_pWindow->setMode(WindowMode::CURSOR_DISABLED);
				m_guiMode = false;
			}
		});

	m_pInput->addMappedKeyCallback(KeyCode::F3, [this]() {
		if (m_pWindow->getMode() == WindowMode::CURSOR_DISABLED) {
			m_pWindow->setMode(WindowMode::CURSOR_ENABLED);
			m_guiMode = true;
		}
		else {
			m_pWindow->setMode(WindowMode::CURSOR_DISABLED);
			m_guiMode = false;
		}
		});

	m_pWindow->setMode(WindowMode::CURSOR_ENABLED);

	auto pRegistry = &m_pWorld->getRegistry();
	auto view = pRegistry->view<Properties>();
}

void Game::input() {
	m_pConsoleGui->frame();

	if (!m_pConsoleGui->isOpened()) { 
		m_pControlSystem->input();
	}

	//if (m_pWindow->getMode() == WindowMode::CURSOR_ENABLED) {
	//	m_lastMousePosX = m_pInput->getMousePosition().x;
	//	m_lastMousePosY = m_pInput->getMousePosition().y;
	//	return;
	//}

	float offsetMouseX = (float)(m_pInput->getMousePosition().x- m_lastMousePosX);
	float offsetMouseY = (float)(m_pInput->getMousePosition().y-m_lastMousePosY);

	m_lastMousePosX = m_pInput->getMousePosition().x;
	m_lastMousePosY = m_pInput->getMousePosition().y;

	if (!m_pConsoleGui->isOpened()) {
		m_pControlSystem->input();
	}
	//m_pCamera->setPosition(cameraPos);

}

void Game::update() {
	entt::registry* pRegistry = &m_pWorld->getRegistry();

	entt::entity surface;
	entt::entity surfaceScene;

	m_pGraphicsSystems->update();
	m_pPhysicsSystem->update();
	m_pControlSystem->update();
}

void Game::render() {
	m_pGraphicsSystems->frame();
	m_pGui->frame();
	m_pRender->render();
}

void Game::cleanUp() {}

