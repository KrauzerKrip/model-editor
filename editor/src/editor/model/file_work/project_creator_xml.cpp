#include "project_creator_xml.h"

#include <iostream>

#include <filesystem>
#include <pugixml.hpp>

#include "lc_client/tier0/tier0.h"


struct XmlStringWriter : pugi::xml_writer {
	std::string result = "<?xml version=\" 1.0 \" encoding=\" utf - 8 \"?>\n\n";

	virtual void write(const void* data, size_t size) { result.append(static_cast<const char*>(data), size); }
};


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

		XmlStringWriter writer;
		docPhysics.print(writer);
		m_pFileWriter->writeString(dirPath + "physics.xml", writer.result);
	}

	XmlStringWriter writer;
	docModel.print(writer);
	m_pFileWriter->writeString(dirPath + "model.xml", writer.result);
}

