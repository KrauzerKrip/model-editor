#pragma once

#include <string>

#include "project_data.h"


class IProjectLoader {
public:
	virtual ~IProjectLoader() = default;

	virtual ProjectData load(std::string dirPath) = 0;
};
