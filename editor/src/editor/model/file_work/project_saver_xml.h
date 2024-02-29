#pragma once

#include "lc_client/util/i_eng_resource.h"
#include "i_project_saver.h"
#include "file_writer.h"


class ProjectSaverXml : public IProjectSaver {
public:
	ProjectSaverXml(eng::IResource* pResource, FileWriter* pFileWriter);

	void save(std::string dirPath, const ProjectData& projectData) override;

private:
	void saveModel(std::string dirPath, const ProjectData& projectData);
	void savePhysics(std::string dirPath, const ProjectData& projectData);

	eng::IResource* m_pResource = nullptr;
	FileWriter* m_pFileWriter = nullptr;
};