#include "pack_editor_json.h"

#include <fstream>

#include <nlohmann/json.hpp>


using json = nlohmann::json;


PackEditorJson::PackEditorJson(eng::IResource* pResource, FileWriter* pFileWriter) { 
	m_pResource = pResource;
	m_pFileWriter = pFileWriter;
}

void PackEditorJson::addModel(std::string pack, std::string name) {
	std::vector<unsigned char> buffer = m_pResource->getFileResource(pack + "/pack.json");
	auto descriptor = json::parse(buffer);
	auto& models = descriptor.at("models");
	models[name] = pack + "/models/" + name + "/";

	m_pFileWriter->writeJson(pack + "/pack.json", descriptor);
}

std::vector<std::tuple<std::string, std::string>> PackEditorJson::getPackModels(std::string pack) {
	std::vector<unsigned char> buffer = m_pResource->getFileResource(pack + "/pack.json");
	auto descriptor = json::parse(buffer);
	auto& modelsJson = descriptor.at("models");

	std::vector<std::tuple<std::string, std::string>> models; 

	for (auto& model : modelsJson.items()) {
		models.push_back(std::make_tuple(static_cast<std::string>(model.key()), static_cast<std::string>(model.value())));
	}

	return models;
}
