#pragma once

#include <string>
#include <stdexcept>

#include <entt/entt.hpp>

#include "file_work/i_project_creator.h"
#include "file_work/i_project_loader.h"
#include "file_work/i_project_saver.h"
#include "file_work/i_pack_editor.h"


class NoProjectException : public std::runtime_error {
public:
	NoProjectException(std::string msg) : std::runtime_error(msg) {}
};


class Project {
public:
	Project(IProjectCreator* pProjectCreator, IProjectLoader* pProjectLoader, IProjectSaver* pProjectSaver, IPackEditor* pPackEditor, entt::registry* pRegistry);

	void create(std::string pack, std::string name, bool createPhysicsFile);
	void load(std::string pack, std::string name);
	void save();

	std::string m_modelFile;
	std::string m_materialType;
	std::string m_vertexShader;
	std::string m_fragmentShader;

private:
	IProjectCreator* m_pProjectCreator = nullptr;
	IProjectLoader* m_pProjectLoader = nullptr;
	IProjectSaver* m_pProjectSaver = nullptr;
	IPackEditor* m_pPackEditor = nullptr;
	entt::registry* m_pRegistry = nullptr;

	std::string m_pack;
	std::string m_name;
};