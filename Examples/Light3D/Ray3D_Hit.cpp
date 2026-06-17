#include "Ray3D_Hit.hpp"



bool Ray3D_Hit::Is() const { return (Ray != nullptr); }

VectorF3 Ray3D_Hit::Pos() const
{
	return (Ray -> Pos) + ((Ray -> Dir) * Interval);
}

Ray3D_Hit::~Ray3D_Hit()
{ }
Ray3D_Hit::Ray3D_Hit()
	: Ray(nullptr)
{ }
Ray3D_Hit::Ray3D_Hit(const Ray3D_Hit & other)
	: Ray(other.Ray)
	, Interval(other.Interval)
{ }
Ray3D_Hit & Ray3D_Hit::operator=(const Ray3D_Hit & other)
{
	Ray = other.Ray;
	Interval = other.Interval;
	return *this;
}

Ray3D_Hit::Ray3D_Hit(const Ray3D & ray, float interval)
	: Ray(&ray)
	, Interval(interval)
{ }

bool Ray3D_Hit::Consider(const Ray3D_Hit & other)
{
	if (other.Is() && (!Is() || other.Interval < Interval))
	{
		*this = other;
		return true;
	}
	return false;
}





#include "ValueType/Trans3D.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Object.hpp"
#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/PalletManager.hpp"
#include "PolyHedraUI/Object.hpp"

Ray3D_Hit RayIntersectHit(const Ray3D & ray, const VectorF3 & a, const VectorF3 & b, const VectorF3 & c)
{
	VectorF3 plane_vec_0 = b - a;
	VectorF3 plane_vec_1 = c - a;
	VectorF3 diff_plane_ray = ray.Pos - a;

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
				return Ray3D_Hit(ray, t);
			}
		}
	}
	return Ray3D_Hit();
}

Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedra & polyhedra, const Trans3D & trans)
{
	Ray3D_Hit_Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];

		VectorF3 a = polyhedra.Corners[face.udx[0]].Position;
		VectorF3 b = polyhedra.Corners[face.udx[1]].Position;
		VectorF3 c = polyhedra.Corners[face.udx[2]].Position;

		a = trans.forward(a);
		b = trans.forward(b);
		c = trans.forward(c);

		Ray3D_Hit hit = RayIntersectHit(ray, a, b, c);
		hit_return.Consider(hit, i);
	}
	return hit_return;
}
Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale)
{
	Ray3D_Hit_Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];

		VectorF3 a = polyhedra.Corners[face.udx[0]].Position;
		VectorF3 b = polyhedra.Corners[face.udx[1]].Position;
		VectorF3 c = polyhedra.Corners[face.udx[2]].Position;

		a = trans.forward(a * scale);
		b = trans.forward(b * scale);
		c = trans.forward(c * scale);

		Ray3D_Hit hit = RayIntersectHit(ray, a, b, c);
		hit_return.Consider(hit, i);
	}
	return hit_return;
}

Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedraObjectData & object)
{
	return RayIntersectHit(ray, *(object.PalletManager -> Pallet), object.Trans);
}
Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedraObject & object)
{
	if (object.Is())
	{
		return RayIntersectHit(ray, *object.Pallet(), object.Trans());
	}
	return Ray3D_Hit_Type<unsigned int>();
}
Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedraUIObject & object)
{
	if (object.Is())
	{
		return RayIntersectHit(ray, *object.Pallet(), object.Trans(), object.Scale());
	}
	return Ray3D_Hit_Type<unsigned int>();
}
