#pragma once

#include <string>

#include "JupiterCore/Xml.h"

#include "IoConfig.h"

namespace Jupiter::Io {

	typedef void (*init_func)(void);

	class ProjectIo {

	public:
		ProjectIo() = delete;
		ProjectIo(ProjectIo&) = delete;
		ProjectIo(std::string& cfgFile, init_func func);
		~ProjectIo();

		void run();

	private:
		bool load(std::string& error);
		bool execute(std::string& error);
		bool release(std::string& error);

	private:
		std::string m_ConfigFilePath;
		IoConfig m_Config;
		init_func m_InitFunction = nullptr;
	};
}
