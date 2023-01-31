#pragma once

namespace Jupiter {

	/// <summary>
	/// Namespace mathamathical functions for Jupiter
	/// </summary>
	namespace JMath {
		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		int iMax(int a, int b);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		int& iMaxRef(int& a, int& b);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		float fMax(float a, float b);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		float& fMaxRef(float& a, float& b);
	};

}
