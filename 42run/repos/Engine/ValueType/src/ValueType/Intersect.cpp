#include "ValueType/Intersect.hpp"
#include "ValueType/_Include.hpp"



bool IsIntersecting(
	const RayF2 & ray,
	const LineF2 & line
)
{
	VectorF2 perp(-ray.Dir.Y, +ray.Dir.X);
	VectorF2 diff = line.Target - line.Origin;

	float dot = VectorF2::dot(diff, perp);
	if (dot == 0.0f) { return false; }

	VectorF2 rel = ray.Pos - line.Origin;
	float line_t = rel.dot(perp) / dot;
	if (line_t < 0.0f || line_t > 1.0f) { return false; }

	float ray_t = VectorF2::cross(diff, rel) / dot;
	if (ray_t < 0.0f) { return false; }

	return true;
}

bool IsIntersecting(
	const LineF2 & line0,
	const LineF2 & line1
)
{
	VectorF2 diff0 = line0.Target - line0.Origin;
	VectorF2 perp(-diff0.Y, +diff0.X);
	VectorF2 diff1 = line1.Target - line1.Origin;

	float dot = VectorF2::dot(diff1, perp);
	if (dot == 0.0f) { return false; }

	VectorF2 rel = line0.Origin - line1.Origin;

	float line1_t = rel.dot(perp) / dot;
	if (line1_t < 0.0f || line1_t > 1.0f) { return false; }

	float line0_t = VectorF2::cross(diff1, rel) / dot;
	if (line0_t < 0.0f || line0_t > 1.0f) { return false; }

	return true;
}

bool Intersection(const LineF2 & line0, const LineF2 & line1, VectorF2 & ret)
{
	VectorF2 diff0 = line0.Target - line0.Origin;
	VectorF2 perp(-diff0.Y, +diff0.X);
	VectorF2 diff1 = line1.Target - line1.Origin;

	float dot = VectorF2::dot(diff1, perp);
	if (dot == 0.0f) { return false; }

	VectorF2 rel = line0.Origin - line1.Origin;

	float line1_t = rel.dot(perp) / dot;
	if (line1_t < 0.0f || line1_t > 1.0f) { return false; }

	float line0_t = VectorF2::cross(diff1, rel) / dot;
	if (line0_t < 0.0f || line0_t > 1.0f) { return false; }

	ret = line0.Origin + (diff0 * line0_t);
	return true;
}
