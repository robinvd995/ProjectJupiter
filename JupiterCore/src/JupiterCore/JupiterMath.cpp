#include "JupiterCore/JupiterMath.h"

namespace Jupiter {

	int JMath::iMax(int a, int b) {
		return a > b ? a : b;
	}

	int& JMath::iMaxRef(int& a, int& b) {
		return a > b ? a : b;
	}

	float JMath::fMax(float a, float b) {
		return a > b ? a : b;
	}

	float& JMath::fMaxRef(float& a, float& b) {
		return a > b ? a : b;
	}

}