#ifndef  PNG_IHDR_HPP
# define PNG_IHDR_HPP

# include "FileParsing/ByteStreamGetter.hpp"
# include "uint.hpp"

struct VectorU2;

namespace PNG
{
struct IHDR
{
	uint32	width;
	uint32	height;

	uint8	bit_depth;
	uint8	color_type;

	uint8	compression_method;
	uint8	filter_method;
	uint8	interlace_method;

	IHDR();

	void	Parse(ByteStreamGetter & stream);

	VectorU2	ImageSize() const;
	uint64		UncompressedSize() const;

	void	ToConsole() const;
};
};

#endif