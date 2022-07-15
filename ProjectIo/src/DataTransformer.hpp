#pragma once

#include "Transformers/DataTransformerPng.hpp"
#include "Transformers/DataTransformerCollada.hpp"

namespace Jupiter::Io {

	typedef char* (*DataTransformFunction)(LoadedAsset);

	class DataTransformManager {

	public:
		static void addDataTransformer(uint32_t inputtype, uint32_t outputtype, DataTransformFunction func) { getInstance()->localAddDataTransformer(inputtype, outputtype, func); }
		static const DataTransformFunction getTransformFunction(uint32_t inputtype, uint32_t outputtype) { return getInstance()->localGetTransformFunction(inputtype, outputtype); }
	private:
		void localAddDataTransformer(uint32_t inputtype, uint32_t outputtype, DataTransformFunction func) { m_DataTransformFunctions[inputtype][outputtype] = func; }
		DataTransformFunction localGetTransformFunction(uint32_t inputtype, uint32_t outputtype) { return m_DataTransformFunctions[inputtype][outputtype]; }

		static DataTransformManager* getInstance() { return s_Instance; }

		DataTransformManager() {}
		DataTransformManager(DataTransformManager&) = delete;

	private:
		DataTransformFunction m_DataTransformFunctions[1][1] = { };

		inline static DataTransformManager* s_Instance = nullptr;

		friend class ProjectIo;
	};
}
