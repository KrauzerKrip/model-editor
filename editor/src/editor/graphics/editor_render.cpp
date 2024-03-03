#include "editor_render.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <ImGuizmo.h>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"
#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/eng_graphics/openGL/renders/gl_mesh_render.h"
#include "lc_client/eng_physics/entt/components.h"
#include "editor/control/components.h"

#include "lc_client/tier0/tier0.h"


EditorRender::EditorRender(
	IWindow* pWindow, Camera* pCamera, ShaderLoaderGl* pShaderLoader, World* pWorld, Editor* pEditor)
	: m_colliderManipulation(pEditor, &pWorld->getRegistry()),
	  m_meshRender(&pWorld->getUtilRegistry()),
	  m_outlineRender(&m_meshRender, pShaderLoader) {
	m_pWindow = pWindow; // mb remove it
	m_pCamera = pCamera;
	m_pShaderLoader = pShaderLoader;
	m_pFramebuffer = new Framebuffer(pWindow->getSize()[0], pWindow->getSize()[1]);

	m_pRegistry = &pWorld->getRegistry();
	m_pUtilRegistry = &pWorld->getUtilRegistry();

	m_imguiIsDepthTestEnabled = false;

	m_colliderShader = pShaderLoader->createShaderProgram("primitive", "primitive_alpha");

	 float cubeVertices[] = {// front

		-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0};

	GLuint cubeIndices[] = {// front
		0, 1, 2, 2, 3, 0,
		// right
		1, 5, 6, 6, 2, 1,
		// back
		7, 6, 5, 5, 4, 7,
		// left
		4, 0, 3, 3, 7, 4,
		// bottom
		4, 5, 1, 1, 0, 4,
		// top
		3, 2, 6, 6, 7, 3};

	unsigned int cubeVbo;
	unsigned int cubeEbo;

	glGenVertexArrays(1, &m_cubeVao);
	glGenBuffers(1, &cubeVbo);
	glBindVertexArray(m_cubeVao);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &cubeEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

EditorRender::~EditorRender() {}

void EditorRender::init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_MULTISAMPLE);

	createFramebufferVao();

	m_framebufferShader = m_pShaderLoader->createShaderProgram("framebuffer", "framebuffer");

	m_pWindow->setResizeCallback([this](int width, int height) {
		delete m_pFramebuffer;
		m_pFramebuffer = new Framebuffer(width, height);
		});
	

	m_pPrimitiveRender = new PrimitiveRender(m_pShaderLoader, m_pRegistry, m_pRegistry);

	glClearColor(64.0f / 255, 64.0f / 255, 64.0f / 255, 1.0f);

	ImGuizmo::SetImGuiContext(ImGui::GetCurrentContext());
	ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
	ImGuizmo::SetRect(0, 0, m_pWindow->getSize()[0], m_pWindow->getSize()[1]);
}

unsigned int iDebug = 0;


void EditorRender::render() {
	ImGuizmo::BeginFrame();

	iDebug++;
	if (iDebug > 1000) {
		int i = 0;
	}


	m_pFramebuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask(0x00);

	float aspectRatio = (float)m_pWindow->getAspectRatio()[0] / (float)m_pWindow->getAspectRatio()[1];
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 view = m_pCamera->getViewMatrix(); // glm::mat4(1.0f);

	auto opaqueModels = m_pRegistry->view<Transform, Model, ShaderGl>();

	for (auto&& [entity, transform, model, shader] : opaqueModels.each()) {
		std::vector<entt::entity>& meshes = model.meshes;
		unsigned int shaderProgram = shader.shaderProgram;
		glUseProgram(shaderProgram);

		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());

		if (m_pRegistry->all_of<ShaderUniforms>(entity)) {
			const ShaderUniforms& uniforms = m_pRegistry->get<ShaderUniforms>(entity);

			for (auto&& [k, v] : uniforms.floatUniforms) {
				setUniform(shaderProgram, k, v);
			}
			for (auto&& [k, v] : uniforms.vectorUniforms) {
				setUniform(shaderProgram, k, v);
			}
		}

		m_meshRender.setUp(transform, shaderProgram, projection, view);

		for (entt::entity& meshEntity : meshes) {
			m_meshRender.renderMesh(meshEntity);
		}
	}

	glDepthMask(false);
	auto cubeEntities = m_pRegistry->view<BoxCollider, Transform>();
	glUseProgram(m_colliderShader);
	for (auto&& [entity, transform] : cubeEntities.each()) {
		glm::mat4 mvp = projection * view;

		glBindVertexArray(m_cubeVao);

		setUniform(m_colliderShader, "color", glm::vec4(111.0 / 255.0, 174 / 255.0, 225.0 / 255.0, 0.5));

		glm::mat4 model(1.0);

		model = glm::translate(model, transform.position);
		model *= glm::mat4_cast(transform.rotation);
		model = glm::scale(model, transform.scale);

		mvp *= model;

		unsigned int mvpLoc = glGetUniformLocation(m_colliderShader, "mvp");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

		if (m_pRegistry->all_of<Selected>(entity)) {
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
		}

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		if (m_pRegistry->all_of<Selected>(entity)) {
			Transform transformOutline(transform);
			transformOutline.scale = transform.scale + 0.1f;

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glUseProgram(m_colliderShader);
			setUniform(m_colliderShader, "color", glm::vec4(1.0, 102.0 / 255.0, 0, 1.0));
			glm::mat4 modelOutline(1.0);
			modelOutline = glm::translate(modelOutline, transform.position);
			modelOutline *= glm::mat4_cast(transform.rotation);
			modelOutline = glm::scale(modelOutline, transform.scale + 0.1f);
			glm::mat4 mvpOutline = projection * view;
			mvpOutline *= modelOutline;
			unsigned int mvpLocOutline = glGetUniformLocation(m_colliderShader, "mvp");
			glUniformMatrix4fv(mvpLocOutline, 1, GL_FALSE, glm::value_ptr(mvpOutline));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);
		}

		glBindVertexArray(0);
	}

	glDepthMask(true);
	m_pPrimitiveRender->render(projection, view);
	glDisable(GL_DEPTH_TEST);

	m_colliderManipulation.frame(view, projection);

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	m_pFramebuffer->bindTexture();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_framebufferShader);
	setUniform(m_framebufferShader, "screenTexture", TextureType::FRAMEBUFFER);

	glBindVertexArray(m_framebufferVao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_DEPTH_TEST);
}

void EditorRender::clear() {}

void EditorRender::cleanUp() {}

void EditorRender::createFramebufferVao() {
	float quadVertices[] = {// positions // texCoords
		-1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	unsigned int quadVBO;
	glGenVertexArrays(1, &m_framebufferVao);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(m_framebufferVao);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

const float* EditorRender::mat4toArray(const glm::mat4& mat) { 
	float* pArray = new float[16];

	const float* pSource = (const float*)glm::value_ptr(mat);
	for (int i = 0; i < 16; ++i) {
		pArray[i] = pSource[i];
	}
	
	return pArray;
}