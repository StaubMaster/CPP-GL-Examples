#ifndef  RAY_3D_HIT_HPP
# define RAY_3D_HIT_HPP

# include "ValueType/Ray3D.hpp"
# include "Miscellaneous/Container/Array.hpp"

struct PolyHedra;
struct Trans3D;
struct PolyHedra;
struct PolyHedraObject;
struct PolyHedraUIObject;

struct Ray3D_Hit
{
	const Ray3D *	Ray;
	float			Interval;

	bool	Is() const;

	VectorF3	Pos() const;

	~Ray3D_Hit();
	Ray3D_Hit();
	Ray3D_Hit(const Ray3D_Hit & other);
	Ray3D_Hit & operator=(const Ray3D_Hit & other);

	Ray3D_Hit(const Ray3D & ray, float interval);

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

Ray3D_Hit RayIntersectHit(const Ray3D & ray, const VectorF3 & a, const VectorF3 & b, const VectorF3 & c);

Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedra & polyhedra, const Trans3D & trans);
Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedra & polyhedra, const Trans3D & trans, float scale);

Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedraObject & object);
Ray3D_Hit_Type<unsigned int> RayIntersectHit(const Ray3D & ray, const PolyHedraUIObject & object);

#endif