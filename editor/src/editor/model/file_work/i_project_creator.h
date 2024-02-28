#pragma once

#include <string>
#include <stdexcept>


class ProjectExistsException : public std::runtime_error {
public:
	ProjectExistsException() : std::runtime_error("Project already exists.") {}
};


class IProjectCreator {
public:
	virtual ~IProjectCreator() = default;

	virtual void create(std::string dirPath, bool createPhysicsFile) = 0;
};