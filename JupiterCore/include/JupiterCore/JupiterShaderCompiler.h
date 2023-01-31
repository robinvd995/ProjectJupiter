#ifndef JPT_CORE_INCLUDE_SHADER_COMPILER

#pragma once

#include "JupiterCore.h"
#include "JupiterCoreDefinitions.h"

#include <map>

namespace Jupiter {

	typedef l_uint ShaderCompilerFlags;

	constexpr ShaderCompilerFlags ShaderCompilerFlags_None = 0 << 0;
	constexpr ShaderCompilerFlags ShaderCompilerFlags_OptimizationZero = 1 << 1;
	constexpr ShaderCompilerFlags ShaderCompilerFlags_OptimizationPerformance = 1 << 2;
	constexpr ShaderCompilerFlags ShaderCompilerFlags_OptimizationSize = 1 << 3;

	typedef const std::vector<uint> SPIRVSource;
	typedef std::map<uint, SPIRVSource> SPIRVSourceMap;

	enum class ShaderStageType {
		VERTEX = 0,
		GEOMETRY = 1,
		FRAGMENT = 2,
		COMPUTE = 3,

		COUNT
	};

	/// <summary>
	/// Class to represent a stage in the shader pipeline
	/// </summary>
	class ShaderStage {

	public:
		/// <summary>
		/// Array containing the pointers to the shader stages
		/// </summary>
		static ShaderStage** s_Values;

	private:
		const uint32_t c_Ordinal;
		const std::string c_Name;
		const std::string c_StageMacroDefinition;
		const uint32_t c_ShaderKind;

	public:
		ShaderStage() = delete;
		ShaderStage(const uint32_t ordinal, const std::string& name, const std::string& stageMacro, uint32_t shaderKind);
		ShaderStage(const ShaderStage&) = delete;
		~ShaderStage() = default;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const uint32_t ordinal() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::string macroDefinition() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const uint32_t shaderKind() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::string& name() const;
	};

	/// <summary>
	/// 
	/// </summary>
	class ShaderCompilationMessages {

	public:
		ShaderCompilationMessages() = default;
		~ShaderCompilationMessages() = default;

	private:
		std::vector<std::string> m_Errors;
		uint m_Warnings = 0;

		friend class ShaderCompilationContainer;
	};

	/// <summary>
	/// 
	/// </summary>
	class ShaderCompilationContainer {

	public:
		ShaderCompilationContainer() = default;
		~ShaderCompilationContainer() = default;

		/// <summary>
		/// Polls if the container contains the given stage
		/// </summary>
		/// <param name="shaderStage">the stage to check for</param>
		/// <returns>true if the stage has been found within the container</returns>
		bool hasStage(uint shaderStage);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="error"></param>
		void addCompilationError(const std::string& error);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="count"></param>
		void addCompilationWarning(uint count);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="stage"></param>
		/// <param name="source"></param>
		void addSource(uint stage, SPIRVSource& source);

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const uint getWarningCount() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const uint getErrorCount() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::string& getName() const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		void setName(const std::string& name);

		SPIRVSourceMap::const_iterator begin() const;
		SPIRVSourceMap::const_iterator end() const;

	private:
		std::string m_Name;
		ShaderCompilationMessages m_CompilationMessages;

		// bool m_ShaderStages[(uint)ShaderStageType::COUNT] = {false};
		SPIRVSourceMap m_StageCompileMap;
	};

	/// <summary>
	/// 
	/// </summary>
	class ShaderReflectionContainer {

	public:
		ShaderReflectionContainer() = default;
		~ShaderReflectionContainer() = default;
	};

	/// <summary>
	/// 
	/// </summary>
	class ShaderCompiler {

	public:
		ShaderCompiler() = delete;
		ShaderCompiler(const std::string& name, const std::string& shadersource);
		~ShaderCompiler();

		/// <summary>
		/// TODO
		/// </summary>
		void compile(ShaderCompilationContainer& container, l_uint flags);

	private:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool verifySource();

	private:
		const std::string m_Name;
		std::string m_ShaderSource;
		bool m_FoundShaderStages[(uint)ShaderStageType::COUNT];
	};

	/// <summary>
	/// Namespace functions
	/// </summary>
	namespace ShaderHelper {

		/// <summary>
		/// Generates reflection data for the given shader source
		/// </summary>
		void reflect(const ShaderCompilationContainer& compilerContainer, ShaderReflectionContainer& reflectionContainer);

		/// <summary>
		/// 
		/// </summary>
		void initShaderCompiler();

		/// <summary>
		/// 
		/// </summary>
		void cleanupShaderCompiler();
	}
}

#endif
