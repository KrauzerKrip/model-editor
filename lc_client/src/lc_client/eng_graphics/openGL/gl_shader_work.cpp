#include "gl_shader_work.h"

#include <iostream>

#include <glad/glad.h>


void ShaderWorkGl::loadShaders(entt::entity entity, const std::string vertexShaderName,
							   const std::string fragmentShaderName) {

	m_pRegistry->emplace_or_replace<ShaderGl>(entity, (int) createShaderProgram(vertexShaderName, fragmentShaderName));
}

unsigned int ShaderWorkGl::createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	try {
		glAttachShader(shaderProgram, m_pShaderManager->getFragmentShader(fragmentShaderName));
	}
	catch (const std::out_of_range& exception) {
		std::cerr << exception.what() << std::endl;
		m_pConsole->warn(exception.what());
	}
	try {
		glAttachShader(shaderProgram, m_pShaderManager->getVertexShader(vertexShaderName));
	}
	catch (const std::out_of_range& exception) {
		std::cerr << exception.what() << std::endl;
		m_pConsole->warn(exception.what());
	}

	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

	if (success) {
		std::cout << "gl_shader_work: shader program linked successfully: " << shaderProgram << std::endl;
	}
	else {
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		std::cerr << "gl_shader_work: shader program link failure: \n" << infoLog << std::endl;
		std::string msgText = "gl_shader_work: shader program link failure: " + (std::string) infoLog;
		m_pConsole->warn(msgText);
	}

	return shaderProgram;
}