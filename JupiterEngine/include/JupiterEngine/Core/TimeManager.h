#pragma once

#include "JupiterEngine/JupiterEngine.h"

namespace Jupiter {

	/// <summary>
	/// 
	/// </summary>
	struct TimeVariables {
		const double m_FixedTimestep;
		const double m_MaxAllowedTimestep;
		const double m_ParticleTimestep;

		TimeVariables() = delete;
		TimeVariables(double fixedTimestep, double maxAllowedTimestep, double particleTimestep) :
			m_FixedTimestep(fixedTimestep), m_MaxAllowedTimestep(maxAllowedTimestep), m_ParticleTimestep(particleTimestep)
		{}
		~TimeVariables() = default;
	};

	/// <summary>
	/// 
	/// </summary>
	class TimeManager {
		MANAGER_CLASS(TimeManager);
		TimeManager(double fixedTimestep, double maxAllowedTimestep, double particleTimestep);

	public:

	private:
		const TimeVariables m_TimeConstants;
		double m_TimeScale = 1.0;
	};

}