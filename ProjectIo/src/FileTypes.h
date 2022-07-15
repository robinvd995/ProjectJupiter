#pragma once

#include <string>
#include <vector>

#define JPT_IO_FILE_TYPE_COUNT 5

namespace Jupiter::Io {

	class FileType {

	public:
		FileType(const uint32_t file_type_id, const uint32_t file_usage, const std::initializer_list<std::string>& aliases);
		~FileType();

	private:
		const uint32_t m_FileTypeId;
		const uint32_t m_UsageFlags = 0;
		const std::vector<std::string> m_Aliases;

		friend class FileTypeManager;
		friend class ProjectIo;
	};

	class FileTypeManager {

	public:
		FileTypeManager();
		~FileTypeManager();

		static FileType* addFileType(uint32_t file_type_id, uint32_t file_usage, const std::initializer_list<std::string>& aliases);

		static FileType* getFileTypeFromAlias(const std::string& alias);
		static FileType* getFileTypeForId(uint32_t file_type_id);

	private:
		inline static FileTypeManager* s_Instance;
		friend class ProjectIo;

	private:
		FileType* m_FileTypes[JPT_IO_FILE_TYPE_COUNT] = {};
	};

}

