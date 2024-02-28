#pragma once

#include <string>

#include "editor/model/editor.h"


class Inspector {
public:
	Inspector(Editor* pEditor);

	void frame();

private:
	std::string m_modelFile;
	std::string m_materialType;
	std::string m_vertexShader;
	std::string m_fragmentShader;

	Editor* m_pEditor = nullptr;
};