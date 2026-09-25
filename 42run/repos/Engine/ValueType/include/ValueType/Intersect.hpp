#ifndef  INTERSECT_HPP
# define INTERSECT_HPP

# include "ValueType/_Declare.hpp"

namespace Intersect { };

bool IsIntersecting(
	const RayF2 & ray,
	const LineF2 & line
);

bool IsIntersecting(
	const LineF2 & line0,
	const LineF2 & line1
);

bool Intersection(
	const LineF2 & line0,
	const LineF2 & line1,
	VectorF2 & ret
);

#endif