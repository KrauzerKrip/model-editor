#pragma once

#include <string>

#include <entt/entt.hpp>

#include "file_work/i_project_creator.h"
#include "file_work/i_project_loader.h"
#include "file_work/i_project_saver.h"


class Project {
public:
	Project(std::string modelDir, IProjectCreator* pProjectCreator, IProjectLoader* pProjectLoader, IProjectSaver* pProjectSaver, entt::registry* pRegistry);

	void create(std::string name, bool createPhysicsFile);
	void load(std::string name);
	void save();

private:
	IProjectCreator* m_pProjectCreator;
	IProjectLoader* m_pProjectLoader;
	IProjectSaver* m_pProjectSaver;
	entt::registry* m_pRegistry = nullptr;
	std::string m_modelDir;
};