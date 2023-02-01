#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include "Shader.h"
#include "RenderBuffers.h"

namespace Jupiter {

	class Material {

	public:
		Material(s_ptr<Shader> shader, s_ptr<UniformBuffer> buffer);
		~Material();

		void bind();

		// TODO: void sort();

	private:
		// Material needs to contain a shader, uniform variables and textures
		// Maybe also contain draw modes, but likely not

		s_ptr<Shader> m_Shader;
		s_ptr<UniformBuffer> m_MaterialSpecs;
		// s_ptr<TextureBuffer> m_Textures; TODO
		// JupiterDrawMode m_DrawMode ????
	};

}
