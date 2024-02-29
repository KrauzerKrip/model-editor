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

	m_pack = pack;
	m_name = name;
}

void Project::load(std::string pack, std::string name) {
	m_pack = pack;
	m_name = name;

	ProjectData projectData = m_pProjectLoader->load(pack + "/models/" + name + "/");

	m_modelFile = projectData.modelFile;
	m_materialType = projectData.materialType;
	m_vertexShader = projectData.vertexShader;
	m_fragmentShader = projectData.fragmentShader;

	for (auto& callback : m_loadCallbacks) {
		callback();
	}
}

void Project::save() { 
	ProjectData projectData;
	projectData.modelFile = m_modelFile;
	projectData.materialType = m_materialType;
	projectData.vertexShader = m_vertexShader;
	projectData.fragmentShader = m_fragmentShader;
	
	if (m_name.empty()) {
		throw NoProjectException("No project loaded.");
	}

	m_pProjectSaver->save(m_pack + "/models/" + m_name + "/", projectData);
}

void Project::addLoadingCallback(std::function<void()> callback) { m_loadCallbacks.push_back(callback); }

std::string Project::getPack() const { return m_pack; }

std::string Project::getName() const { return m_name; }
