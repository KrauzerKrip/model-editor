#pragma once

#include <unordered_map> 

#include <entt/entt.hpp>

#include "lc_client/util/eng_resource.h"
#include "entt/components.h"
#include "lc_client/tier1/openGL/gl_texture_manager.h"
#include "lc_client/tier0/console/i_console.h"

class ModelManager {

public:
	ModelManager(eng::IResource* pResource, TextureManager* pTextureManager, entt::registry& pUtilRegistry, IConsole* pConsole);

	Model* getModel(const std::string modelPath, const std::string texturesDirPath, const std::string materialType);

private :
	Model* loadModel(const std::string modelPath, const std::string texturesDirPath, const std::string materialType);

	std::unordered_map<std::string, Model*> m_modelMap;

	eng::IResource* m_pResource;
	TextureManager* m_pTextureManager;
	entt::registry* m_pUtilRegistry;
	IConsole* m_pConsole;

	const static std::string FILE_FORMAT;
	const static std::string ERROR_MODEL_PATH;
};
