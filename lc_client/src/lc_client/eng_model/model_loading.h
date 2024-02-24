#pragma once

#include <vector>

#include <entt/entt.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "entt/components.h"
#include "lc_client/tier1/openGL/gl_texture_manager.h"
#include "lc_client/util/eng_resource.h"


namespace eng {

	class ModelLoading {

	public:
		ModelLoading(std::string modelPath, std::string texturesDirPath, std::string materialType,
			std::string fileFormat, eng::IResource* pResource, TextureManager* pTextureManager,
			entt::registry* pUtilRegistry);
		Model* loadModel();
		std::vector<MaterialSG>& getMeshesMaterialsSG();

	private:
		void processNode(aiNode* node, const aiScene* scene, Model* pModel);

		Mesh processMesh(aiMesh* pMesh, const aiScene* scene);

		void processVertices(aiMesh* pMesh, std::vector<Vertex>& vertices);
		void processIndices(aiMesh* pMesh, std::vector<unsigned int>& indices);
		MaterialMR getMaterialMR(aiMaterial* pMaterial);
		MaterialSG getMaterialSG(aiMaterial* pMaterial);


		const std::string m_modelPath;
		const std::string m_texturesDirPath;
		const std::string m_fileFormat;
		const std::string m_materialType;
		eng::IResource* m_pResource = nullptr;
		TextureManager* m_pTextureManager = nullptr;
		std::vector<MaterialSG> m_materials;
		entt::registry* m_pUtilRegistry;
	};
}
