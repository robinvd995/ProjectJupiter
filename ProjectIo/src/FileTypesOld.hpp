/*#pragma once

#include <string>
#include <vector>
#include <algorithm>

#define JPT_IO_FILE_TYPE_UNDEFINED_ID 0						// TODO DOCUMENTATION
#define JPT_IO_FILE_TYPE_UNDEFINED_IDENTIFIER "NULL"		// TODO DOCUMENTATION
#define JPT_IO_FILE_TYPE_INPUT_AMOUNT 16					// TODO DOCUMENTATION
#define JPT_IO_FILE_TYPE_OUTPUT_AMOUNT 16					// TODO DOCUMENTATION

namespace Jupiter::Io {

	enum EnumFileUsage {
		FILE_USAGE_INPUT					= 0,
		FILE_USAGE_OUTPUT					= 1
	};

	enum EnumFileType {
		FILE_TYPE_UNDEFINED					= 0,
		FILE_TYPE_PNG						= 1,
		FILE_TYPE_COLLADA					= 2,
		FILE_TYPE_TEX_RGBA					= 3,
		FILE_TYPE_MODEL_STATIC				= 4
	};

	struct FileType {
		const uint32_t m_Id = 0;
		const std::string m_Identifier;
		const uint32_t m_FileUsage;

		FileType() : m_Id(JPT_IO_FILE_TYPE_UNDEFINED_ID), m_Identifier(JPT_IO_FILE_TYPE_UNDEFINED_IDENTIFIER), m_FileUsage(FILE_USAGE_INPUT) {};
		FileType(FileType&) = delete;
		FileType(const uint32_t id, const std::string& identifier, const uint32_t file_usage) : m_Id(id), m_Identifier(identifier), m_FileUsage(file_usage) {}

		bool isValid() { return m_Id != JPT_IO_FILE_TYPE_UNDEFINED_ID; }
	};

	class FileTypeParser;

	class FileTypeManager {

	public:
		static void addInputFileType(uint32_t id, const std::string& identifier) { getInstance()->localAddInputFileType(id, identifier); }
		static void addOutputFileType(uint32_t id, const std::string& identifier) { getInstance()->localAddOutputFileType(id, identifier); }

		static std::string& getInputStringFromId(uint32_t id) { return getInstance()->localGetInputStringFromId(id); }
		static std::string& getOutputStringFromId(uint32_t id) { return getInstance()->localGetOutputStringFromId(id); }

		static FileType& getInputTypeFromId(uint32_t id) { return  getInstance()->localGetInputTypeFromId(id); }
		static FileType& getOutputTypeFromId(uint32_t id) { return getInstance()->localGetOutputTypeFromId(id); }

	private:
		void localAddInputFileType(uint32_t id, const std::string& identifier) {
			std::string data = identifier;
			std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) { return std::tolower(c); } );
			m_InputFileTypes[id] = { id, data };
		}
		void localAddOutputFileType(uint32_t id, const std::string& identifier) { 
			std::string data = identifier;
			std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) { return std::tolower(c); } );
			m_OutputFileTypes[id] = {id, data };
		}

		std::string& localGetInputStringFromId(uint32_t id) { return m_InputFileTypes[id].m_Identifier; }
		std::string& localGetOutputStringFromId(uint32_t id) { return m_OutputFileTypes[id].m_Identifier; }

		FileType& localGetInputTypeFromId(uint32_t id) { return m_InputFileTypes[id]; }
		FileType& localGetOutputTypeFromId(uint32_t id) { return m_OutputFileTypes[id]; }

		static FileTypeManager* getInstance() { return s_Instance; }

		FileTypeManager() {
			localAddInputFileType(JPT_IO_FILE_TYPE_UNDEFINED_ID, JPT_IO_FILE_TYPE_UNDEFINED_IDENTIFIER);
			localAddOutputFileType(JPT_IO_FILE_TYPE_UNDEFINED_ID, JPT_IO_FILE_TYPE_UNDEFINED_IDENTIFIER);
		}

		FileTypeManager(FileTypeManager&) = delete;

	private:
		FileType m_InputFileTypes[JPT_IO_FILE_TYPE_INPUT_AMOUNT];
		FileType m_OutputFileTypes[JPT_IO_FILE_TYPE_OUTPUT_AMOUNT];

		inline static FileTypeManager* s_Instance;

		friend class FileTypeParser;
		friend class ProjectIo;
	};

	class FileTypeParser {
	public:
		static FileType& parseFileInputTypeFromString(const std::string& value) {
			std::string identifier = value;
			std::transform(identifier.begin(), identifier.end(), identifier.begin(), [](unsigned char c) { return std::tolower(c); });

			for (int i = 0; i < JPT_IO_FILE_TYPE_INPUT_AMOUNT; i++) {
				if (FileTypeManager::s_Instance->m_InputFileTypes[i].m_Identifier == identifier) return FileTypeManager::s_Instance->m_InputFileTypes[i];
			}

			return FileTypeManager::s_Instance->m_InputFileTypes[JPT_IO_FILE_TYPE_UNDEFINED_ID];
		}

		static FileType& parseFileOutputTypeFromString(const std::string& value) {
			std::string identifier = value;
			std::transform(identifier.begin(), identifier.end(), identifier.begin(), [](unsigned char c) { return std::tolower(c); });

			for (int i = 0; i < JPT_IO_FILE_TYPE_OUTPUT_AMOUNT; i++) {
				if (FileTypeManager::s_Instance->m_OutputFileTypes[i].m_Identifier == identifier) return FileTypeManager::s_Instance->m_OutputFileTypes[i];
			}

			return FileTypeManager::s_Instance->m_OutputFileTypes[JPT_IO_FILE_TYPE_UNDEFINED_ID];
		}
	};
}*/
