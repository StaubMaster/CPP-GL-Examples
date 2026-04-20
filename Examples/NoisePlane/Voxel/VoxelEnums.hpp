#ifndef  VOXEL_ENUMS_HPP
# define VOXEL_ENUMS_HPP

# include <iosfwd>



enum class Axis : unsigned char
{
	Here  = 0b000,
	PrevX = 0b001,
	PrevY = 0b010,
	PrevZ = 0b100,
	NextX = 0b110,
	NextY = 0b101,
	NextZ = 0b011,
	None  = 0b111,
}; // 8 Values ; 3 Bits
std::ostream & operator<<(std::ostream & s, Axis axis);



/*
Diag::Here : (+X, +Y, +Z)
Diag::Prev : (+Z, +X, +Y)
Diag::Next : (+Y, +Z, +X)
Diag::DiagX: (-X, -Z, -Y)
Diag::DiagY: (-Z, -Y, -X)
Diag::DiagZ: (-Y, -X, -Z)
*/
enum class Diag : unsigned char
{
	Here,
	Next,
	Prev,
	DiagX,
	DiagY,
	DiagZ,
}; // 6 Values ; 3 Bits
std::ostream & operator<<(std::ostream & s, Diag diag);



/*
Flip::None : (+X, +Y, +Z)
Flip::FlipX: (+X, -Y, -Z)
Flip::FlipY: (-X, +Y, -Z)
Flip::FlipZ: (-X, -Y, +Z)
*/
enum class Flip : unsigned char
{
	None,
	FlipX,
	FlipY,
	FlipZ,
}; // 4 Values ; 2 Bits
std::ostream & operator<<(std::ostream & s, Flip flip);

#endif