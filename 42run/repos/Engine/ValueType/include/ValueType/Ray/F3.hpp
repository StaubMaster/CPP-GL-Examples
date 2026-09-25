#ifndef  RAY_F3_HPP
# define RAY_F3_HPP

# include "ValueType/Vector/F3.hpp"

struct LineF3;

struct RayF3
{
	public:
	VectorF3	Pos;
	VectorF3	Dir;

	public:
	~RayF3() = default;
	RayF3() = default;
	RayF3(const RayF3 & other) = default;
	RayF3 & operator=(const RayF3 & other) = default;

	RayF3(const VectorF3 & pos, const VectorF3 & dir);
	RayF3(const LineF3 & line);
};

#endif