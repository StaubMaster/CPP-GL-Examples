#ifndef SPLINE_OBJECT
#define SPLINE_OBJECT

struct SplineObject
{
	unsigned int	Index;
	float			SplineValue;

	SplineObject() { }
	SplineObject(unsigned int idx, float val)
	{
		Index = idx;
		SplineValue = val;
	}
};

#endif