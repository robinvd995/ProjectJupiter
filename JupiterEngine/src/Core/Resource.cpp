#include "JupiterEngine/Core/Resource.h"

namespace Jupiter {

	ResourceTexture::ResourceTexture() :
		m_TextureObject(nullptr),
		m_Valid(false)
	{}

	ResourceTexture::ResourceTexture(r_ptr<Texture> textureObj) :
		m_TextureObject(textureObj),
		m_Valid(true)
	{}

	ResourceTexture::~ResourceTexture() {
		
	}

	void ResourceTexture::releaseResource() {
		delete m_TextureObject;
	}

	bool ResourceTexture::isValid() {
		return m_Valid;
	}

	ResourceMesh::ResourceMesh() :
		m_VertexBuffer(nullptr),
		m_Valid(false)
	{}

	ResourceMesh::ResourceMesh(r_ptr<VertexBuffer> vertexBufferObj) :
		m_VertexBuffer(vertexBufferObj),
		m_Valid(true)
	{}

	ResourceMesh::~ResourceMesh() {}

	void ResourceMesh::releaseResource() {
		delete m_VertexBuffer;
	}

	bool ResourceMesh::isValid() {
		return m_Valid;
	}
}