#include "ProjectIo/AssetRegister.h"

#include "JupiterCore/Xml.h"

#define ASSET_REGISTER_ROOT_NODE_ID "asset_register"

#define ASSET_REGISTER_ENTRY_NODE_ID "entry"

#define ASSET_REGISTER_ENTRY_ATTRIB_ID "i_id"
#define ASSET_REGISTER_ENTRY_ATTRIB_NAME "name"
#define ASSET_REGISTER_ENTRY_ATTRIB_LOCATION "location"
#define ASSET_REGISTER_ENTRY_ATTRIB_BEGIN "begin"
#define ASSET_REGISTER_ENTRY_ATTRIB_END "end"

namespace Jupiter::Io {

	// ----- START AssetRegisterEntry -----

	AssetRegisterEntry::AssetRegisterEntry(uint32_t id, const std::string& name, const std::string& location, uint32_t begin, uint32_t end) :
		m_Id(id), m_Name(name), m_Location(location), m_Begin(begin), m_End(end)
	{}

	bool AssetRegisterEntry::operator<(const AssetRegisterEntry& other) const {
		return m_Id < other.m_Id;
	}

	bool AssetRegisterEntry::operator==(const AssetRegisterEntry& other) {
		return m_Id == other.m_Id;
	}

	const uint32_t AssetRegisterEntry::getId() const {
		return m_Id;
	}

	const std::string& AssetRegisterEntry::getName() const {
		return m_Name;
	}

	const std::string& AssetRegisterEntry::getLocation() const {
		return m_Location;
	}

	const uint32_t AssetRegisterEntry::getBegin() const {
		return m_Begin;
	}

	const uint32_t AssetRegisterEntry::getEnd() const {
		return m_End;
	}



	// -----  END  AssetRegisterEntry -----

	// ----- START AssetRegister -----

	AssetRegister::AssetRegister() {}
	AssetRegister::~AssetRegister() {}

	void AssetRegister::loadFromRegister(const std::string& register_file) {
		Xml::XmlDocument doc = Xml::parseXmlFile(register_file, ASSET_REGISTER_ROOT_NODE_ID);
		const Xml::XmlNode root = doc.getRootNode();

		root.iterate(ASSET_REGISTER_ENTRY_NODE_ID, [this](const Xml::XmlNode& node) -> bool {
			uint32_t id = node.getAttributeAsUint64(ASSET_REGISTER_ENTRY_ATTRIB_ID);
			std::string name = node.getAttribute(ASSET_REGISTER_ENTRY_ATTRIB_NAME);
			std::string location = node.getAttribute(ASSET_REGISTER_ENTRY_ATTRIB_LOCATION);
			uint32_t begin = node.getAttributeAsUint64(ASSET_REGISTER_ENTRY_ATTRIB_BEGIN);
			uint32_t end = node.getAttributeAsUint64(ASSET_REGISTER_ENTRY_ATTRIB_END);

			add(id, name, location, begin, end);
			return true;
		});
	}

	void AssetRegister::exportToRegister(const std::string& register_file) {
		Xml::XmlDocument doc = Xml::createDocument(ASSET_REGISTER_ROOT_NODE_ID);
		
		for (AssetRegistryIt it = m_Entries.begin(); it != m_Entries.end(); it++) {
			Xml::XmlNode entryNode = doc.allocateNode(ASSET_REGISTER_ENTRY_NODE_ID);

			entryNode.appendAttribute(ASSET_REGISTER_ENTRY_ATTRIB_ID, (uint64_t)it->m_Id);
			entryNode.appendAttribute(ASSET_REGISTER_ENTRY_ATTRIB_NAME, it->m_Name.c_str());
			entryNode.appendAttribute(ASSET_REGISTER_ENTRY_ATTRIB_LOCATION, it->m_Location.c_str());
			entryNode.appendAttribute(ASSET_REGISTER_ENTRY_ATTRIB_BEGIN, (uint64_t)it->m_Begin);
			entryNode.appendAttribute(ASSET_REGISTER_ENTRY_ATTRIB_END, (uint64_t)it->m_End);

			doc.appendNodeToRoot(entryNode);
		}

		std::ofstream file(register_file);
		file << doc;
		file.close();
		doc.close();
	}

	void AssetRegister::pack() {
		int i = 0;
		AssetRegistryIt it = m_Entries.begin();
		while (it != m_Entries.end()) {
			it->m_Id = i;
			it++; i++;
		}
	}

	void AssetRegister::clean() {
		m_Entries.clear();
	}

	void AssetRegister::add(const std::string& name, const std::string& location, uint32_t begin, uint32_t end) {
		m_Entries.insert({ nextId(), name, location, begin, end});
	}

	void AssetRegister::add(uint32_t id, const std::string& name, const std::string& location, uint32_t begin, uint32_t end) {
		m_Entries.insert({ id, name, location, begin, end });
	}

	const AssetRegisterEntry& AssetRegister::get(uint32_t id) {
		for (AssetRegistryIt it = m_Entries.begin(); it != m_Entries.end(); it++) {
			if (it->m_Id == id) return (*it);
		}
		return AssetRegisterEntry(UINT_MAX, "NULL", "NULL", UINT_MAX, UINT_MAX);
	}

	const AssetRegisterEntry& AssetRegister::get(const std::string name) {
		for (AssetRegistryIt it = m_Entries.begin(); it != m_Entries.end(); it++) {
			if (it->m_Name == name) return (*it);
		}
		return AssetRegisterEntry(UINT_MAX, "NULL", "NULL", UINT_MAX, UINT_MAX);
	}

	void AssetRegister::updateName(uint32_t id, const std::string& new_name) {
		for (AssetRegistryIt it = m_Entries.begin(); it != m_Entries.end(); it++) {
			if (it->m_Id == id) it->m_Name = new_name;
		}
	}

	void AssetRegister::updateLocation(uint32_t id, const std::string& new_location, uint32_t new_begin, uint32_t new_end) {
		for (AssetRegistryIt it = m_Entries.begin(); it != m_Entries.end(); it++) {
			if (it->m_Id == id) {
				it->m_Location = new_location;
				it->m_Begin = new_begin;
				it->m_End = new_end;
			}
		}
	}

	void AssetRegister::remove(uint32_t id) {
		AssetRegistryIt it = m_Entries.begin();
		while (it != m_Entries.end()) {
			if(it->m_Id == id) m_Entries.erase(it);
			it++;
		}
	}

	void AssetRegister::remove(const std::string& name) {
		AssetRegistryIt it = m_Entries.begin();
		while (it != m_Entries.end()) {
			if (it->m_Name == name) m_Entries.erase(it);
			it++;
		}
	}

	uint32_t AssetRegister::nextId() {
		if (m_Entries.size() == 0) return 0;
		AssetRegistryIt it = m_Entries.end();
		it--;
		return it->m_Id + 1;
	}

	// -----  END  AssetRegister -----
}
