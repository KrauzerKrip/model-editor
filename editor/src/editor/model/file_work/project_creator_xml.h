#pragma once

#include <string>

#include "editor/model/file_work/i_project_creator.h"
#include "lc_client/util/i_eng_resource.h"


class ProjectCreatorXml : public IProjectCreator {
public:
	ProjectCreatorXml(eng::IResource* pResource);

	void create(std::string dirPath, bool createPhysicsFile) override;

private:
	eng::IResource* m_pResource = nullptr;
};