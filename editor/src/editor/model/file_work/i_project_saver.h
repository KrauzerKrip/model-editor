#pragma once

#include <string>

#include "project_data.h"


class IProjectSaver {
public:
	virtual ~IProjectSaver() = default;

	virtual void save(std::string dirPath, const ProjectData& projectData) = 0;
};

