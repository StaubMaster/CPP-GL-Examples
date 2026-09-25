#ifndef  LINE_F2_HPP
# define LINE_F2_HPP

# include "ValueType/Vector/F2.hpp"

struct RayF2;

struct LineF2
{
	public:
	VectorF2	Origin;
	VectorF2	Target;

	public:
	~LineF2() = default;
	LineF2() = default;
	LineF2(const LineF2 & other) = default;
	LineF2 & operator=(const LineF2 & other) = default;

	LineF2(const VectorF2 & origin, const VectorF2 & target);
	LineF2(const RayF2 & ray);



	LineF2	Reverse() const;

	VectorF2	Differance() const;
	float		Length() const;

	VectorF2	Middle() const;
	VectorF2	Normal() const;
};

#endif