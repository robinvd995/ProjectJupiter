#include "FileTypes.h"

namespace Jupiter::Io {

	// ----- START FileType -----

	FileType::FileType(const uint32_t file_type_id, const std::initializer_list<std::string>& aliases) :
		m_FileTypeId(file_type_id),
		m_Aliases(aliases)
	{

	}

	FileType::~FileType() {

	}

	const uint32_t FileType::getFileTypeId() const {
		return m_FileTypeId;
	}

	// -----  END  FileType -----


	// ----- START FileTypeManager -----

	FileTypeManager::FileTypeManager() {

	}

	FileTypeManager::~FileTypeManager() {
		for (int i = 0; i < ENUM_FILE_TYPE_COUNT; i++) {
			FileType* ft = s_Instance->m_FileTypes[i];
			if (!ft) continue;
			delete ft;
		}
	}

	FileType* FileTypeManager::addFileType(uint32_t file_type_id, const std::initializer_list<std::string>& aliases) {
		if (s_Instance->m_FileTypes[file_type_id]) return s_Instance->m_FileTypes[file_type_id];
		FileType* fileType = new FileType(file_type_id, aliases);
		s_Instance->m_FileTypes[file_type_id] = fileType;
		return fileType;
	}

	FileType* FileTypeManager::getFileTypeFromAlias(const std::string& alias) {
		for (int i = 0; i < ENUM_FILE_TYPE_COUNT; i++) {
			FileType* ft = s_Instance->m_FileTypes[i];
			if (!ft) continue;
			for (const std::string& ftAlias : ft->m_Aliases)
				if (alias == ftAlias) return ft;
		}
		return nullptr;
	}

	FileType* FileTypeManager::getFileTypeForId(uint32_t file_type_id) {
		return s_Instance->m_FileTypes[file_type_id];
	}

	// -----  END  FileTypeManager -----

}
