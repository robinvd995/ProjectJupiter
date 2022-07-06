#include "ColladaLoader.h"

#include <filesystem>

namespace Jupiter::Io {

	ColladaLoader::ColladaLoader() {}
	ColladaLoader::~ColladaLoader() {}

	ModelMesh* ColladaLoader::processMesh(aiMesh* aimesh) {
		ModelMesh* modelMesh = new ModelMesh();

		bool hasPosition = aimesh->HasPositions();
		bool hasTextureCoords0 = aimesh->HasTextureCoords(0);
		bool hasNormals = aimesh->HasNormals();
		bool hasFaces = aimesh->HasFaces();

		// Allocate buffers
		if (hasPosition) modelMesh->vertexPositionBuffer.allocate(aimesh->mNumVertices * (size_t)3);
		if (hasTextureCoords0) modelMesh->textureCoordinateBuffer.allocate(aimesh->mNumVertices * (size_t)2);
		if (hasNormals) modelMesh->vertexNormalBuffer.allocate(aimesh->mNumVertices * (size_t)3);

		if (hasFaces) {
			modelMesh->hasIndexBuffer = true;
			modelMesh->indexBuffer.allocate((size_t)aimesh->mNumFaces * (size_t)aimesh->mFaces[0].mNumIndices);
		}

		// Write vertex data
		for (uint32_t i = 0; i < aimesh->mNumVertices; i++) {

			// Vertex positions
			if (hasPosition) {
				modelMesh->vertexPositionBuffer.write(aimesh->mVertices[i].x);
				modelMesh->vertexPositionBuffer.write(aimesh->mVertices[i].y);
				modelMesh->vertexPositionBuffer.write(aimesh->mVertices[i].z);
			}

			// Texture Coordinates
			if (hasTextureCoords0) {
				modelMesh->textureCoordinateBuffer.write(aimesh->mTextureCoords[0][i].x);
				modelMesh->textureCoordinateBuffer.write(aimesh->mTextureCoords[0][i].y);
			}

			// Vertex Normals
			if (hasNormals) {
				modelMesh->vertexNormalBuffer.write(aimesh->mNormals[i].x);
				modelMesh->vertexNormalBuffer.write(aimesh->mNormals[i].y);
				modelMesh->vertexNormalBuffer.write(aimesh->mNormals[i].z);
			}
		}

		// Write index data
		for (uint32_t i = 0; i < aimesh->mNumFaces; i++) {
			aiFace& face = aimesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++) {
				modelMesh->indexBuffer.write(face.mIndices[j]);
			}
		}

		// Set layout
		uint32_t m_LocationIndex = 0;
		if (hasPosition) modelMesh->meshLayout.layoutEntries.push_back({ MeshLayoutType::VertexPositions, MeshLayoutDataType::Float3, m_LocationIndex++ });
		if (hasTextureCoords0) modelMesh->meshLayout.layoutEntries.push_back({ MeshLayoutType::TextureCoordinates0, MeshLayoutDataType::Float2, m_LocationIndex++ });
		if (hasNormals) modelMesh->meshLayout.layoutEntries.push_back({ MeshLayoutType::VertexNormals, MeshLayoutDataType::Float3, m_LocationIndex++ });

		return modelMesh;
	}

	void ColladaLoader::addMeshToMap(ModelAsset* model, ModelMeshNode* node, ModelMesh* mesh, uint32_t index) {
		std::string name = std::string(node->name).append("_").append(std::to_string(index));
		model->insertMesh(name, mesh);
	}

	void ColladaLoader::processNode(aiNode* node, const aiScene* scene, ModelMeshNode* meshNode, ModelAsset* model) {

		meshNode->name = std::string(node->mName.C_Str());

		for (uint32_t i = 0; i < node->mNumMeshes; i++) {
			aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];

			if (!aimesh) continue;
			ModelMesh* modelmesh = processMesh(aimesh);
			meshNode->meshes.push_back(modelmesh);
			addMeshToMap(model, meshNode, modelmesh, i);
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++) {

			aiNode* childainode = node->mChildren[i];
			if (childainode->mNumChildren == 0 && childainode->mNumMeshes == 0) continue;

			ModelMeshNode* child = new ModelMeshNode();
			processNode(childainode, scene, child, model);
			meshNode->children.push_back(child);
		}
	}

	void ColladaLoader::loadColladaModel(const std::string& filepath, ModelAsset* model) {
		bool exists = std::filesystem::exists(filepath);
		//SLD_CORE_ASSERT(exists, "Error while loading model, could not find file {0}!", filepath);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
		//SLD_CORE_ASSERT(scene, "Error while loading model {0}!", filepath);

		if (scene->HasMeshes()) {
			ModelMeshNode* rootnode = new ModelMeshNode();
			model->setRootNode(rootnode);
			processNode(scene->mRootNode, scene, rootnode, model);
		}
	}

}