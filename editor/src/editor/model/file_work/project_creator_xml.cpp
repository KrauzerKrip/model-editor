#include "project_creator_xml.h"

#include <iostream>

#include <filesystem>
#include <pugixml.hpp>

#include "lc_client/tier0/tier0.h"



ProjectCreatorXml::ProjectCreatorXml(eng::IResource* pResource) {}

void ProjectCreatorXml::create(std::string dirPath, bool createPhysicsFile) { 
	std::filesystem::directory_entry dir(dirPath);
	if (!dir.exists()) {
		std::filesystem::create_directory(dir);
	}

	pugi::xml_document doc;

	auto modelXml = doc.append_child("model");
	modelXml.append_child("model_file");
	modelXml.append_child("material_type");
	modelXml.append_child("vertex_shader");
	modelXml.append_child("fragment_shader");

	if (createPhysicsFile) {
		modelXml.append_child("physics_file");
	}

	doc.print(std::cout);
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
