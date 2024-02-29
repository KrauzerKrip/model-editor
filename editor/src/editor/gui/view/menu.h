#pragma once

#include "editor/model/editor.h"
#include "editor/model/project.h"


class Menu {
public:
	Menu(Editor* pEditor);

	void frame();

private:
	void showNoProject();
	void showProjectList();

	void createProject();

	bool m_windowNew;
	bool m_windowNoProject;
	bool m_windowProjectList;
	bool m_createPhysicsFile = false;
	std::string m_modelName;
	std::vector<std::tuple<std::string, std::string>> m_models;
	int m_selectedModel;
	std::string m_selectedModelName;

	Editor* m_pEditor = nullptr;
};