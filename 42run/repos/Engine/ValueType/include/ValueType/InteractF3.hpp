#ifndef  INTERSECT_F3_HPP
# define INTERSECT_F3_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

# include "ValueType/NormalPlaneF3.hpp"
# include "ValueType/TriangleF3.hpp"

namespace InteractF3
{
	void	Skew(const RayF3 & ray0, RayHitF3 & hit0, const RayF3 & ray1, RayHitF3 & hit1);

	RayHitF3	Plane(const RayF3 & ray, const NormalPlaneF3 & plane);
	RayHitF3	Triangle(const RayF3 & ray, const TriangleF3 & triangle);
};

#endif