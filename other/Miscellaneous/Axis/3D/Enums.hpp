#ifndef  AXIS_3D_ENUMS_HPP
# define AXIS_3D_ENUMS_HPP

namespace Axis3D
{
	enum class Abs : unsigned char
	{
		None = 0b00,
		X    = 0b01,
		Y    = 0b10,
		Z    = 0b11,
	}; // 4 Values ; 2 Bits

	enum class Rel : unsigned char
	{
		None  = 0b000,
		PrevX = 0b001,
		PrevY = 0b010,
		PrevZ = 0b100,
		NextX = 0b110,
		NextY = 0b101,
		NextZ = 0b011,
		Here  = 0b111,
	}; // 8 Values ; 3 Bits

	enum class Diag : unsigned char
	{
		Here,  // (+X, +Y, +Z)
		Next,  // (+Z, +X, +Y)
		Prev,  // (+Y, +Z, +X)
		DiagX, // (-X, -Z, -Y)
		DiagY, // (-Z, -Y, -X)
		DiagZ, // (-Y, -X, -Z)
	}; // 6 Values ; 3 Bits

	enum class Flip : unsigned char
	{
		None,  // (+X, +Y, +Z)
		FlipX, // (+X, -Y, -Z)
		FlipY, // (-X, +Y, -Z)
		FlipZ, // (-X, -Y, +Z)
	}; // 4 Values ; 2 Bits
};

#endif