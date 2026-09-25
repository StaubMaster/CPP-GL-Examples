#ifndef  NORMAL_PLANE_F3_HPP
# define NORMAL_PLANE_F3_HPP

# include "Vector/F3.hpp"

struct NormalPlaneF3
{
	public:
	VectorF3	Origin;
	VectorF3	Normal;

	public:
	~NormalPlaneF3() = default;
	NormalPlaneF3() = default;
	NormalPlaneF3(const NormalPlaneF3 & other) = default;
	NormalPlaneF3 & operator=(const NormalPlaneF3 & other) = default;

	public:
	NormalPlaneF3(const VectorF3 & origin, const VectorF3 & normal);
};

#endif