#include "file_writer.h"

#include <fstream>


struct XmlStringWriter : pugi::xml_writer {
	std::string result = "<?xml version=\" 1.0 \" encoding=\" utf - 8 \"?>\n\n";

	virtual void write(const void* data, size_t size) { result.append(static_cast<const char*>(data), size); }
};


FileWriter::FileWriter(std::string resPath) { m_resPath = resPath; }

void FileWriter::writeJson(std::string filePath, const json& json) { 
	std::ofstream stream(m_resPath + filePath);

	if (!stream.is_open()) {
		throw FileWriteException(m_resPath + filePath);
	}
	else {
		stream << json;
		stream.close();
	}
}

void FileWriter::writeXml(std::string filePath, const pugi::xml_document& xml) {
	XmlStringWriter writer;
	xml.print(writer);
	writeString(filePath, writer.result);
}

void FileWriter::writeString(std::string filePath, const std::string& data) {
	std::ofstream stream(m_resPath + filePath);

	if (!stream.is_open()) {
		throw FileWriteException(m_resPath + filePath);
	}
	else {
		stream << data;
		stream.close();
	}
}

void FileWriter::createDirectory(std::string dirPath) {
	std::filesystem::directory_entry dir(m_resPath + dirPath);
	if (!dir.exists()) {
		std::filesystem::create_directory(dir);
	}
}
