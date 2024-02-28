#include "file_writer.h"

#include <fstream>


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
