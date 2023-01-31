#include "JupiterEngine/Core/Config.h"

#include "JupiterCore/JupiterMath.h"
#include "JupiterCore/JupiterString.h"

#include <fstream>

namespace Jupiter {

	// Derived classes start

	/// <summary>
	/// Derived class from ConfigPropertyBase to hold a float value
	/// </summary>
	class ConfigPropertyFloat : public ConfigPropertyBase {

	public:
		ConfigPropertyFloat() = delete;
		ConfigPropertyFloat(const std::string& id, float value) : m_Identifier(id), m_Value(value) {}
		~ConfigPropertyFloat() {}

		virtual void set(void* value) { m_Value = *(float*)value; }
		virtual const std::string& getIdentifier() override { return m_Identifier; }
		virtual const ConfigValueType getValueType() override { return ConfigValueType::Float; }
		virtual const float asFloat() override { return m_Value; }
		virtual const int asInt() override { throw; }
		virtual const uint asUint() override { throw; }
		virtual const char asChar() override { throw; }
		virtual const bool asBool() override { throw; }

	private:
		const std::string m_Identifier;
		float m_Value;
	};

	/// <summary>
	/// Derived class from ConfigPropertyBase to hold a int value
	/// </summary>
	class ConfigPropertyInt : public ConfigPropertyBase {

	public:
		ConfigPropertyInt() = delete;
		ConfigPropertyInt(const std::string& id, int value);
		~ConfigPropertyInt();

		virtual const std::string& getIdentifier() override;
		virtual const ConfigValueType getValueType() override;
		virtual const float asFloat() override;
		virtual const int asInt() override;
		virtual const uint asUint() override;
		virtual const char asChar()override;
		virtual const bool asBool() override;
	};

	/// <summary>
	/// Derived class from ConfigPropertyBase to hold a uint value
	/// </summary>
	class ConfigPropertyUInt : public ConfigPropertyBase {

	public:
		ConfigPropertyUInt() = delete;
		ConfigPropertyUInt(const std::string& id, uint value);
		~ConfigPropertyUInt();

		virtual const std::string& getIdentifier() override;
		virtual const ConfigValueType getValueType() override;
		virtual const float asFloat() override;
		virtual const int asInt() override;
		virtual const uint asUint() override;
		virtual const char asChar()override;
		virtual const bool asBool() override;
	};

	/// <summary>
	/// Derived class from ConfigPropertyBase to hold a char value
	/// </summary>
	class ConfigPropertyChar : public ConfigPropertyBase {

	public:
		ConfigPropertyChar() = delete;
		ConfigPropertyChar(const std::string& id, char value);
		~ConfigPropertyChar();

		virtual const std::string& getIdentifier() override;
		virtual const ConfigValueType getValueType() override;
		virtual const float asFloat() override;
		virtual const int asInt() override;
		virtual const uint asUint() override;
		virtual const char asChar()override;
		virtual const bool asBool() override;
	};

	/// <summary>
	/// Derived class from ConfigPropertyBase to hold a bool value
	/// </summary>
	class ConfigPropertyBool : public ConfigPropertyBase {

	public:
		ConfigPropertyBool() = delete;
		ConfigPropertyBool(const std::string& id, bool value);
		~ConfigPropertyBool();

		virtual const std::string& getIdentifier() override;
		virtual const ConfigValueType getValueType() override;
		virtual const float asFloat() override;
		virtual const int asInt() override;
		virtual const uint asUint() override;
		virtual const char asChar()override;
		virtual const bool asBool() override;
	};

	// Functions Start
	ConfigPropertyBase* createPropertyNull(const std::string& group, const std::string identifier, void* value) {
		// TODO Throw exception
		return nullptr;
	}

	ConfigPropertyBase* createPropertyFloat(const std::string& group, const std::string identifier, void* value) {
		return new ConfigPropertyFloat(identifier, *(float*)value);
	}

	ConfigPropertyBase* createPropertyInt(const std::string& group, const std::string identifier, void* value) {
		return nullptr;
	}

	ConfigPropertyBase* createPropertyUInt(const std::string& group, const std::string identifier, void* value) {
		return nullptr;
	}

	ConfigPropertyBase* createPropertyChar(const std::string& group, const std::string identifier, void* value) {
		return nullptr;
	}

	ConfigPropertyBase* createPropertyBool(const std::string& group, const std::string identifier, void* value) {
		return nullptr;
	}


	// ConfigGroup Start

	ConfigGroup::ConfigGroup(const std::string& group_id, uint reserved_size) :
		m_GroupIdentifier(group_id),
		m_GroupProperties(reserved_size)
	{}

	ConfigGroup::~ConfigGroup() {}


	// ConfigContainer Start 

	ConfigContainer::ConfigContainer() {

	}

	ConfigContainer::~ConfigContainer() {

	}


	// ConfigParser Start

	void ConfigParser::loadConfigFile(ConfigContainer& container, const std::string& file) {
		std::ifstream in(file);
		std::string line;

		std::string groupIdentifier = JPT_CONFIG_GROUP_DEFAULT_ID;

		while (std::getline(in, line)) {
			char token = line.at(0);
			if (token == JPT_CONFIG_TOKEN_PROPERTY) {
				int iao = line.find_first_of('=', 1);
				JPT_ASSERT(iao == -1, "Could not find the assignment operator in a property line!");
				std::string propIdentifier = line.substr(1, iao - 1);
				std::string propValue = line.substr(iao + 1, line.size() - iao);

#ifdef JPT_CONFIG_TRIM_WHITESPACES
				JString::trim(propIdentifier);
				JString::trim(propValue);
#endif // JPT_CONFIG_TRIM_WHITESPACES

				JPT_ENGINE_INFO("[0],[1]", propIdentifier, propValue);
			}
			else if (token == JPT_CONFIG_TOKEN_GROUP) {
				int iws = JMath::iMax(line.find_first_of(' ', 1), line.size());
				groupIdentifier = line.substr(1, iws - 1);

#ifdef JPT_CONFIG_TRIM_WHITESPACES
				JString::trim(groupIdentifier);
#endif // JPT_CONFIG_TRIM_WHITESPACES
			}
		}
	}


	// ConfigManager Start 

	ConfigManager* ConfigManager::s_Instance = nullptr;

	ConfigManager::ConfigManager() {
		
	}

	ConfigManager::~ConfigManager() {

	}

	bool ConfigManager::hasGroup(const std::string& groupId) {
		std::vector<ConfigGroup>::iterator it;
		for (it = m_GroupRegister.begin(); it != m_GroupRegister.end(); it++) {
			if (groupId == it->m_GroupIdentifier) return true;
		}
		return false;
	}

	void ConfigManager::loadPropertyBindings() {
		s_Instance->m_PropertyCreateFuncBindings = (FuncCreateConfigProperty*)malloc(sizeof(FuncCreateConfigProperty) * 6);

		s_Instance->m_PropertyCreateFuncBindings[(int)ConfigValueType::Undefined] = createPropertyNull;
		s_Instance->m_PropertyCreateFuncBindings[(int)ConfigValueType::Float] = createPropertyFloat;
		s_Instance->m_PropertyCreateFuncBindings[(int)ConfigValueType::Int] = createPropertyInt;
		s_Instance->m_PropertyCreateFuncBindings[(int)ConfigValueType::UInt] = createPropertyUInt;
		s_Instance->m_PropertyCreateFuncBindings[(int)ConfigValueType::Char] = createPropertyChar;
		s_Instance->m_PropertyCreateFuncBindings[(int)ConfigValueType::Bool] = createPropertyBool;
	}

	void ConfigManager::unloadPropertyBindings() {
		free(s_Instance->m_PropertyCreateFuncBindings);
	}

	void ConfigManager::registerConfigProperty(const std::string& group, const std::string& prop, void* defaultValue, ConfigValueType valueType) {

	}

	void ConfigManager::registerConfigGroup(const std::string& group, uint reservedSize) {
#ifdef JPT_DEBUG
		JPT_ASSERT(s_Instance->hasGroup(group), "Config group '" + group + "' already exists!");
#endif // JPT_DEBUG
		s_Instance->m_GroupRegister.emplace_back(group, reservedSize);
	}

	void ConfigManager::loadFromFile(const std::string& file) {

	}


	// Derived classes start

	// ConfigPropertyFloat::ConfigPropertyFloat(const std::string& id, float value) : m_Identifier(id), m_Value(value) {}
	// ConfigPropertyFloat::~ConfigPropertyFloat(){}
	// const std::string& ConfigPropertyFloat::getIdentifier() {}
	// const ConfigValueType ConfigPropertyFloat::getValueType() {}
	// const float ConfigPropertyFloat::asFloat() {}
	// const int ConfigPropertyFloat::asInt() {}
	// const uint ConfigPropertyFloat::asUint() {}
	// const char ConfigPropertyFloat::asChar() {}
	// const bool ConfigPropertyFloat::asBool() {}
}
