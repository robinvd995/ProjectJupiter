#include "JupiterCompiler.h"

#include "JupiterCore/JupiterString.h"
#include "JupiterCore/JupiterShaderCompiler.h"


#include <fstream>

namespace Jupiter {

	void compileShader(const CommandParser& parser) {
		std::string filepath;
		if (parser.findArgument("file", filepath)) {

			std::ifstream file(filepath);
			if (!file.is_open()) {
				std::cout << "Cannot open file '" << filepath << "'!" << std::endl;
				return;
			}

			// TODO: detect for single file versus multi file shader setups

			// File has been found, now compile it into its spirv form
			std::string shadersource((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
			file.close();

			ShaderHelper::initShaderCompiler();

			ShaderCompilationContainer container;
			ShaderCompiler shaderCompiler(filepath, shadersource);
			shaderCompiler.compile(container, ShaderCompilerFlags_None);

			ShaderReflectionContainer reflectionData;
			ShaderHelper::reflect(container, reflectionData);

			ShaderHelper::cleanupShaderCompiler();
		}
		else {
			std::cout << "No file path has been given!" << std::endl;
		}
	}

	JupiterCompiler::JupiterCompiler(int argc, char* argv[]) :
		m_CommandParser(argc, argv)
	{
		m_FuncMap.emplace("SHADER", compileShader);
	}

	void JupiterCompiler::run() {

#ifdef JPT_COMMAND_PARSER_DEBUG
		m_CommandParser.print();
#endif

		if (m_CommandParser.hasCommand()) {
			std::string command = JString::toUpper_copy(m_CommandParser.getCommand());
			auto it = m_FuncMap.find(command);
			if (it != m_FuncMap.end()) {
				it->second(m_CommandParser);
			}
			else {
				std::cout << "Unknown command '" << command << "'!" << std::endl;
			}
		}
		else {
			std::cout << "No command has been given!" << std::endl;
		}
	}

}