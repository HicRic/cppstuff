#include "pch.h"
#include "math/math.h"

float Math::RandomRange(float min, float max)
{
	return ((max - min) * (static_cast<float>(rand()) / RAND_MAX)) + min;
}
