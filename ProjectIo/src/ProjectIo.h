#pragma once

#include <string>

#include "JupiterCore/Xml.h"

#include "IoConfig.h"

namespace Jupiter::Io {

	class ProjectIO {

	public:
		ProjectIO() = delete;
		ProjectIO(ProjectIO&) = delete;
		ProjectIO(std::string& cfgFile);
		~ProjectIO();

		void init();

		bool load(std::string& error);
		bool execute(std::string& error);
		bool release(std::string& error);

	private:
		std::string m_ConfigFilePath;
		IoConfig m_Config;
	};
}
