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

Ray3D_Hit::Ray3D_Hit(const RayF3 & ray, float interval)
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





#include "ValueType/Trans/3D.hpp"
#include "PolyHedra/Data.hpp"

#include "PolyHedra/Object.hpp"
#include "PolyHedra/ObjectData.hpp"
#include "PolyHedra/PalletManager.hpp"

//#include "PolyHedraUI/Object.hpp"
//#include "PolyHedraUI/ObjectData.hpp"
//#include "PolyHedraUI/PalletManager.hpp"

//#include "NewPolyHedra/DataType/Basic3D/Object.hpp"
//#include "NewPolyHedra/DataType/TransScaleColor3D/Object.hpp"

#include "NewPolyHedra/DataType/Basic3D/ObjectData.hpp"
#include "NewPolyHedra/DataType/TransScaleColor3D/ObjectData.hpp"

//#include "NewPolyHedra/Type/ObjectData.hpp"
#include "NewPolyHedra/Type/Object.hpp"
#include "NewPolyHedra/Type/PalletObjectData.hpp"

#include "NewPolyHedra/PalletObjectManager.hpp"
#include "NewPolyHedra/Pallet.hpp"

void RaySkew(const RayF3 & ray0, Ray3D_Hit & hit0 , const RayF3 & ray1, Ray3D_Hit & hit1)
{
	VectorF3 diff = ray1.Pos - ray0.Pos;
	VectorF3 norm = VectorF3::cross(ray0.Dir, ray1.Dir);

	float norm_inv = 1.0f / norm.length2();

	if (norm_inv != 0.0f)
	{
		hit0 = Ray3D_Hit(ray0, ray1.Dir.cross(norm).dot(diff) * norm_inv);
		hit1 = Ray3D_Hit(ray1, ray0.Dir.cross(norm).dot(diff) * norm_inv);
	}
	else
	{
		hit0 = Ray3D_Hit();
		hit1 = Ray3D_Hit();
	}
}

Plane3D::Plane3D(VectorF3 origin, VectorF3 normal)
	: Origin(origin)
	, Normal(normal)
{ }
Ray3D_Hit RayHitPlane(const RayF3 & ray, const Plane3D & plane)
{
	VectorF3 diff = plane.Origin - ray.Pos;

	float dot = ray.Dir.dot(plane.Normal);
	if (dot != 0.0f)
	{
		return Ray3D_Hit(ray, diff.dot(plane.Normal) / dot);
	}
	else
	{
		return Ray3D_Hit();
	}
}

Triangle3D::Triangle3D(VectorF3 a, VectorF3 b, VectorF3 c)
	: A(a)
	, B(b)
	, C(c)
{ }
Ray3D_Hit RayHitTriangle(const RayF3 & ray, const Triangle3D & triangle)
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
				return Ray3D_Hit(ray, t);
			}
		}
	}
	return Ray3D_Hit();
}



Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans)
{
	Ray3D_Hit_Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];

		Triangle3D triangle(
			polyhedra.Corners[face.udx[0]].Position,
			polyhedra.Corners[face.udx[1]].Position,
			polyhedra.Corners[face.udx[2]].Position
		);

		triangle.A = trans.forward(triangle.A);
		triangle.B = trans.forward(triangle.B);
		triangle.C = trans.forward(triangle.C);

		Ray3D_Hit hit = RayHitTriangle(ray, triangle);
		hit_return.Consider(hit, i);
	}
	return hit_return;
}
Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale)
{
	Ray3D_Hit_Type<unsigned int> hit_return;
	for (unsigned int i = 0; i < polyhedra.Faces.Count(); i++)
	{
		const PolyHedra::Face & face = polyhedra.Faces[i];

		Triangle3D triangle(
			polyhedra.Corners[face.udx[0]].Position,
			polyhedra.Corners[face.udx[1]].Position,
			polyhedra.Corners[face.udx[2]].Position
		);

		triangle.A = trans.forward(triangle.A * scale);
		triangle.B = trans.forward(triangle.B * scale);
		triangle.C = trans.forward(triangle.C * scale);

		Ray3D_Hit hit = RayHitTriangle(ray, triangle);
		hit_return.Consider(hit, i);
	}
	return hit_return;
}

Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraObjectData & object)
{
	return RayHitObject(ray, *(object.PalletManager -> Pallet), object.Trans);
}
Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraObject & object)
{
	if (object.Is())
	{
		return RayHitObject(ray, *object.Pallet(), object.Trans());
	}
	return Ray3D_Hit_Type<unsigned int>();
}

/*Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraUIObjectData & object)
{
	return RayHitObject(ray, *(object.PalletManager -> Pallet), object.Trans, object.Scale);
}*/
/*Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraUIObject & object)
{
	if (object.Is())
	{
		return RayHitObject(ray, *object.Pallet(), object.Trans(), object.Scale());
	}
	return Ray3D_Hit_Type<unsigned int>();
}*/

Ray3D_Hit_Type<unsigned int> RayHitObject0(const RayF3 & ray, const NewPolyHedra_Type_Object<Basic3D::ObjectData> & object)
{
	{
		return RayHitObject(ray, *(object.PalletObjectData -> Manager -> Pallet -> Object), object.Data().Trans);
	}
	return Ray3D_Hit_Type<unsigned int>();
}
Ray3D_Hit_Type<unsigned int> RayHitObject1(const RayF3 & ray, const NewPolyHedra_Type_Object<TransScaleColor3D::ObjectData> & object)
{
	{
		return RayHitObject(ray, *(object.PalletObjectData -> Manager -> Pallet -> Object), object.Data().Trans, object.Data().Scale);
	}
	return Ray3D_Hit_Type<unsigned int>();
}

Ray3D_Hit_Type<unsigned int> RayHitObject0(const RayF3 & ray, const NewPolyHedra_Type_PalletObjectData<Basic3D::ObjectData> & object)
{
	{
		return RayHitObject(ray, *(object.Manager -> Pallet -> Object), object.Data.Trans);
	}
	return Ray3D_Hit_Type<unsigned int>();
}
Ray3D_Hit_Type<unsigned int> RayHitObject1(const RayF3 & ray, const NewPolyHedra_Type_PalletObjectData<TransScaleColor3D::ObjectData> & object)
{
	{
		return RayHitObject(ray, *(object.Manager -> Pallet -> Object), object.Data.Trans, object.Data.Scale);
	}
	return Ray3D_Hit_Type<unsigned int>();
}
