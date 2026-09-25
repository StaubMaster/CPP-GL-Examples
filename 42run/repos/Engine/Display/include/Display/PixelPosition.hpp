#ifndef  DISPLAY_PIXEL_POSITION_HPP
# define DISPLAY_PIXEL_POSITION_HPP

# include "ValueType/Vector/F2.hpp"

struct PixelPosition
{
	VectorF2		Corner;
	VectorF2		Center;

	~PixelPosition();
	PixelPosition();

	PixelPosition(const PixelPosition & other);
	PixelPosition & operator=(const PixelPosition & other);
};

#endif