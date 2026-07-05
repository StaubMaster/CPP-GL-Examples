#ifndef  RAY_3D_HIT_HPP
# define RAY_3D_HIT_HPP

# include "ValueType/Ray/F3.hpp"
# include "Miscellaneous/Container/Array.hpp"

struct Ray3D_Hit
{
	const RayF3 *	Ray;
	float			Interval;

	bool	Is() const;

	VectorF3	Pos() const;

	~Ray3D_Hit();
	Ray3D_Hit();
	Ray3D_Hit(const Ray3D_Hit & other);
	Ray3D_Hit & operator=(const Ray3D_Hit & other);

	Ray3D_Hit(const RayF3 & ray, float interval);

	bool	Consider(const Ray3D_Hit & other);
};

template<typename IndexType>
struct Ray3D_Hit_Type : public Ray3D_Hit
{
	IndexType	Index;

	Ray3D_Hit_Type()
		: Ray3D_Hit()
	{ }
	Ray3D_Hit_Type(IndexType index)
		: Ray3D_Hit()
		, Index(index)
	{ }

	bool Consider(const Ray3D_Hit & other, IndexType index)
	{
		if (Ray3D_Hit::Consider(other))
		{
			Index = index;
			return true;
		}
		return false;
	}
};

void RaySkew(const RayF3 & ray0, Ray3D_Hit & hit0 , const RayF3 & ray1, Ray3D_Hit & hit1);

struct Plane3D
{
	VectorF3	Origin;
	VectorF3	Normal;
	Plane3D(VectorF3 origin, VectorF3 normal);
};
Ray3D_Hit RayHitPlane(const RayF3 & ray, const Plane3D & plane);

struct Triangle3D
{
	VectorF3	A;
	VectorF3	B;
	VectorF3	C;
	Triangle3D(VectorF3 a, VectorF3 b, VectorF3 c);
};
Ray3D_Hit RayHitTriangle(const RayF3 & ray, const Triangle3D & triangle);



struct Trans3D;
class PolyHedra;



struct PolyHedraObject;
struct PolyHedraObjectData;

//struct PolyHedraUIObject;
//struct PolyHedraUIObjectData;

struct NewPolyHedra_Pallet;
struct NewPolyHedra_PalletObjectManager;

namespace Basic3D { struct ObjectData; };
namespace TransScaleColor3D { struct ObjectData; };
template<typename TypeData> struct NewPolyHedra_Type_Object;
template<typename TypeData> struct NewPolyHedra_Type_PalletObjectData;

Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans);
Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale);

Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraObjectData & object);
Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraObject & object);

//Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraUIObjectData & object);
//Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const PolyHedraUIObject & object);

Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra_Type_Object<Basic3D::ObjectData> & object);
Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra_Type_Object<TransScaleColor3D::ObjectData> & object);

Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra_Type_PalletObjectData<Basic3D::ObjectData> & object);
Ray3D_Hit_Type<unsigned int> RayHitObject(const RayF3 & ray, const NewPolyHedra_Type_PalletObjectData<TransScaleColor3D::ObjectData> & object);

#endif