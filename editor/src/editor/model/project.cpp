#include "project.h"

Project::Project(std::string modelDir, IProjectCreator* pProjectCreator, IProjectLoader* pProjectLoader,
	IProjectSaver* pProjectSaver,
	entt::registry* pRegistry) {
	m_modelDir = modelDir;
	m_pProjectCreator = pProjectCreator;
	m_pProjectLoader = pProjectLoader;
	m_pProjectSaver = pProjectSaver;
	m_pRegistry = pRegistry;
}

void Project::create(std::string name, bool createPhysicsFile) { 
	m_pRegistry->clear();

	m_pProjectCreator->create(m_modelDir + name, createPhysicsFile);
}

void Project::load(std::string name) {}

void Project::save() {}
