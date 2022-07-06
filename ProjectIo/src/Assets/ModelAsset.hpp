#pragma once

#include <vector>
#include <map>

#include "JupiterCore/DataBuffers.hpp"

#include "AssetBase.h"

namespace Jupiter::Io {

	enum class MeshLayoutType {
		Unknown = 0,
		VertexPositions = 1,
		TextureCoordinates0 = 2,
		VertexNormals = 3
	};

	typedef std::map<MeshLayoutType, char*> MeshBufferMap;

	enum class MeshLayoutDataType {
		Int = 0, Int2 = 1, Int3 = 2, Int4 = 3,
		Uint = 4, Uint2 = 5, Uint3 = 6, Uint4 = 7,
		Float = 8, Float2 = 9, Float3 = 10, Float4 = 11,
		Double = 12, Double2 = 13, Double3 = 14, Double4 = 15
	};

	inline size_t meshLayoutDataTypeSizeMap[] = {
		4,  8,  12, 16,
		4,  8,  12, 16,
		4,  8,  12, 16,
		8,  16, 24, 32
	};

	inline uint32_t meshLayoutDataTypeComponentCountMap[] = {
		1,  2,  3,  4,
		1,  2,  3,  4,
		1,  2,  3,  4,
		1,  2,  3,  4
	};

	typedef uint32_t MeshLayoutLocation;

	struct MeshLayoutEntry {
		MeshLayoutType type;
		MeshLayoutDataType data;
		MeshLayoutLocation location;

		MeshLayoutEntry(MeshLayoutType p_type, MeshLayoutDataType p_data, MeshLayoutLocation p_location) :
			type(p_type), data(p_data), location(p_location)
		{}
	};

	struct MeshLayout {
		std::vector<MeshLayoutEntry> layoutEntries;
	};

	struct ModelMesh {
		Core::FloatBuffer vertexPositionBuffer;
		Core::FloatBuffer textureCoordinateBuffer;
		Core::FloatBuffer vertexNormalBuffer;

		Core::UInt32Buffer indexBuffer;
		bool hasIndexBuffer;

		MeshLayout meshLayout;
	};

	struct ModelMeshNode {
		std::string name;
		std::vector<ModelMesh*> meshes;
		std::vector<ModelMeshNode*> children;
	};

	class ModelAsset : public AssetBase {

	public:
		typedef std::map<std::string, ModelMesh*> ModelMeshMap;

		ModelAsset() = default;

		~ModelAsset() {
			deleteModelMeshNode(m_RootNode);
			m_MeshMap.clear();
		};

		void deleteModelMeshNode(ModelMeshNode* node) {
			for (auto child : node->children) deleteModelMeshNode(child);
			for (auto mesh : node->meshes) delete mesh;
			delete node;
		}

		void setFileName(const std::string& filename) { m_FileName = filename; }
		const std::string& getFileName() { return m_FileName; }

		ModelMeshMap& getMeshMap() { return m_MeshMap; }

		virtual size_t getAssetSize() override { return 0; }
		virtual char* getAssetSource() override { return nullptr; }

		void insertMesh(const std::string& name, ModelMesh* mesh) { m_MeshMap.insert({ name, mesh }); }
		void setRootNode(ModelMeshNode* rootnode) { m_RootNode = rootnode; }
		ModelMeshNode* getRootNode() { return m_RootNode; }

	private:
		// Should have no meshes attached to it, just children
		ModelMeshNode* m_RootNode = nullptr;

		// A map containing all the meshes of the model identified by its meshId
		ModelMeshMap m_MeshMap;

		std::string m_FileName = "unknown.model";
	};

}
