#pragma once

#include "editor/model/editor.h"
#include "editor/model/project.h"


class Menu {
public:
	Menu(Editor* pEditor);

	void frame();

private:
	void createProject();

	bool m_windowNew;
	bool m_createPhysicsFile = false;
	std::string m_modelName;

	Editor* m_pEditor = nullptr;
};