#pragma once

#include "LoaderCommon.h"

#include "Assets/ModelAsset.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <string>

namespace Jupiter::Io {

	class ColladaLoader {

	public:
		ColladaLoader();
		~ColladaLoader();

		
		void loadColladaModel(const std::string& filepath, ModelAsset* asset);

	private:
		ModelMesh* processMesh(aiMesh* aimesh);
		void addMeshToMap(ModelAsset* model, ModelMeshNode* node, ModelMesh* mesh, uint32_t index);
		void processNode(aiNode* node, const aiScene* scene, ModelMeshNode* meshNode, ModelAsset* model);
	};

}
