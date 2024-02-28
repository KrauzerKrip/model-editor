#pragma once

#include <string>

#include "project_data.h"


class IProjectSaver {
public:
	virtual ~IProjectSaver() = default;

	virtual void save(const ProjectData& data) = 0;
};

