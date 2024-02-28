#include "project.h"

Project::Project(IProjectCreator* pProjectCreator, IProjectLoader* pProjectLoader,
	IProjectSaver* pProjectSaver, IPackEditor* pPackEditor,
	entt::registry* pRegistry) {
	m_pProjectCreator = pProjectCreator;
	m_pProjectLoader = pProjectLoader;
	m_pProjectSaver = pProjectSaver;
	m_pPackEditor = pPackEditor;
	m_pRegistry = pRegistry;
}

void Project::create(std::string pack, std::string name, bool createPhysicsFile) { 
	m_pRegistry->clear();

	m_pProjectCreator->create(pack + "/models/" + name + "/", createPhysicsFile);
	m_pPackEditor->addModel(name);
}

void Project::load(std::string pack, std::string name) {}

void Project::save() {}
