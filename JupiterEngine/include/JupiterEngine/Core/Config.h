#pragma once

#include "JupiterEngine/JupiterEngine.h"

#include <stdexcept>

#ifndef JPT_CONFIG_GROUP_DEFAULT_ID
#define JPT_CONFIG_GROUP_DEFAULT_ID "default"
#endif // !JPT_CONFIG_GROUP_DEFAULT_ID

#ifndef JPT_CONFIG_TOKEN_GROUP
#define JPT_CONFIG_TOKEN_GROUP '#'
#endif // !JPT_CONFIG_TOKEN_GROUP

#ifndef JPT_CONFIG_TOKEN_PROPERTY
#define JPT_CONFIG_TOKEN_PROPERTY '@'
#endif // !JPT_CONFIG_TOKEN_PROPERTY

#ifndef JPT_CONFIG_GROUP_DEFAULT_RESERVATION_SIZE
#define JPT_CONFIG_GROUP_DEFAULT_RESERVATION_SIZE 16
#endif // !JPT_CONFIG_GROUP_DEFAULT_RESERVATION_SIZE

namespace Jupiter {

	/// <summary>
	/// TODO
	/// </summary>
	enum class ConfigValueType {
		Undefined = 0,
		Float = 1,
		Int = 2,
		UInt = 3,
		Char = 4,
		Bool = 5
	};

	/// <summary>
	/// TODO
	/// </summary>
	struct ConfigGroup {
		std::string m_GroupIdentifier;
		std::vector<uint> m_GroupProperties;

		// Delete default constructor
		ConfigGroup() = delete;

		// Add new constructor with 2 parameters
		ConfigGroup(const std::string& group_id, uint reserved_size);

		// Default destructor
		~ConfigGroup();

		// Delete copy constructors
		ConfigGroup(const ConfigGroup&) = delete;
		ConfigGroup& operator=(const ConfigGroup&) = delete;

		// Enable move constructors
		ConfigGroup(ConfigGroup&&) noexcept {}
		ConfigGroup& operator=(ConfigGroup&&) noexcept {}
	};

	/// <summary>
	/// 
	/// </summary>
	class ConfigPropertyBase {

	public:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="value"></param>
		virtual void set(void* value) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const std::string& getIdentifier() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const ConfigValueType getValueType() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const float asFloat() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const int asInt() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const uint asUint() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const char asChar() = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual const bool asBool() = 0;
	};

	/// <summary>
	/// Contains the config properties and associated values
	/// </summary>
	class ConfigContainer {
		
	public:
		ConfigContainer();
		~ConfigContainer();

	private:
		/// <summary>
		/// Adds a config group to the container
		/// </summary>
		/// <param name="identifier">TODO</param>
		/// <param name="index">TODO</param>
		void addGroup(const std::string& identifier, uint index) {}
		
		/// <summary>
		/// Adds a config property to the container
		/// </summary>
		/// <param name="valueType">TODO</param>
		/// <param name="identifier">TODO</param>
		/// <param name="valueRef">TODO</param>
		void addProperty(ConfigValueType valueType, const std::string& identifier, void* valueRef) {}

	private:
		std::vector<ConfigPropertyBase*> m_PropertyVector;
		std::vector<ConfigGroup> m_GroupVector;
	};

	/// <summary>
	/// Parses the config file
	/// Might move this from a class to a namespace function
	/// </summary>
	class ConfigParser {

	public:
		/// <summary>
		/// TODO
		/// </summary>
		/// <param name="container">TODO</param>
		/// <param name="file">TODO</param>
		static void loadConfigFile(ConfigContainer& container, const std::string& file);

	private:
		ConfigParser() = default;
		~ConfigParser() = default;
	};

	/// <summary>
	/// Used to maintain the registered config configurations ( :) ) and the container, is basicly used as an general interface
	/// </summary>
	class ConfigManager {

		typedef ConfigPropertyBase* (*FuncCreateConfigProperty)(const std::string& group, const std::string identifier, void* value);

	private:
		ConfigManager();
		ConfigManager(const ConfigManager&) = delete;
		~ConfigManager();
		ConfigManager& operator=(const ConfigManager&) = delete;
		friend class JupiterEngineApplication;

		/// <summary>
		/// Checks if the group register contains an group with id
		/// </summary>
		/// <param name="groupId">The id of the group to match against</param>
		/// <returns>true if register contains an entry with the id, false otherwise</returns>
		bool hasGroup(const std::string& groupId);

	private:
		static ConfigManager* s_Instance;

		/// <summary>
		/// TODO
		/// </summary>
		static void loadPropertyBindings();

		/// <summary>
		/// TODO
		/// </summary>
		static void unloadPropertyBindings();

		// static ConfigPropertyBase* createPropertyNull(const std::string& group, const std::string identifier, void* value);
		// static ConfigPropertyBase* createPropertyFloat(const std::string& group, const std::string identifier, void* value);
		// static ConfigPropertyBase* createPropertyInt(const std::string& group, const std::string identifier, void* value);
		// static ConfigPropertyBase* createPropertyUInt(const std::string& group, const std::string identifier, void* value);
		// static ConfigPropertyBase* createPropertyChar(const std::string& group, const std::string identifier, void* value);
		// static ConfigPropertyBase* createPropertyBool(const std::string& group, const std::string identifier, void* value);

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="group">TODO</param>
		/// <param name="property">TODO</param>
		/// <param name="value">TODO</param>
		/// <param name="valueType">TODO</param>
		static void registerConfigProperty(const std::string& group, const std::string& prop, void* value, ConfigValueType valueType);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="group">the identifier of the group</param>
		/// <param name="reservedSize">The amount of properties reserved for this group, default = #def(JPT_CONFIG_GROUP_DEFAULT_RESERVATION_SIZE)</param>
		static void registerConfigGroup(const std::string& group, uint reservedSize = JPT_CONFIG_GROUP_DEFAULT_RESERVATION_SIZE);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="file"></param>
		static void loadFromFile(const std::string& file);

	private:
		// std::vector<ConfigProperty> m_PropertyRegister;
		std::vector<ConfigGroup> m_GroupRegister{};
		FuncCreateConfigProperty* m_PropertyCreateFuncBindings = nullptr;
	};
}
