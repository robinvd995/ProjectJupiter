#ifdef JPT_TEST

#include <gtest/gtest.h>

#include "Properties.h"
#include "JptMemory.h"

namespace Jupiter::Io {

	enum EnumTestPropertiesValues {
		ETPV_TEST_VALUE_0 = 0,
		ETPV_TEST_VALUE_1 = 1,
		ETPV_TEST_VALUE_2 = 2,
		ETPV_TEST_VALUE_3 = 3,
	};

	enum EnumTestPropertiesProperties {
		ETP_TEST_PROPERTY_0 = 0,
		ETP_TEST_PROPERTY_1 = 1,
		ETP_TEST_PROPERTY_2 = 2,
		ETP_TEST_PROPERTY_3 = 3,
		ETP_TEST_PROPERTY_4 = 4,
		ETP_TEST_PROPERTY_5 = 5
	};

	enum EnumTestPropertiesGroups {
		ETPG_TEST_GROUP_0 = 0,
		ETPG_TEST_GROUP_1 = 1,
		ETPG_TEST_GROUP_2 = 2,
	};

	class PropertiesTestAdapter {

	public:
		PropertiesTestAdapter() {
			PropertyManager::s_Instance = new PropertyManager();
			MemoryManager::s_Instance = new MemoryManager();
		}

		~PropertiesTestAdapter() {
			delete PropertyManager::s_Instance;
			delete MemoryManager::s_Instance;
		}

		void testBufferPropertyTemplate() {
			uint32_t x = 1;
			uint32_t y = 5;
			uint32_t z = 9;
			BufferPropertyTemplate<uint32_t> uintbuffer({ &x, &y, &z });
			ASSERT_EQ(*uintbuffer.m_Buffer[0], 1);
			ASSERT_EQ(*uintbuffer.m_Buffer[1], 5);
			ASSERT_EQ(*uintbuffer.m_Buffer[2], 9);
		}

		void testPropertyBufferIndexMap() {

		}

		void testPropertyBuffer() {

		}

		void testPropertyValueTemplate() {
			typedef PropertyValueTemplate* PVT;
			PVT pvtTest0 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_0, "test0");
			PVT pvtTest1 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_1, "test1");
			PVT pvtTest2 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_2, "test2");
			PVT pvtTest3 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_3, "test3");

			PVT pvtReg0 = PropertyManager::s_Instance->m_ValueTemplates[ETPV_TEST_VALUE_0];
			PVT pvtReg1 = PropertyManager::s_Instance->m_ValueTemplates[ETPV_TEST_VALUE_1];
			PVT pvtReg2 = PropertyManager::s_Instance->m_ValueTemplates[ETPV_TEST_VALUE_2];
			PVT pvtReg3 = PropertyManager::s_Instance->m_ValueTemplates[ETPV_TEST_VALUE_3];

			ASSERT_EQ(pvtReg0->m_PropertyValueId, pvtTest0->m_PropertyValueId);
			ASSERT_EQ(pvtReg1->m_PropertyValueId, pvtTest1->m_PropertyValueId);
			ASSERT_EQ(pvtReg2->m_PropertyValueId, pvtTest2->m_PropertyValueId);
			ASSERT_EQ(pvtReg3->m_PropertyValueId, pvtTest3->m_PropertyValueId);

			ASSERT_EQ(ETPV_TEST_VALUE_0, pvtReg0->m_PropertyValueId);
			ASSERT_EQ(ETPV_TEST_VALUE_1, pvtReg1->m_PropertyValueId);
			ASSERT_EQ(ETPV_TEST_VALUE_2, pvtReg2->m_PropertyValueId);
			ASSERT_EQ(ETPV_TEST_VALUE_3, pvtReg3->m_PropertyValueId);

			ASSERT_EQ(pvtReg0->m_PropertyValueName, pvtTest0->m_PropertyValueName);
			ASSERT_EQ(pvtReg0->m_PropertyValueName, pvtTest0->m_PropertyValueName);
			ASSERT_EQ(pvtReg0->m_PropertyValueName, pvtTest0->m_PropertyValueName);
			ASSERT_EQ(pvtReg0->m_PropertyValueName, pvtTest0->m_PropertyValueName);

			ASSERT_EQ("test0", pvtReg0->m_PropertyValueName);
			ASSERT_EQ("test1", pvtReg1->m_PropertyValueName);
			ASSERT_EQ("test2", pvtReg2->m_PropertyValueName);
			ASSERT_EQ("test3", pvtReg3->m_PropertyValueName);
		}

		void testPropertyTemplate() {
			typedef PropertyValueTemplate* PVT;
			PVT pvtTest0 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_0, "test0");
			PVT pvtTest1 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_1, "test1");
			PVT pvtTest2 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_2, "test2");
			PVT pvtTest3 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_3, "test3");

			typedef PropertyTemplate* PT;
			PT ptTest0 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_0, "pt_test0", { pvtTest0, pvtTest1 });
			PT ptTest1 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_1, "pt_test1", { pvtTest2, pvtTest3 });

			PT ptReg0 = PropertyManager::s_Instance->m_PropertyTemplates[ETP_TEST_PROPERTY_0];
			PT ptReg1 = PropertyManager::s_Instance->m_PropertyTemplates[ETP_TEST_PROPERTY_1];

			ASSERT_EQ(ETPV_TEST_VALUE_0, PropertyManager::getDefaultValueForProperty(ETP_TEST_PROPERTY_0));
			ASSERT_EQ(ETPV_TEST_VALUE_2, PropertyManager::getDefaultValueForProperty(ETP_TEST_PROPERTY_1));

			ASSERT_EQ(ptTest0->m_PropertyId, ptReg0->m_PropertyId);
			ASSERT_EQ(ptTest1->m_PropertyId, ptReg1->m_PropertyId);

			ASSERT_EQ(ptTest0->m_PropertyName, ptReg0->m_PropertyName);
			ASSERT_EQ(ptTest1->m_PropertyName, ptReg1->m_PropertyName);

			ASSERT_EQ(ptTest0->m_PropertyBufferSize, ptReg0->m_PropertyBufferSize);
			ASSERT_EQ(ptTest1->m_PropertyBufferSize, ptReg1->m_PropertyBufferSize);

			ASSERT_EQ(2, ptTest0->m_AcceptedValues.m_Buffer.size());
			ASSERT_EQ(2, ptTest1->m_AcceptedValues.m_Buffer.size());

			ASSERT_EQ(ETPV_TEST_VALUE_0, ptTest0->m_AcceptedValues.m_Buffer[0]->m_PropertyValueId);
			ASSERT_EQ(ETPV_TEST_VALUE_1, ptTest0->m_AcceptedValues.m_Buffer[1]->m_PropertyValueId);

			ASSERT_EQ(ETPV_TEST_VALUE_2, ptTest1->m_AcceptedValues.m_Buffer[0]->m_PropertyValueId);
			ASSERT_EQ(ETPV_TEST_VALUE_3, ptTest1->m_AcceptedValues.m_Buffer[1]->m_PropertyValueId);
		}

		void testPropertyGroupTemplate() {
			typedef PropertyValueTemplate* PVT;
			PVT pvtTest0 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_0, "test0");
			PVT pvtTest1 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_1, "test1");
			PVT pvtTest2 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_2, "test2");
			PVT pvtTest3 = PropertyManager::addPropertyValueTemplate(ETPV_TEST_VALUE_3, "test3");

			typedef PropertyTemplate* PT;
			PT ptTest0 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_0, "pt_test0", { pvtTest0, pvtTest1 });
			PT ptTest1 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_1, "pt_test1", { pvtTest0, pvtTest2 });
			PT ptTest2 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_2, "pt_test2", { pvtTest0, pvtTest3 });
			PT ptTest3 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_3, "pt_test3", { pvtTest1, pvtTest1 });
			PT ptTest4 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_4, "pt_test4", { pvtTest1, pvtTest2 });
			PT ptTest5 = PropertyManager::addPropertyTemplate(ETP_TEST_PROPERTY_5, "pt_test5", { pvtTest1, pvtTest3 });

			typedef PropertyGroupTemplate* PGT;
			PGT pgtTest0 = PropertyManager::addPropertyGroupTemplate(ETPG_TEST_GROUP_0, "pgt_test0", { ptTest0, ptTest1 });
			PGT pgtTest1 = PropertyManager::addPropertyGroupTemplate(ETPG_TEST_GROUP_1, "pgt_test1", { ptTest2, ptTest3 });
			PGT pgtTest2 = PropertyManager::addPropertyGroupTemplate(ETPG_TEST_GROUP_2, "pgt_test2", { ptTest4, ptTest5 });
		}

		void testPropertyManager() {

		}

	private:

	};

}

TEST(properties_test, buffer_property_template) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testBufferPropertyTemplate();
}

TEST(properties_test, property_buffer_index_map) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testPropertyBufferIndexMap();
}

TEST(properties_test, property_buffer) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testPropertyBuffer();
}

TEST(properties_test, property_value_template) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testPropertyValueTemplate();
}

TEST(properties_test, property_template) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testPropertyTemplate();
}

TEST(properties_test, property_group_template) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testPropertyGroupTemplate();
}

TEST(properties_test, property_manager) {
	Jupiter::Io::PropertiesTestAdapter testAdapter;
	testAdapter.testPropertyManager();
}

#endif
