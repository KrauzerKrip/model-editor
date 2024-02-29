#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_physics/physics_parser.h"


struct ProjectData {
	std::string modelFile;
	std::string materialType;
	std::string vertexShader;
	std::string fragmentShader;
	std::vector<ColliderData> colliders;
};