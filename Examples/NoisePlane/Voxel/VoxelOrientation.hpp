#ifndef  VOXEL_ORIENTATION_HPP
# define VOXEL_ORIENTATION_HPP

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

enum class Diag : unsigned char
{
	Here,
	Next,
	Prev,
	DiagX,
	DiagY,
	DiagZ,
}; // 6 Values ; 3 Bits
/*
Diag::Here : (+X, +Y, +Z)
Diag::Prev : (+Z, +X, +Y)
Diag::Next : (+Y, +Z, +X)
Diag::DiagX: (-X, -Z, -Y)
Diag::DiagY: (-Z, -Y, -X)
Diag::DiagZ: (-Y, -X, -Z)
*/

enum class Flip : unsigned char
{
	None,
	FlipX,
	FlipY,
	FlipZ,
}; // 4 Values ; 2 Bits
/*
Flip::None : (+X, +Y, +Z)
Flip::FlipX: (+X, -Y, -Z)
Flip::FlipY: (-X, +Y, -Z)
Flip::FlipZ: (-X, -Y, +Z)
*/

/*
  Diag::Here   Flip::None   XYZ +++
  Diag::Prev   Flip::None   ZXY +++
  Diag::Next   Flip::None   YZX +++
  Diag::Here   Flip::FlipX  XYZ +--
  Diag::Prev   Flip::FlipX  ZXY +--
  Diag::Next   Flip::FlipX  YZX +--
  Diag::Here   Flip::FlipY  XYZ -+-
  Diag::Prev   Flip::FlipY  ZXY -+-
  Diag::Next   Flip::FlipY  YZX -+-
  Diag::Here   Flip::FlipZ  XYZ --+
  Diag::Prev   Flip::FlipZ  ZXY --+
  Diag::Next   Flip::FlipZ  YZX --+
  Diag::DiagX  Flip::None   XZY ---
  Diag::DiagY  Flip::None   ZYX ---
  Diag::DiagZ  Flip::None   YXZ ---
  Diag::DiagX  Flip::FlipX  XZY -++
  Diag::DiagY  Flip::FlipX  ZYX -++
  Diag::DiagZ  Flip::FlipX  YXZ -++
  Diag::DiagX  Flip::FlipY  XZY +-+
  Diag::DiagY  Flip::FlipY  ZYX +-+
  Diag::DiagZ  Flip::FlipY  YXZ +-+
  Diag::DiagX  Flip::FlipZ  XZY ++-
  Diag::DiagY  Flip::FlipZ  ZYX ++-
  Diag::DiagZ  Flip::FlipZ  YXZ ++-
*/

# include "ValueType/VectorF3.hpp"

/*struct AxisPair
{
	::Axis	Prev;
	::Axis	Next;
	~AxisPair();
	AxisPair();
	AxisPair(::Axis prev, ::Axis next);
	AxisPair(const AxisPair & other);
	AxisPair & operator=(const AxisPair & other);
	AxisPair operator+() const;
	AxisPair operator-() const;
	static AxisPair X();
	static AxisPair Y();
	static AxisPair Z();
};*/
/*struct AxisOrientation
{
	AxisPair	X;
	AxisPair	Y;
	AxisPair	Z;
	~AxisOrientation();
	AxisOrientation();
	AxisOrientation(AxisPair x, AxisPair y, AxisPair z);
	AxisOrientation(const AxisOrientation & other);
	AxisOrientation & operator=(const AxisOrientation & other);
	void make(::Diag diag, ::Flip flip);
};*/
/*static AxisOrientation AxisOrientations[24] =
{
	AxisOrientation(Diag::Here , Flip::None ), //  XYZ +++
	AxisOrientation(Diag::Prev , Flip::None ), //  ZXY +++
	AxisOrientation(Diag::Next , Flip::None ), //  YZX +++
	AxisOrientation(Diag::Here , Flip::FlipX), //  XYZ +--
	AxisOrientation(Diag::Prev , Flip::FlipX), //  ZXY +--
	AxisOrientation(Diag::Next , Flip::FlipX), //  YZX +--
	AxisOrientation(Diag::Here , Flip::FlipY), //  XYZ -+-
	AxisOrientation(Diag::Prev , Flip::FlipY), //  ZXY -+-
	AxisOrientation(Diag::Next , Flip::FlipY), //  YZX -+-
	AxisOrientation(Diag::Here , Flip::FlipZ), //  XYZ --+
	AxisOrientation(Diag::Prev , Flip::FlipZ), //  ZXY --+
	AxisOrientation(Diag::Next , Flip::FlipZ), //  YZX --+
	AxisOrientation(Diag::DiagX, Flip::None ), //  XZY ---
	AxisOrientation(Diag::DiagY, Flip::None ), //  ZYX ---
	AxisOrientation(Diag::DiagZ, Flip::None ), //  YXZ ---
	AxisOrientation(Diag::DiagX, Flip::FlipX), //  XZY -++
	AxisOrientation(Diag::DiagY, Flip::FlipX), //  ZYX -++
	AxisOrientation(Diag::DiagZ, Flip::FlipX), //  YXZ -++
	AxisOrientation(Diag::DiagX, Flip::FlipY), //  XZY +-+
	AxisOrientation(Diag::DiagY, Flip::FlipY), //  ZYX +-+
	AxisOrientation(Diag::DiagZ, Flip::FlipY), //  YXZ +-+
	AxisOrientation(Diag::DiagX, Flip::FlipZ), //  XZY ++-
	AxisOrientation(Diag::DiagY, Flip::FlipZ), //  ZYX ++-
	AxisOrientation(Diag::DiagZ, Flip::FlipZ), //  YXZ ++-
};*/

struct VoxelOrientation
{
	private:
	unsigned char Value;
	public:

	Diag	GetDiag() const;
	Flip	GetFlip() const;

	void	SetDiag(Diag diag);
	void	SetFlip(Flip flip);

//	::Diag	Diag;
//	::Flip	Flip;

//	::Axis	Origin0;
//	::Axis	Target0;
//	::Axis	Origin1;
//	::Axis	Target1;



	void	make(Diag diag, Flip flip);
	void	make(Axis origin0, Axis target0, Axis origin1, Axis target1); // make this a static function ?

	~VoxelOrientation();
	VoxelOrientation();

	VoxelOrientation(const VoxelOrientation & other);
	VoxelOrientation & operator=(const VoxelOrientation & other);

	VectorF3	absolute(VectorF3 v) const;
	Axis		absolute(Axis axis) const;
	Axis		relative(Axis axis) const;
};

#endif