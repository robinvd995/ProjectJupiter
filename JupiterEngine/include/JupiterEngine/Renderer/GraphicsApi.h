#pragma once

#include "JupiterEngine/JupiterEngine.h"

namespace Jupiter {

	/// <summary>
	/// Enum containing the all the different "supported" graphics API's
	/// </summary>
	enum class EnumGraphicsAPI {
		NONE,			// Filler
		OPEN_GL,		// OpenGL V4.6
		DIRECTX11,		// DirectX 11
		DIRECTX12,		// DirectX 12
		VULKAN			// Vulkan 1.2
	};
}
