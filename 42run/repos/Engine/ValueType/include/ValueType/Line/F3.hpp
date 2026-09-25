#ifndef  LINE_F3_HPP
# define LINE_F3_HPP

# include "ValueType/Vector/F3.hpp"

struct RayF3;

struct LineF3
{
	public:
	VectorF3	Origin;
	VectorF3	Target;

	public:
	~LineF3() = default;
	LineF3() = default;
	LineF3(const LineF3 & other) = default;
	LineF3 & operator=(const LineF3 & other) = default;

	LineF3(const VectorF3 & origin, const VectorF3 & target);
	LineF3(const RayF3 & ray);



	LineF3	Reverse() const;

	VectorF3	Differance() const;
	float		Length() const;

	VectorF3	Middle() const;
};

#endif