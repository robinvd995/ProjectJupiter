#pragma once

#include <string>
#include <vector>

#include "FileDefinitions.h"

namespace Jupiter::Io {

	class FileType {

	public:
		FileType(const uint32_t file_type_id, const std::initializer_list<std::string>& aliases);
		~FileType();

		const uint32_t getFileTypeId() const;

	private:
		const uint32_t m_FileTypeId;
		const std::vector<std::string> m_Aliases;

		friend class FileTypeManager;
		friend class ProjectIo;
	};

	class FileTypeManager {

	public:
		FileTypeManager();
		~FileTypeManager();

		static FileType* addFileType(uint32_t file_type_id, const std::initializer_list<std::string>& aliases);

		static FileType* getFileTypeFromAlias(const std::string& alias);
		static FileType* getFileTypeForId(uint32_t file_type_id);

	private:
		inline static FileTypeManager* s_Instance;
		friend class ProjectIo;

	private:
		FileType* m_FileTypes[ENUM_FILE_TYPE_COUNT] = {};
	};

}
