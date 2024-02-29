#include "project_creator_xml.h"

#include <iostream>

#include <filesystem>
#include <pugixml.hpp>

#include "lc_client/tier0/tier0.h"



ProjectCreatorXml::ProjectCreatorXml(eng::IResource* pResource, FileWriter* pFileWriter) {
	m_pFileWriter = pFileWriter;
}

void ProjectCreatorXml::create(std::string dirPath, bool createPhysicsFile) { 
	m_pFileWriter->createDirectory(dirPath);

	pugi::xml_document docModel;

	auto modelXml = docModel.append_child("model");
	modelXml.append_child("model_file");
	modelXml.append_child("material_type");
	modelXml.append_child("vertex_shader");
	modelXml.append_child("fragment_shader");

	if (createPhysicsFile) {
		modelXml.append_child("physics_file");

		pugi::xml_document docPhysics;
		docPhysics.append_child("physics");

		m_pFileWriter->writeXml(dirPath + "physics.xml", docPhysics);
	}

	m_pFileWriter->writeXml(dirPath + "model.xml", docModel);
}

