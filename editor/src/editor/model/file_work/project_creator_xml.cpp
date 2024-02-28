#include "project_creator_xml.h"

#include <iostream>

#include <filesystem>
#include <pugixml.hpp>

#include "lc_client/tier0/tier0.h"


struct XmlStringWriter : pugi::xml_writer {
	std::string result;

	virtual void write(const void* data, size_t size) { result.append(static_cast<const char*>(data), size); }
};


ProjectCreatorXml::ProjectCreatorXml(eng::IResource* pResource, FileWriter* pFileWriter) {
	m_pFileWriter = pFileWriter;
}

void ProjectCreatorXml::create(std::string dirPath, bool createPhysicsFile) { 
	m_pFileWriter->createDirectory(dirPath);

	pugi::xml_document doc;

	auto modelXml = doc.append_child("model");
	modelXml.append_child("model_file");
	modelXml.append_child("material_type");
	modelXml.append_child("vertex_shader");
	modelXml.append_child("fragment_shader");

	if (createPhysicsFile) {
		modelXml.append_child("physics_file");
	}

	XmlStringWriter writer;
	doc.print(writer);
	m_pFileWriter->writeString(dirPath + "model.xml", writer.result);
}


//<?xml version="1.0" encoding="utf-8"?>
//
//<model>
//  <model_file>model.dae</model_file>
//  <material_type>sg</material_type>
//  <vertex_shader>base</vertex_shader>
//  <fragment_shader>lighting</fragment_shader>
//  <physics_file>physics.xml</physics_file>
//</model>
