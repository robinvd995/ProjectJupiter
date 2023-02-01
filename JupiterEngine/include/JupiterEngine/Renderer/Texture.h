#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include "JupiterCore/JupiterTexture.h"

namespace Jupiter {
	
	/// <summary>
	/// Struct containing information about the texture source
	/// </summary>
	struct TextureSource {
		const uint textureWidth;
		const uint textureHeight;
		const uint textureColorChannels;
		const unsigned char* textureData;

		TextureSource() = delete;
		TextureSource(uint width, uint height, uint channels, unsigned char* data);
		TextureSource(JupiterTextureLoader& loader);
	};

	/// <summary>
	/// Struct containg the specifications the texture when loaded into GPU memory
	/// </summary>
	struct TextureSpecification {
		TextureMinFilterSpecification minFilter = TextureMinFilterSpecification::Linear;
		TextureMagFilterSpecification magFilter = TextureMagFilterSpecification::Linear;
		TextureWrapSpecification wrapR = TextureWrapSpecification::Repeat;
		TextureWrapSpecification wrapS = TextureWrapSpecification::Repeat;
		TextureWrapSpecification wrapT = TextureWrapSpecification::Repeat;
		
		const TextureFormat format;

		TextureSpecification() = delete;
		TextureSpecification(TextureFormat textureformat);
	};

	/// <summary>
	/// Generic texture class
	/// </summary>
	class Texture {

	public:
		virtual ~Texture() = default;

		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;

		virtual void bind() const = 0;
	};
	
	/// <summary>
	/// Class representing a 2D texture
	/// </summary>
	class Texture2D : public Texture {

	public:
		virtual ~Texture2D() = default;
	};
}
