#pragma once

#include "Transformers/DataTransformerPng.hpp"

namespace Jupiter::Io {

	typedef char* (*DataTransformFunction)(void*);

	class DataTransformManager {

	public:
		static void addDataTransformer(uint32_t inputtype, uint32_t outputtype, DataTransformFunction func) { getInstance()->localAddDataTransformer(inputtype, outputtype, func); }
		static const DataTransformFunction getTransformFunction(uint32_t inputtype, uint32_t outputtype) { return getInstance()->localGetTransformFunction(inputtype, outputtype); }
	private:
		void localAddDataTransformer(uint32_t inputtype, uint32_t outputtype, DataTransformFunction func) { m_DataTransformFunctions[inputtype][outputtype] = func; }
		DataTransformFunction localGetTransformFunction(uint32_t inputtype, uint32_t outputtype) { return m_DataTransformFunctions[inputtype][outputtype]; }

		static DataTransformManager* getInstance() { if (!s_Instance) s_Instance = new DataTransformManager(); return s_Instance; }

		DataTransformManager() {}
		DataTransformManager(DataTransformManager&) = delete;

	private:
		DataTransformFunction m_DataTransformFunctions[JPT_IO_FILE_TYPE_INPUT_AMOUNT][JPT_IO_FILE_TYPE_OUTPUT_AMOUNT] = { };

		inline static DataTransformManager* s_Instance = nullptr;
	};
}
