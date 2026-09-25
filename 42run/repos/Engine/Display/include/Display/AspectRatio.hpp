#ifndef  DISPLAY_ASPECT_RATIO_HPP
# define DISPLAY_ASPECT_RATIO_HPP

# include "ValueType/Vector/F2.hpp"

/*
	AspectRatio.X = size.X / v
	AspectRatio.Y = size.Y / v

	AspectRatio.X [ 0.0 , 1.0 ]
	AspectRatio.Y [ 0.0 , 1.0 ]
*/
struct AspectRatio
{
	VectorF2		Value;

	~AspectRatio();
	AspectRatio();
	
	AspectRatio(const AspectRatio & other);
	AspectRatio & operator=(const AspectRatio & other);

	AspectRatio(VectorF2 size);
	void Change(VectorF2 size);
};

#endif