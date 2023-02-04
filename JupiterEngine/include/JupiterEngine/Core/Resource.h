#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include "JupiterEngine/Renderer/RenderBuffers.h"
#include "JupiterEngine/Renderer/Texture.h"

#include <map>

#define JPT_ENABLE_RESOURCE_CHECKS

// Macro block for when resource checks are enabled
#ifdef JPT_ENABLE_RESOURCE_CHECKS

// Enum defining the resource type
enum class ResourceType {
	RESOURCE_TEXTURE, RESOURCE_MESH, RESOURCE_SHADER
};

// Macro to define 2 methods that are beeing used for resource checking
// type = an instance of ResourceType, ex. ResourceType::RESOURCE_TEXTURE
#define JPT_DEFINE_RESOURCE_TYPE(type) \
public: static ResourceType getStaticResourceType() { return type; }\
virtual ResourceType getResourceType() override { return type; }
#else
#define JPT_DEFINE_RESOURCE_TYPE(type)
#endif

namespace Jupiter {

	/// <summary>
	/// Base resource class
	/// </summary>
	class ResourceBase {

	public:
		virtual ~ResourceBase() {}

		/// <summary>
		/// Delete the resource from memory
		/// </summary>
		virtual void releaseResource() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual bool isValid() = 0;

#ifdef JPT_ENABLE_RESOURCE_CHECKS
		virtual ResourceType getResourceType() = 0;
#endif
	};

	/// <summary>
	/// Representation of a Texture as a resource
	/// </summary>
	class ResourceTexture : public ResourceBase {
		JPT_DEFINE_RESOURCE_TYPE(ResourceType::RESOURCE_TEXTURE)

	public:
		ResourceTexture();
		ResourceTexture(r_ptr<Texture> textureObj);
		virtual ~ResourceTexture();

		virtual void releaseResource() override;	// See ResourceBase::releaseResource() for more information
		virtual bool isValid() override;			// See ResourceBase::isValid() for more information

		/// <summary>
		/// Binds the texture contained within this resource
		/// Calls the Jupiter::Texture::bind() function
		/// </summary>
		inline void bindTexture() { m_TextureObject->bind(); }

		/// <summary>
		/// Returns the width of the texture contained within this resource
		/// Calls Jupiter::Texture::getWidth() function
		/// </summary>
		/// <returns>The width of the texture in pixels</returns>
		inline uint getWidth() { return m_TextureObject->getWidth(); }

		/// <summary>
		/// Returns the height of the texture contained within this resource
		/// Calls Jupiter::Texture::getHeight() function
		/// </summary>
		/// <returns>The height of the texture in pixels</returns>
		inline uint getHeight() { return m_TextureObject->getHeight(); }

	private:
		bool m_Valid;
		r_ptr<Texture> m_TextureObject;
	};

	/// <summary>
	/// Representation of a Mesh as a resource
	/// </summary>
	class ResourceMesh : public ResourceBase {
		JPT_DEFINE_RESOURCE_TYPE(ResourceType::RESOURCE_MESH)

	public:
		ResourceMesh();
		ResourceMesh(r_ptr<VertexBuffer> vertexBufferObj);
		virtual ~ResourceMesh();

		virtual void releaseResource() override;	// See ResourceBase::releaseResource() for more information
		virtual bool isValid() override;			// See ResourceBase::isValid() for more information

		/// <summary>
		/// Binds the mesh contained within this resource
		/// Calls the Jupiter::VertexBuffer::bind() function
		/// </summary>
		inline void bindMesh() { m_VertexBuffer->bind(); }

	private:
		r_ptr<VertexBuffer> m_VertexBuffer;
		bool m_Valid;
	};

	/// <summary>
	/// Functor object used to load in a single resource
	/// </summary>
	class ResourceLoadFunctor {

	protected:
		virtual ~ResourceLoadFunctor() = default;
		virtual r_ptr<ResourceBase> operator()() = 0;

		friend class ResourceManager;
	};

	/// <summary>
	/// A resource is first registered, this requires a resource id in the form of a string, and a ResourceLoadFunctor object
	/// The ResourceLoadFunctor object can be called to load the registered resource into memory
	/// The registering in the resource does nothing with the data provided within the functor, it just prepares the data 
	/// ready to load and binds it to an string which is now its id
	/// 
	/// after a resource is registered, the resource can then be allocated
	/// This effectifly loads the resource into memory and makes it ready to be used
	/// To load a resource the only thing required is the resource id as a string passed into the register function
	/// 
	/// after a resource is loaded, it can be retrieved with the getResource method, this takes a string as resource id and
	/// retrieves the resource loaded with the allocate method
	/// 
	/// When the program is done with the resource, free resource should be called
	/// </summary>
	class ResourceManager {

	public:
		ResourceManager() {}
		~ResourceManager() {}

		/// <summary>
		/// Registers a recource, allowing it to be allocated
		/// </summary>
		/// <typeparam name="T">Thee type of the functor object</typeparam>
		/// <typeparam name="...Args">The arguments required to create the functor object</typeparam>
		/// <param name="resource_id">The id of the resource to register</param>
		/// <param name="...args">The parameters of the functor constructor</param>
		template<typename T, typename... Args>
		void registerResource(const std::string& resource_id, Args&&... args) {
#ifdef JPT_ENABLE_RESOURCE_CHECKS
			auto& resource = m_ResourceRegisterMap.find(resource_id);
			if (resource != m_ResourceRegisterMap.end())
				JPT_ASSERT_FAIL("Trying to register a resource with an already used ID!")
#endif
			// insantiate the load functor
			r_ptr<ResourceLoadFunctor> resourceLoadFunctor = (r_ptr<ResourceLoadFunctor>)new T((args)...);

			// place the functor in the map with the resource id as the key
			m_ResourceRegisterMap.emplace(resource_id, resourceLoadFunctor);
		}

		/// <summary>
		/// Allocates a resource
		/// </summary>
		/// <param name="resource_id">The id of the resource passed when registerResource was called</param>
		void allocateResource(const std::string& resource_id) {
			// Search the registry map for the resource id
			auto& it = m_ResourceRegisterMap.find(resource_id);
#ifdef JPT_ENABLE_RESOURCE_CHECKS
			if (it == m_ResourceRegisterMap.end())
				JPT_ASSERT_FAIL("Trying to load an resource with an unknown ID!")
#endif
			// Place the resource in the map using the resource id as the key
			m_ResourceMap.emplace(resource_id, (*it->second)());
		}

		/// <summary>
		/// Allocates a resource and returns the resource allocated
		/// </summary>
		/// <typeparam name="T">The type of the resource</typeparam>
		/// <param name="resource_id">The id of the resource</param>
		/// <returns>A reference to the resource object</returns>
		template<typename T>
		T& allocateAndGetResource(const std::string& resource_id) {
			auto& it = m_ResourceRegisterMap.find(resource_id);
			if (it == m_ResourceRegisterMap.end()) return T();
			ResourceBase* base = (*it->second)();
#ifdef JPT_ENABLE_RESOURCE_CHECKS
			ResourceType staticType = T::getStaticResourceType();
			ResourceType objectType = base->getResourceType();
			JPT_ASSERT((staticType == objectType), "Static type is not equal to the object type!");
#endif // JPT_ENABLE_RESOURCE_CHECKS
			return *((r_ptr<T>)base);
		}

		/// <summary>
		/// Gets a already loaded resource
		/// </summary>
		/// <typeparam name="T">The type of the resource</typeparam>
		/// <param name="resource_id">The id of the resource</param>
		/// <returns>A reference to the resource object</returns>
		template<typename T>
		T& getResource(const std::string& resource_id) {
			auto& it = m_ResourceMap.find(resource_id);
			if (it == m_ResourceMap.end()) return T();
#ifdef JPT_ENABLE_RESOURCE_CHECKS
			ResourceType staticType = T::getStaticResourceType();
			ResourceType objectType = it->second->getResourceType();
			JPT_ASSERT((staticType == objectType), "Static type is not equal to the object type!");
#endif // JPT_ENABLE_RESOURCE_CHECKS
			return *((r_ptr<T>) it->second);
		}

		/// <summary>
		/// Releases the resource freeing up the memory it occupied
		/// </summary>
		void releaseResource(const std::string& resource_id) {
			auto& it = m_ResourceMap.find(resource_id);
#ifdef JPT_ENABLE_RESOURCE_CHECKS
			if (it == m_ResourceMap.end())
				JPT_ASSERT_FAIL("Trying to free an resource that is not currently loaded!");
#endif
			r_ptr<ResourceBase> resource = it->second;
			m_ResourceMap.erase(it);
			resource->releaseResource();
			delete resource;
		}

		/// <summary>
		/// Releases all resources from memory
		/// </summary>
		void releaseAll() {
			for (auto& it = m_ResourceMap.begin(); it != m_ResourceMap.end(); it++) {
				r_ptr<ResourceBase> resource = it->second;
				resource->releaseResource();
				delete resource;
			}
			m_ResourceMap.clear();
		}

	private:
		// Key of the map is the resource id, and the value is the ResourceLoadFunctor object
		std::map<const std::string, r_ptr<ResourceLoadFunctor>> m_ResourceRegisterMap;

		// Key of the map is the resource id, and the Resource is whatever value the ResourceLoadFunctor object returned 
		std::map<const std::string, r_ptr<ResourceBase>> m_ResourceMap;
	};
}
