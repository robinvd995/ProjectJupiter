#pragma once

#include "Core.h"

#include <set>

namespace Jupiter::Io {

	struct AssetRegisterEntry {
		friend class AssetRegister;
		JPT_IO_TEST_CLASS(AssetRegisterTestAdapter)

	private:
		mutable uint32_t m_Id;
		mutable std::string m_Name;
		mutable std::string m_Location;
		mutable uint32_t m_Begin;
		mutable uint32_t m_End;

		AssetRegisterEntry(uint32_t id, const std::string& name, const std::string& location, uint32_t begin, uint32_t end);

	public:
		bool operator<(const AssetRegisterEntry& other) const;
		bool operator==(const AssetRegisterEntry& other);

		/// <summary>
		/// Gets the id of the entry.
		/// </summary>
		const uint32_t getId() const;

		/// <summary>
		/// Gets the name of the entry.
		/// </summary>
		const std::string& getName() const;

		/// <summary>
		/// Gets the source file location of the entry.
		/// </summary>
		const std::string& getLocation() const;

		/// <summary>
		/// Gets the start of the data within the source file.
		/// </summary>
		const uint32_t getBegin() const;

		/// <summary>
		/// Gets the end of the data withing the source file.
		/// </summary>
		const uint32_t getEnd() const;
	};

	typedef std::set<AssetRegisterEntry> AssetRegistry;
	typedef std::set<AssetRegisterEntry>::iterator AssetRegistryIt;

	class AssetRegister {
		JPT_IO_MANAGER_CLASS(AssetRegister) 
		JPT_IO_TEST_CLASS(AssetRegisterTestAdapter)

	public:
		/// <summary>
		/// Loads the register from a file.
		/// </summary>
		/// <param name="register_file">Name of the file to load from.</param>
		void loadFromRegister(const std::string& register_file);

		/// <summary>
		/// Exports the register to a file.
		/// </summary>
		/// <param name="register_file">Name of the file to export to.</param>
		void exportToRegister(const std::string& register_file);

		/// <summary>
		/// Packs all the id's of the assets, makes it so there are no gaps between assets.
		/// ex. 1,3,6 -> 0,1,2
		/// </summary>
		void pack();

		/// <summary>
		/// Cleans the register, emptying out all the assets registered to this object.
		/// </summary>
		void clean();

		/// <summary>
		/// Adds a new entry to the register, the integer id will be determined by the Register.
		/// </summary>
		/// <param name="name">The name of the asset.</param>
		/// <param name="location">The location of the source file of the asset.</param>
		/// <param name="begin">The location in the source file where the asset data starts.</param>
		/// <param name="end">The location in the source file where the asset data ends.</param>
		void add(const std::string& name, const std::string& location, uint32_t begin, uint32_t end);

		/// <summary>
		/// Adds a new entry to the register.
		/// </summary>
		/// <param name="id">The integer representation of the asset id.</param>
		/// <param name="name">The name of the asset.</param>
		/// <param name="location">The location of the source file of the asset.</param>
		/// <param name="begin">The location in the source file where the asset data starts.</param>
		/// <param name="end">The location in the source file where the asset data ends.</param>
		void add(uint32_t id, const std::string& name, const std::string& location, uint32_t begin, uint32_t end);

		/// <summary>
		/// Gets an entry in the register.
		/// </summary>
		/// <param name="id">The integer representation of the asset id.</param>
		/// <returns>The entry accociated with the passed id, if nothing has been found the returned entry will have an id equal to 2^32 - 1</returns>
		const AssetRegisterEntry& get(uint32_t id);

		/// <summary>
		/// Gets an entry in the register.
		/// </summary>
		/// <param name="name">The name of the asset.</param>
		/// <returns>The entry accociated with the passed id, if nothing has been found the returned entry will have an id equal to 2^32 - 1</returns>
		const AssetRegisterEntry& get(const std::string name);

		/// <summary>
		/// Updates the name of the asset entry
		/// </summary>
		/// <param name="id">The integer representation of the asset id.</param>
		/// <param name="new_name">The new value of name</param>
		void updateName(uint32_t id, const std::string& new_name);

		/// <summary>
		/// Updates the location info of the asset entry
		/// </summary>
		/// <param name="id">The integer representation of the asset id.</param>
		/// <param name="new_location">The new location of the source file.</param>
		/// <param name="new_begin">The new starting point of the asset data within the source file.</param>
		/// <param name="new_end">The new end point of the asset data withing the source file./param>
		void updateLocation(uint32_t id, const std::string& new_location, uint32_t new_begin, uint32_t new_end);

		/// <summary>
		/// Removes an registered entry
		/// </summary>
		/// <param name="id">The integer representation of the asset id.</param>
		void remove(uint32_t id);

		/// <summary>
		/// Removes an registered entry
		/// </summary>
		/// <param name="name">The string representation of the asset id.</param>
		void remove(const std::string& name);

		/// <summary>
		/// Gets the next available id in the registry
		/// </summary>
		/// <returns>Integer value representing the next available id in the registry</returns>
		uint32_t nextId();

	private:
		AssetRegistry m_Entries;
	};
}
