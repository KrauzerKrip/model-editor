#pragma once

#include "i_project_loader.h"

#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_physics/physics_parser.h"


class ProjectLoaderXml : public IProjectLoader {
public:
	ProjectLoaderXml(eng::IResource* pResource, PhysicsParser* pPhysicsParser);

	ProjectData load(std::string dirPath);

private:
	void loadModel(std::string dirPath, ProjectData& projectData);
	void loadPhysics(std::string dirPath, std::string physicsFile, ProjectData &projectData);

	eng::IResource* m_pResource = nullptr;
	PhysicsParser* m_pPhysicsParser = nullptr;
};