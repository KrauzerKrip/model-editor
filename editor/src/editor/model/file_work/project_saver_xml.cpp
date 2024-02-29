#include "project_saver_xml.h"

#include <pugixml.hpp>


ProjectSaverXml::ProjectSaverXml(eng::IResource* pResource, FileWriter* pFileWriter) { 
	m_pResource = pResource;
	m_pFileWriter = pFileWriter;
}

void ProjectSaverXml::save(std::string dirPath, const ProjectData& projectData) { 
	this->saveModel(dirPath, projectData);
	this->savePhysics(dirPath, projectData);
}

void ProjectSaverXml::saveModel(std::string dirPath, const ProjectData& projectData) {
	std::vector<unsigned char> modelFileBuffer = m_pResource->getFileResource(dirPath + "model.xml");
	pugi::xml_document modelDoc;
	modelDoc.load_buffer(modelFileBuffer.data(), modelFileBuffer.size());
	auto modelRootXml = modelDoc.child("model");
	modelRootXml.child("model_file").text().set(projectData.modelFile.c_str());
	modelRootXml.child("material_type").text().set(projectData.materialType.c_str());
	modelRootXml.child("vertex_shader").text().set(projectData.vertexShader.c_str());
	modelRootXml.child("fragment_shader").text().set(projectData.fragmentShader.c_str());
	modelRootXml.child("physics_file").text().set("physics.xml");

	m_pFileWriter->writeXml(dirPath + "model.xml", modelDoc);
}

void ProjectSaverXml::savePhysics(std::string dirPath, const ProjectData& projectData) {
	pugi::xml_document physicsDoc;
	auto physicsRootXml = physicsDoc.append_child("physics");

	for (auto&& [type, transform] : projectData.colliders) {
		if (type == ColliderType::BOX) {
			auto boxCollider = physicsRootXml.append_child("box_collider");
			auto pos = boxCollider.append_child("position");
			pos.append_attribute("x").set_value(transform.position.x);
			pos.append_attribute("y").set_value(transform.position.y);
			pos.append_attribute("z").set_value(transform.position.z);

			auto rot = boxCollider.append_child("rotation");
			auto angles = glm::eulerAngles(transform.rotation);
			rot.append_attribute("x").set_value(angles.x);
			rot.append_attribute("y").set_value(angles.y);
			rot.append_attribute("z").set_value(angles.z);

			auto scale = boxCollider.append_child("scale");
			scale.append_attribute("x").set_value(transform.scale.x);
			scale.append_attribute("y").set_value(transform.scale.y);
			scale.append_attribute("z").set_value(transform.scale.z);
		}
	}

	m_pFileWriter->writeXml(dirPath + "physics.xml", physicsDoc);
}
