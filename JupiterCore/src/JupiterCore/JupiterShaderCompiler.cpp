#include "JupiterCore/JupiterShaderCompiler.h"

#include "JupiterCore/JupiterTimer.h"

#include <vulkan/vulkan.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include <spirv_cross/spirv_hlsl.hpp>
#include <shaderc/shaderc.hpp>

namespace Jupiter {

	ShaderStage** ShaderStage::s_Values = nullptr;

	ShaderStage::ShaderStage(const uint32_t ordinal, const std::string& name, const std::string& stageMacro, uint32_t shaderKind) :
		c_Ordinal(ordinal), c_Name(name), c_StageMacroDefinition(stageMacro), c_ShaderKind(shaderKind)
	{

	}

	const uint32_t ShaderStage::ordinal() const {
		return c_Ordinal;
	}

	const std::string ShaderStage::macroDefinition() const {
		return c_StageMacroDefinition;
	}

	const uint32_t ShaderStage::shaderKind() const {
		return c_ShaderKind;
	}

	const std::string& ShaderStage::name() const {
		return c_Name;
	}

	bool ShaderCompilationContainer::hasStage(uint shaderStage) {
		//return m_ShaderStages[shaderStage];
		auto it = m_StageCompileMap.find(shaderStage);
		return it != m_StageCompileMap.end();
	}

	void ShaderCompilationContainer::addCompilationError(const std::string& error) {
		m_CompilationMessages.m_Errors.push_back(error);
	}

	void ShaderCompilationContainer::addCompilationWarning(uint count) {
		m_CompilationMessages.m_Warnings += count;
	}

	void ShaderCompilationContainer::addSource(uint stage, SPIRVSource& source) {
		// m_ShaderStages[stage] = true;
		m_StageCompileMap.emplace(stage, source);
	}

	const uint ShaderCompilationContainer::getWarningCount() const {
		return m_CompilationMessages.m_Warnings;
	}

	const uint ShaderCompilationContainer::getErrorCount() const {
		return m_CompilationMessages.m_Errors.size();
	}

	const std::string& ShaderCompilationContainer::getName() const {
		return m_Name;
	}

	void ShaderCompilationContainer::setName(const std::string& name) {
		m_Name = name;
	}

	SPIRVSourceMap::const_iterator ShaderCompilationContainer::begin() const {
		return m_StageCompileMap.begin();
	}

	SPIRVSourceMap::const_iterator ShaderCompilationContainer::end() const {
		return m_StageCompileMap.end();
	}

	ShaderCompiler::ShaderCompiler(const std::string& name, const std::string& shadersource) :
		m_Name(name), m_ShaderSource(shadersource)
	{
		bool result = verifySource();
	}

	ShaderCompiler::~ShaderCompiler() {

	}

	bool ShaderCompiler::verifySource() {

		JPT_CORE_INFO("Verifying shader source [0]...", m_Name);

		// Detecting what stages are withing the source file
		for (int i = 0; i < (uint)ShaderStageType::COUNT; i++) {
			ShaderStage* stage = ShaderStage::s_Values[i];

			// Define the declaration to look for in the source as a string
			std::string stageDeclaration = std::string("#ifdef ").append(stage->macroDefinition());

			// Find the location of the declaration in the source
			size_t pos = m_ShaderSource.find(stageDeclaration);

			// If location has not been found, set the shader stage found to false
			if (pos == m_ShaderSource.npos) m_FoundShaderStages[i] = false;

			// If the location has been found, set the shader stage found to true
			else {
				JPT_CORE_INFO("Found stage '[0]'", stage->name());
				m_FoundShaderStages[i] = true;
			}
		}

		return true;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="compiler"></param>
	/// <param name="compileOptions"></param>
	/// <param name="stage"></param>
	/// <param name="shaderSource"></param>
	/// <param name="container"></param>
	/// <returns></returns>
	bool compileStage(shaderc::Compiler& compiler, shaderc::CompileOptions compileOptions, ShaderStage* stage,
		const std::string& shaderSource, ShaderCompilationContainer& container) {

		// Add macro definition for the given stage so only the relevant parts of the source will be compiled
		compileOptions.AddMacroDefinition(stage->macroDefinition());

		// Create a timer and start the timer
		JTimer timer;
		timer.start();

		// Compile the glsl to spirv
		shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(shaderSource,
			static_cast<shaderc_shader_kind>(stage->shaderKind()), container.getName().c_str(), compileOptions);

		// End the timer
		timer.end();

		JPT_CORE_INFO("Done compiling stage [0], duration=[1]s, warnings=[2], errors=[3]",
			stage->name(), timer.getTimeS(), result.GetNumWarnings(), result.GetNumErrors());

		// Add warnings to the container ecountered during the compilation
		container.addCompilationWarning(result.GetNumWarnings());

		// Add errors to the container encountered during the compilation
		if (result.GetNumErrors() > 0) {
			container.addCompilationError(std::string(stage->name()).append(": " + result.GetErrorMessage()));
			return false;
		}

		// Put the compiled source into the map
		SPIRVSource compiledSrc = SPIRVSource(result.begin(), result.end());
		container.addSource(stage->ordinal(), compiledSrc);

		// return true if the compilation was succesfull
		return result.GetCompilationStatus() == shaderc_compilation_status_success;
	}

	void ShaderCompiler::compile(ShaderCompilationContainer& container, l_uint flags) {

		// Set the name of the container
		container.setName(m_Name);

		// Create compiler and options
		shaderc::Compiler shadercCompiler;
		shaderc::CompileOptions compileOptions;

		// Set the target environment for the compiler
		compileOptions.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);

		// If optimization flag zero is passed, set the optimization level to zero
		if (flags & ShaderCompilerFlags_OptimizationZero)
			compileOptions.SetOptimizationLevel(shaderc_optimization_level_zero);

		// If optimization flag performance is passed, set the optimization level to performance
		if (flags & ShaderCompilerFlags_OptimizationPerformance)
			compileOptions.SetOptimizationLevel(shaderc_optimization_level_performance);

		// If optimization flag size is passed, set the optimization level to size
		if (flags & ShaderCompilerFlags_OptimizationSize)
			compileOptions.SetOptimizationLevel(shaderc_optimization_level_size);

		// Compiling the individual stages
		for (int i = 0; i < (uint)ShaderStageType::COUNT; i++) {
			ShaderStage* stage = ShaderStage::s_Values[i];

			// If stage was not found during the verification process, continue
			if (!m_FoundShaderStages[i]) continue;
			JPT_CORE_INFO("Compiling stage [0]...", stage->name());

			// Compile the current stage
			bool success = compileStage(shadercCompiler, compileOptions, stage, m_ShaderSource, container);

			// If compiling was not successfull, give an error
			if (!success)
				JPT_CORE_ERROR("Failed compiling stage [0]!", stage->name());
		}

		JPT_CORE_INFO("Done compiling '[0]', total warnings=[1], total errors=[2]", m_Name, container.getWarningCount(), container.getErrorCount());
	}

	/// <summary>
	/// 
	/// </summary>
	void reflectStage(ShaderStage* stage, const SPIRVSource& source) {
		spirv_cross::Compiler compiler(source);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		// TODO: reflection
	}

	void ShaderHelper::reflect(const ShaderCompilationContainer& compilerContainer, ShaderReflectionContainer& reflectionContainer) {
		JPT_CORE_INFO("Generating reflection data for '[0]'...", compilerContainer.getName());

		JTimer timer;
		// Reflecting individual stages
		for (auto it = compilerContainer.begin(); it != compilerContainer.end(); it++) {
			ShaderStage* stage = ShaderStage::s_Values[it->first];
			JPT_CORE_INFO("Reflecting stage [0]...", stage->name());
			timer.start();
			reflectStage(stage, it->second);
			timer.end();
			JPT_CORE_INFO("Done reflecting stage, duration=[0]s", timer.getTimeS());
		}
	}

	void ShaderHelper::initShaderCompiler() {
		// Check if the shader stages are already initialized
		if (ShaderStage::s_Values == nullptr) {

			// allocate the space for the shader stages
			ShaderStage::s_Values = (ShaderStage**)malloc(sizeof(ShaderStage*) * (uint)ShaderStageType::COUNT);

			// create vertex stage
			ShaderStage::s_Values[(uint)ShaderStageType::VERTEX] = new ShaderStage((uint)ShaderStageType::VERTEX,
				"Vertex Shader", "STAGE_VERTEX", shaderc_shader_kind::shaderc_vertex_shader);

			// create geometry stage
			ShaderStage::s_Values[(uint)ShaderStageType::GEOMETRY] = new ShaderStage((uint)ShaderStageType::GEOMETRY,
				"Geometry Shader", "STAGE_GEOMETRY", shaderc_shader_kind::shaderc_geometry_shader);

			// create fragment stage
			ShaderStage::s_Values[(uint)ShaderStageType::FRAGMENT] = new ShaderStage((uint)ShaderStageType::FRAGMENT,
				"Fragment Shader", "STAGE_FRAGMENT", shaderc_shader_kind::shaderc_fragment_shader);

			// create compute stage
			ShaderStage::s_Values[(uint)ShaderStageType::COMPUTE] = new ShaderStage((uint)ShaderStageType::COMPUTE,
				"Fragment Shader", "STAGE_COMPUTE", shaderc_shader_kind::shaderc_compute_shader);
		}
		else {
			// Shader stages are already initialized so warn the user
			JPT_CORE_WARN("Trying to intialize shader compiler values twice!");
		}
	}

	void ShaderHelper::cleanupShaderCompiler() {
		// Delete vertex stage
		delete ShaderStage::s_Values[(uint)ShaderStageType::VERTEX];

		// Delete geometry stage
		delete ShaderStage::s_Values[(uint)ShaderStageType::GEOMETRY];

		// Delete fragment stage
		delete ShaderStage::s_Values[(uint)ShaderStageType::FRAGMENT];

		// Delete compute stage
		delete ShaderStage::s_Values[(uint)ShaderStageType::COMPUTE];

		// Free the stage values and set it to nullptr so the program knows it has been free'd
		free(ShaderStage::s_Values);
		ShaderStage::s_Values = nullptr;
	}
}
