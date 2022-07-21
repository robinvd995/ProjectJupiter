#pragma once

#include <vector>

namespace Jupiter::Io {

	class MemoryManager {

	public:
		MemoryManager();
		~MemoryManager();

	//private:
		inline static MemoryManager* s_Instance;

	//private:
		std::vector<void*> m_AllocatedPointers;
		friend class ProjectIo;
	};

	template<typename T, typename ...Args>
	constexpr T* createPtr(Args&&... args) {
		T* ptr = new T(args...);
		MemoryManager::s_Instance->m_AllocatedPointers.push_back(ptr);
		return ptr;
	}

	template<typename T>
	constexpr void deletePtr(T* ptr) {
		for (int i = 0; i < MemoryManager::s_Instance->m_AllocatedPointers.size(); i++) {
			void* vptr = MemoryManager::s_Instance->m_AllocatedPointers[i];
			if (vptr && ptr == vptr) {
				MemoryManager::s_Instance->m_AllocatedPointers[i] = nullptr;
				delete ptr;
				return;
			}
		}
			
	}

	template<typename T, typename ...Args>
	constexpr T* createShared(Args&&... args) {
		T* ptr = new T(args...);
		return ptr;
	}

}
