#pragma once

#include "JupiterCore/JupiterCoreDefinitions.h"
#include <string>

namespace Jupiter {

	/// <summary>
	/// Enum specifiying the texture filter specification options for the min filter
	/// </summary>
	enum class TextureMinFilterSpecification {
		Linear = 0,
		Nearest = 1,
		NearestMipmapNearest = 2,
		LinearMipmapNearest = 3,
		NearestMipmapLinear = 4,
		LinearMipmapLinear = 5
	};

	/// <summary>
	/// Enum specifiying the texture filter specification options for the mag filter
	/// </summary>
	enum class TextureMagFilterSpecification {
		Linear = 0,
		Nearest = 1
	};

	/// <summary>
	/// Enum specifiying the texture wrap specification options
	/// </summary>
	enum class TextureWrapSpecification {
		Repeat = 0,
		ClampToEdge = 1,
		ClampToBorder = 2,
		MirroredRepeat = 3,
		MirroredClampToEdge = 4
	};

	/// <summary>
	/// Enum specifiying the texture format options
	/// </summary>
	enum class TextureFormat {
		RGBA = 0,
		RGB = 1
	};
	
	/// <summary>
	/// Simple class used to load a texture
	/// </summary>
	class JupiterTextureLoader {

	public:
		JupiterTextureLoader() = delete;
		JupiterTextureLoader(const std::string& texturefile, bool flip = false);
		~JupiterTextureLoader() = default;

		/// <summary>
		/// Frees the allocated memory for loading the texture
		/// </summary>
		void free();

		/// <summary>
		/// Gets the raw texture data
		/// </summary>
		/// <returns></returns>
		unsigned char* textureData();

		/// <summary>
		/// Gets the width of the texture
		/// </summary>
		/// <returns></returns>
		int width();

		/// <summary>
		/// Gets the height of the texture
		/// </summary>
		/// <returns></returns>
		int height();

		/// <summary>
		/// Gets the amount of color channels of the texture
		/// </summary>
		/// <returns></returns>
		int colorChannels();

	private:
		unsigned char* m_TextureData;
		int m_Width;
		int m_Height;
		int m_ColorChannels;
	};

}
