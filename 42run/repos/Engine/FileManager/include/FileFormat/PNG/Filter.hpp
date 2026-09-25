#ifndef  PNG_FILTER_HPP
# define PNG_FILTER_HPP

# include "IHDR.hpp"
# include "ValueType/Vector/U2.hpp"
# include "FileParsing/ByteStreamQueue.hpp"
# include "PNG.hpp"

class	Image;

namespace PNG
{
namespace Filter
{
	static const uint8	rel_X = 0b01;
	static const uint8	rel_Y = 0b10;
	static const uint8	rel_XY = 0b11;

	uint8	getPixel(Image & img, VectorU2 pxl, uint8 col, uint8 rel);

	void	filter_None(Image & img, VectorU2 pxl, uint8 col, uint8 byte);
	void	filter_Sub(Image & img, VectorU2 pxl, uint8 col, uint8 byte);
	void	filter_Up(Image & img, VectorU2 pxl, uint8 col, uint8 byte);
	void	filter_Avg(Image & img, VectorU2 pxl, uint8 col, uint8 byte);
	void	filter_Paeth(Image & img, VectorU2 pxl, uint8 col, uint8 byte);

	Image	filter(IHDR head, ByteBlock data);
};
};

#endif