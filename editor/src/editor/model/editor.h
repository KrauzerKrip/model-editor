#pragma once

#include <entt/entt.hpp>

#include "lc_client/util/i_eng_resource.h"
#include "project.h"
#include "file_work/file_writer.h"


class Editor {
public:
	Editor(entt::registry* pRegistry, eng::IResource* pResource, FileWriter* pFileWriter);

	Project& getProject();
	void loadModel();
	 
private:
	Project m_project;
};