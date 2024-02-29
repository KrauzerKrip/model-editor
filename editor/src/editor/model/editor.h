#pragma once

#include <entt/entt.hpp>

#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_physics/physics_parser.h"
#include "project.h"
#include "file_work/file_writer.h"


class Editor {
public:
	Editor(
		entt::registry* pRegistry, eng::IResource* pResource, FileWriter* pFileWriter, PhysicsParser* pPhysicsParser);

	Project& getProject();
	void loadModel();
	 
private:
	Project m_project;

	entt::registry* m_pRegistry = nullptr;
};