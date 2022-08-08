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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="file_type_id"></param>
		/// <param name="aliases"></param>
		/// <returns></returns>
		static FileType* addFileType(uint32_t file_type_id, const std::initializer_list<std::string>& aliases);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="alias"></param>
		/// <returns></returns>
		static FileType* getFileTypeFromAlias(const std::string& alias);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="file_type_id"></param>
		/// <returns></returns>
		static FileType* getFileTypeForId(uint32_t file_type_id);

	private:
		inline static FileTypeManager* s_Instance;
		friend class ProjectIo;

	private:
		FileType* m_FileTypes[ENUM_FILE_TYPE_COUNT] = {};
	};

}
