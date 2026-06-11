#ifndef  RAY_3D_HIT_HPP
# define RAY_3D_HIT_HPP

# include "ValueType/Ray3D.hpp"
# include "Miscellaneous/Container/Array.hpp"

struct PolyHedra;
struct Trans3D;
struct PolyHedraObject;
struct PolyHedra;
struct SpotLightEntry;

struct Ray3D_Hit
{
	const Ray3D *	Ray;
	float			Interval;
	unsigned int	Index[4];

	// Index[3] is Triangle
	// Index[2] is Container Index
	// Index[1] is Object Selector
	// Index[0] is Object Type

	bool	Is() const;

	VectorF3	Pos() const;

	~Ray3D_Hit();
	Ray3D_Hit();
	Ray3D_Hit(const Ray3D_Hit & other);
	Ray3D_Hit & operator=(const Ray3D_Hit & other);

	Ray3D_Hit(const Ray3D & ray, float interval);

	void	Consider(const Ray3D_Hit & other);
	
	static Ray3D_Hit IntersectHit(const Ray3D & ray, const VectorF3 & a, const VectorF3 & b, const VectorF3 & c);
	static Ray3D_Hit IntersectHit(const Ray3D & ray, const PolyHedra & polyhedra, const Trans3D & trans);
	static Ray3D_Hit IntersectHit(const Ray3D & ray, const PolyHedraObject & object);
	static Ray3D_Hit IntersectHit(const Ray3D & ray, const Container::Array<PolyHedraObject> & objects);
	static Ray3D_Hit IntersectHit(const Ray3D & ray, const SpotLightEntry & light);
	static Ray3D_Hit IntersectHit(const Ray3D & ray, const SpotLightEntry * lights, unsigned int count);
};

#endif