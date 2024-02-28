#pragma once

#include <string>

#include <entt/entt.hpp>

#include "file_work/i_project_creator.h"
#include "file_work/i_project_loader.h"
#include "file_work/i_project_saver.h"
#include "file_work/i_pack_editor.h"


class Project {
public:
	Project(IProjectCreator* pProjectCreator, IProjectLoader* pProjectLoader, IProjectSaver* pProjectSaver, IPackEditor* pPackEditor, entt::registry* pRegistry);

	void create(std::string pack, std::string name, bool createPhysicsFile);
	void load(std::string pack, std::string name);
	void save();

private:
	IProjectCreator* m_pProjectCreator = nullptr;
	IProjectLoader* m_pProjectLoader = nullptr;
	IProjectSaver* m_pProjectSaver = nullptr;
	IPackEditor* m_pPackEditor = nullptr;
	entt::registry* m_pRegistry = nullptr;
};