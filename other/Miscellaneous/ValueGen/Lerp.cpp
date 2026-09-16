#include "ValueGen/Lerp.hpp"
#include "ValueType/Vector/F3.hpp"



float Lerp::interpolate(float val0, float val1, float t)
{
	//t = (3.0f - t * 2.0f) * t * t;
	return (val0 * (1.0f - t)) + (val1 * (t - 0.0f));
}
VectorF3 Lerp::interpolate(VectorF3 val0, VectorF3 val1, float t)
{
	return VectorF3(
		interpolate(val0.X, val1.X, t),
		interpolate(val0.Y, val1.Y, t),
		interpolate(val0.Z, val1.Z, t)
	);
}
