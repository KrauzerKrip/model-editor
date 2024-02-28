#include "pack_editor_json.h"

#include <fstream>

#include <nlohmann/json.hpp>


using json = nlohmann::json;


PackEditorJson::PackEditorJson(std::string pack, eng::IResource* pResource, FileWriter* pFileWriter) { 
	m_pack = pack;
	m_pResource = pResource;
	m_pFileWriter = pFileWriter;
}

void PackEditorJson::addModel(std::string name) {
	std::vector<unsigned char> buffer = m_pResource->getFileResource(m_pack + "/pack.json");
	auto descriptor = json::parse(buffer);
	auto& models = descriptor.at("models");
	models[name] = m_pack + "/models/" + name + "/";

	m_pFileWriter->writeJson(m_pack + "/pack.json", descriptor);
}
