#pragma once

#include <iostream>

//#define JPT_LOG(...) std::cout << __VA_ARGS__ << std::endl;
#define JPT_INFO(message) std::cout << "\033[0m[INFO]: " << message << "\033[0m" << std::endl;
#define JPT_ERROR(message) std::cout << "\033[31m[ERROR]: " << message << "\033[0m" << std::endl;
#define JPT_TRACE(message) std::cout << "\033[32m[TRACE]: " << message << "\033[0m" << std::endl;
#define JPT_WARN(message) std::cout << "\033[33m[WARNING]: " << message << "\033[0m" << std::endl;
