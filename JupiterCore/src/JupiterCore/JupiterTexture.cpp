#include "JupiterCore/JupiterTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Jupiter {

#ifndef JPT_EXLUDE_STB_IMAGE_LOADER
	JupiterTextureLoader::JupiterTextureLoader(const std::string& texturefile, bool flip) : 
		m_TextureData(nullptr),
		m_Width(0),
		m_Height(0),
		m_ColorChannels(0)
	{
		stbi_set_flip_vertically_on_load(flip);
		m_TextureData = stbi_load(texturefile.c_str(), &m_Width, &m_Height, &m_ColorChannels, 0);
	}

	void JupiterTextureLoader::free() {
		stbi_image_free(m_TextureData);
	}

	unsigned char* JupiterTextureLoader::textureData() {
		return m_TextureData;
	}

	int JupiterTextureLoader::width() {
		return m_Width;
	}

	int JupiterTextureLoader::height() {
		return m_Height;
	}

	int JupiterTextureLoader::colorChannels() {
		return m_ColorChannels;
	}
#endif
}
