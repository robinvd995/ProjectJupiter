#pragma once

#include <chrono>

namespace Jupiter {

	typedef std::chrono::steady_clock::time_point JTimePoint;

	/// <summary>
	/// Simple class for timing a from start call to end call
	/// </summary>
	class JTimer {

	public:
		JTimer() = default;
		~JTimer() = default;

		/// <summary>
		/// Start the timer
		/// </summary>
		void start();

		/// <summary>
		/// End the timer
		/// </summary>
		void end();

		/// <summary>
		/// Get the time in milliseconds
		/// </summary>
		/// <returns>The time elapsed from start to end returned in milliseconds</returns>
		float getTimeMS();

		/// <summary>
		/// Get the time in seconds
		/// </summary>
		/// <returns>The time elapsed from start to end returned in seconds</returns>
		float getTimeS();

	private:
		JTimePoint m_Start;
		JTimePoint m_End;
	};
}