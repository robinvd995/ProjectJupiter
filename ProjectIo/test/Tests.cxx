#include "gtest/gtest.h"

#include <iostream>

int main() {
	std::cout << "Test Environment!" << std::endl;
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
