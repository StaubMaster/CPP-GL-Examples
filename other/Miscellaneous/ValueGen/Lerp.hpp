#ifndef  LERP_HPP
# define LERP_HPP

// other/Interpolation
// why is that in a different other/ ?
// but this isnt ?
// make other/ValueGen
// put other/InterPolation in there

struct VectorF3;

namespace Lerp
{
	float		interpolate(float val0, float val1, float t);
	VectorF3	interpolate(VectorF3 val0, VectorF3 val1, float t);
};

#endif