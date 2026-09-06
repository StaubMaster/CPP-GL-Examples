#ifndef  AXIS_2D_ENUMS_HPP
# define AXIS_2D_ENUMS_HPP

namespace Axis2D
{
	enum class Abs : unsigned char
	{
		None = 0b00,
		X    = 0b01,
		Y    = 0b10,
	}; // 3 Values ; 2 Bits

	enum class Rel : unsigned char
	{
		None  = 0b000,
		PrevX = 0b001,
		PrevY = 0b010,
//		PrevZ = 0b100,
		NextX = 0b110,
		NextY = 0b101,
//		NextZ = 0b011,
		Here  = 0b111,
	}; // 6 Values ; 3 Bits

	enum class Diag : unsigned char
	{
		Normal0, // (+X, +Y)
		Invert0, // (+Y, +X)
		Normal1, // (-X, -Y)
		Invert1, // (-Y, -X)
	}; // 4 Values ; 2 Bits

	enum class Flip : unsigned char
	{
		None , // (+X, +Y)
		FlipX, // (+X, -Y)
		FlipY, // (-X, +Y)
	}; // 3 Values ; 2 Bits
};

#endif