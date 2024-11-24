#pragma once

namespace Math
{
	template<typename T> static T Clamp(T x, T min, T max) { return (x < min) ? min : (x > max) ? max : x; }

	/**
	 * \brief Thread-unsafe random float
	 * \param min Inclusive min bounds
	 * \param max Exclusive max bounds
	 * \return Random float
	 */
	float RandomRange(float min, float max);
}
