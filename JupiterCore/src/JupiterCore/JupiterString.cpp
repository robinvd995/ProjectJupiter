#include "JupiterCore/JupiterString.h"

#include <algorithm>
#include <cctype>

namespace Jupiter {

	std::string JString::trimL_copy(std::string s) {
		trimL(s);
		return s;
	}

	std::string JString::trimR_copy(std::string s) {
		trimR(s);
		return s;
	}

	std::string JString::trim_copy(std::string s) {
		trim(s);
		return s;
	}

	void JString::trimL(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	void JString::trimR(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	void JString::trim(std::string& s) {
		trimL(s);
		trimR(s);
	}

	std::string JString::toLower_copy(const std::string& s) {
		std::string ns = s;
		toLower(ns);
		return ns;
	}

	std::string JString::toUpper_copy(const std::string& s) {
		std::string ns = s;
		toUpper(ns);
		return ns;
	}

	void JString::toLower(std::string& s) {
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
			return std::tolower(c);
		});
	}

	void JString::toUpper(std::string& s) {
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
			return std::toupper(c);
		});
	}

}
