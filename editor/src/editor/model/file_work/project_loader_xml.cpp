#include "project_loader_xml.h"

#include <pugixml.hpp>


ProjectLoaderXml::ProjectLoaderXml(eng::IResource* pResource, PhysicsParser* pPhysicsParser) {
	m_pResource = pResource;
	m_pPhysicsParser = pPhysicsParser;
}

ProjectData ProjectLoaderXml::load(std::string dirPath) { 
	ProjectData projectData;

	this->loadModel(dirPath, projectData);

	return projectData;
}

void ProjectLoaderXml::loadModel(std::string dirPath, ProjectData& projectData) {
	std::vector<unsigned char> modelFileBuffer = m_pResource->getFileResource(dirPath + "model.xml");
	pugi::xml_document modelDoc;
	modelDoc.load_buffer(modelFileBuffer.data(), modelFileBuffer.size());

	auto modelRootXml = modelDoc.child("model");
	projectData.modelFile = modelRootXml.child("model_file").text().as_string();
	projectData.materialType = modelRootXml.child("material_type").text().as_string();
	projectData.vertexShader = modelRootXml.child("vertex_shader").text().as_string();
	projectData.fragmentShader = modelRootXml.child("fragment_shader").text().as_string();

	if (!modelRootXml.child("physics_file").empty()) {
		this->loadPhysics(dirPath, modelRootXml.child("physics_file").text().as_string(), projectData);
	}
}

void ProjectLoaderXml::loadPhysics(std::string dirPath, std::string physicsFile, ProjectData& projectData) {
	projectData.colliders = m_pPhysicsParser->parse(dirPath + physicsFile);
}
