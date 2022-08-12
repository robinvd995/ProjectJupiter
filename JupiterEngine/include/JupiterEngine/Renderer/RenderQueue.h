#pragma once

#include "Core.h"

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	struct RenderHandle {

	};

	/// <summary>
	/// 
	/// </summary>
	struct RenderPackage {
		// ShaderHandle shader;
		// VaoHandle vao;
		// std::vector<UniformBufferHandle> uniformBufferTargets;
		// std::vector<UniformBufferSource*> uniformBufferSource;
		// RenderPass renderPass;
		// std::vector<RenderParameters> renderParameters;
		// DrawMode drawMode;
	};

	/// <summary>
	/// 
	/// </summary>
	class RenderQueue {

	public:
		RenderQueue();
		~RenderQueue();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="renderPackage"></param>
		/// <returns></returns>
		RenderHandle submit(RenderPackage& renderPackage);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="handle"></param>
		void remove(RenderHandle handle);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="handle"></param>
		void mask(RenderHandle handle);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="handle"></param>
		void unmask(RenderHandle handle);
		
	};
}
