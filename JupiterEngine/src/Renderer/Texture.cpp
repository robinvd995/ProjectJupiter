#include "JupiterEngine/Renderer/Texture.h"

namespace Jupiter {

	TextureSource::TextureSource(uint width, uint height, uint channels, unsigned char* data) :
		textureWidth(width),
		textureHeight(height),
		textureColorChannels(channels),
		textureData(data)
	{}

	TextureSource::TextureSource(JupiterTextureLoader& loader) : 
		textureWidth(loader.width()),
		textureHeight(loader.height()),
		textureColorChannels(loader.colorChannels()),
		textureData(loader.textureData())
	{}

	TextureSpecification::TextureSpecification(TextureFormat textureformat) :
		format(textureformat)
	{}

}