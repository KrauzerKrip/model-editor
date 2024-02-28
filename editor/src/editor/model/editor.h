#pragma once

#include <entt/entt.hpp>

#include "lc_client/util/i_eng_resource.h"
#include "project.h"


class Editor {
public:
	Editor(entt::registry* pRegistry, eng::IResource* pResource);

	Project& getProject();

private:
	Project m_project;
};