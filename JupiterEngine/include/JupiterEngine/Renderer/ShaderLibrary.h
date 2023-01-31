#pragma once

#include "JupiterEngine/JupiterEngine.h"
#include "JupiterEngine/Renderer/Shader.h"

namespace Jupiter {

	typedef uint ShaderHandle;

	class ShaderLibrary {

	public:
		ShaderLibrary();
		~ShaderLibrary();

		ShaderHandle registerShader();

	private:
		std::vector<Shader*> m_Shaders;
	};

}
