#pragma once

#include "Core.h"

namespace Jupiter {

	/// <summary>
	/// Enum containing the all the different "supported" graphics API's
	/// </summary>
	enum class EnumGraphicsAPI {
		NONE, OPEN_GL, DIRECTX11, DIRECTX12, VULKAN
	};
}
