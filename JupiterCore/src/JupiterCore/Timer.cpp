#include "JupiterCore/JupiterTimer.h"

namespace Jupiter {

	void JTimer::start() {
		m_Start = std::chrono::high_resolution_clock::now();
	}

	void JTimer::end() {
		m_End = std::chrono::high_resolution_clock::now();
	}

	float JTimer::getTimeMS() {
		std::chrono::duration<float, std::milli> ms_float = m_End - m_Start;
		return ms_float.count();
	}

	float JTimer::getTimeS() {
		std::chrono::duration<float, std::milli> ms_float = m_End - m_Start;
		return ms_float.count() / 1000.0f;
	}

}