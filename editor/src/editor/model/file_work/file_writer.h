#pragma once

#include <string>

#include <nlohmann/json.hpp>
#include <pugixml.hpp>


using json = nlohmann::json;


#include <stdexcept>

class FileWriteException : public std::runtime_error {
public:
	FileWriteException(std::string path) : std::runtime_error("Can't write file: " + path) {}
};


class FileWriter {
public:
	FileWriter(std::string absoluteResPath);

	void writeJson(std::string filePath, const json& json);
	void writeXml(std::string filePath, const pugi::xml_document& xml);
	void writeString(std::string filePath, const std::string& data);
	void createDirectory(std::string dirPath);

private:
	std::string m_resPath;
};