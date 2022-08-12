#ifdef JPT_TEST

#include <gtest/gtest.h>
#include "AssetRegister.h"

#include <iostream>

namespace Jupiter::Io {

	class AssetRegisterTestAdapter {

	public:

		AssetRegisterTestAdapter() {
			AssetRegister::s_Instance = new AssetRegister();
		}

		~AssetRegisterTestAdapter() {
			delete AssetRegister::s_Instance;
		}

		static void testRegisterSet() {
			AssetRegister::s_Instance->add(0, "asset.0", "loc0", 0, 0);
			AssetRegister::s_Instance->add(1, "asset.0", "loc0", 0, 0);
			AssetRegister::s_Instance->add(1, "asset.0", "loc0", 0, 0);
			AssetRegister::s_Instance->add(9, "asset.0", "loc0", 0, 0);
			AssetRegister::s_Instance->add(2, "asset.0", "loc0", 0, 0);
			AssetRegister::s_Instance->add(7, "asset.0", "loc0", 0, 0);

			int i = 0;
			int data0[] = {0, 1, 2, 7, 9};
			for (const AssetRegisterEntry& entry : AssetRegister::s_Instance->m_Entries) {
				ASSERT_EQ(entry.m_Id, data0[i++]);
			}

			AssetRegister::s_Instance->pack();
			i = 0;
			int data1[] = {0, 1, 2, 3, 4};
			for (const AssetRegisterEntry& entry : AssetRegister::s_Instance->m_Entries) {
				ASSERT_EQ(data1[i++], entry.m_Id);
			}

			AssetRegister::s_Instance->m_Entries.insert({ 6, "asset.6", "loc6", 0, 0 });
			auto it = AssetRegister::s_Instance->m_Entries.end();
			it--;
			ASSERT_EQ(it->m_Id, 6);

			AssetRegister::s_Instance->pack();
			it = AssetRegister::s_Instance->m_Entries.end();
			it--;
			ASSERT_EQ(it->m_Id, 5);

			AssetRegister::s_Instance->exportToRegister("test_asset_register.xml");
			ASSERT_EQ(AssetRegister::s_Instance->m_Entries.size(), 6);

			AssetRegister::s_Instance->clean();
			ASSERT_EQ(AssetRegister::s_Instance->m_Entries.size(), 0);

			AssetRegister::s_Instance->loadFromRegister("test_asset_register.xml");

			i = 0;
			int data2[] = { 0, 1, 2, 3, 4, 5 };
			for (const AssetRegisterEntry& entry : AssetRegister::s_Instance->m_Entries) {
				ASSERT_EQ(data2[i++], entry.m_Id);
			}

			AssetRegister::s_Instance->clean();

			AssetRegister::s_Instance->add("asset.no_id0", "loc0", 4, 8);
			AssetRegister::s_Instance->add("asset.no_id1", "loc1", 16, 32);
			AssetRegister::s_Instance->add("asset.no_id2", "loc2", 64, 128);

			i = 0;
			int data3[] = { 0, 1, 2 };
			for (const AssetRegisterEntry& entry : AssetRegister::s_Instance->m_Entries) {
				ASSERT_EQ(data3[i++], entry.m_Id);
			}
			
			AssetRegister::s_Instance->exportToRegister("test_asset_register1.xml");
			AssetRegister::s_Instance->clean();
			ASSERT_EQ(AssetRegister::s_Instance->m_Entries.size(), 0);

			AssetRegister::s_Instance->loadFromRegister("test_asset_register1.xml");
			ASSERT_EQ(AssetRegister::s_Instance->m_Entries.size(), 3);

			i = 0;
			int data4[] = { 0, 1, 2 };
			for (const AssetRegisterEntry& entry : AssetRegister::s_Instance->m_Entries) {
				ASSERT_EQ(data4[i++], entry.m_Id);
			}

			const AssetRegisterEntry& entry = AssetRegister::s_Instance->get(0);
			ASSERT_EQ(0, entry.getId());
			ASSERT_EQ("asset.no_id0", entry.getName());
			ASSERT_EQ("loc0", entry.getLocation());
			ASSERT_EQ(4, entry.getBegin());
			ASSERT_EQ(8, entry.getEnd());
		}
	};

}



TEST(asset_register_tests, register_tests) {
	Jupiter::Io::AssetRegisterTestAdapter adapter;
	adapter.testRegisterSet();
}

#endif
