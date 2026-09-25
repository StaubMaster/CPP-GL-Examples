#include "ValueType/InteractF3.hpp"

void InteractF3::Skew(const RayF3 & ray0, RayHitF3 & hit0, const RayF3 & ray1, RayHitF3 & hit1)
{
	VectorF3 diff = ray1.Pos - ray0.Pos;
	VectorF3 norm = VectorF3::cross(ray0.Dir, ray1.Dir);

	float norm_inv = 1.0f / norm.length2();

	if (norm_inv != 0.0f)
	{
		hit0 = RayHitF3(ray0, ray1.Dir.cross(norm).dot(diff) * norm_inv);
		hit1 = RayHitF3(ray1, ray0.Dir.cross(norm).dot(diff) * norm_inv);
	}
	else
	{
		hit0 = RayHitF3();
		hit1 = RayHitF3();
	}
}

RayHitF3 InteractF3::Plane(const RayF3 & ray, const NormalPlaneF3 & plane)
{
	VectorF3 diff = plane.Origin - ray.Pos;

	float dot = ray.Dir.dot(plane.Normal);
	if (dot != 0.0f)
	{
		return RayHitF3(ray, diff.dot(plane.Normal) / dot);
	}
	else
	{
		return RayHitF3();
	}
}
RayHitF3 InteractF3::Triangle(const RayF3 & ray, const TriangleF3 & triangle)
{
	VectorF3 plane_vec_0 = triangle.B - triangle.A;
	VectorF3 plane_vec_1 = triangle.C - triangle.A;
	VectorF3 diff_plane_ray = ray.Pos - triangle.A;

	float p, u, v, t;
	VectorF3 normal;

	normal = VectorF3::cross(plane_vec_1, ray.Dir);
	p = VectorF3::dot(normal, plane_vec_0);
	u = VectorF3::dot(normal, diff_plane_ray);

	normal = VectorF3::cross(plane_vec_0, diff_plane_ray);
	v = VectorF3::dot(normal, ray.Dir);
	t = VectorF3::dot(normal, plane_vec_1);

	u /= p;
	v /= p;
	t /= p;

	if (0.0f <= u && u <= 1.0f)
	{
		if (0.0f <= v && (u + v) <= 1.0f)
		{
			if (t > 0.0f)
			{
				return RayHitF3(ray, t);
			}
		}
	}
	return RayHitF3();
}
