#pragma once

#include <string>

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	namespace JString {

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		std::string trimL_copy(std::string s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		std::string trimR_copy(std::string s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		std::string trim_copy(std::string s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		void trimL(std::string& s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		void trimR(std::string& s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		void trim(std::string& s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		std::string toLower_copy(const std::string& s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		std::string toUpper_copy(const std::string& s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		void toLower(std::string& s);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="s"></param>
		void toUpper(std::string& s);
	}

}
