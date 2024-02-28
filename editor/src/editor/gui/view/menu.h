#pragma once

#include "editor/model/project.h"


class Menu {
public:
	Menu(Project& project);

	void frame();

private:
	void createProject();

	bool m_windowNew;
	bool m_createPhysicsFile = false;
	std::string m_modelName;

	Project& m_project;
};