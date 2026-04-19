#ifndef  VoxelORIENTATION_HPP
# define VoxelORIENTATION_HPP

enum class Axis : unsigned char // 3 Bits
{
	Here  = 0b000,
	PrevX = 0b001,
	PrevY = 0b010,
	PrevZ = 0b100,
	NextX = 0b110,
	NextY = 0b101,
	NextZ = 0b011,
	None  = 0b111,
};

/*
2 * 3 * 4
2 * 2 * 6
Diagonal: 3 (2 flips + 1)
Spin: 10 (3 per Axis + 1)
Flip Axis: 4 (1 per axis + 1)
Flip Diag: 4 (1 per Diag + 1)
*/

/* where is each Axis ?

XYZ
XZY
ZXY
YXZ
YZX
ZYX

+++
--+
-+-
+--

+X+Y+Z	+X-Y-Z	-X+Y-Z	-X-Y+Z
+X+Z+Y	+X-Z-Y	-X+Z-Y	-X-Z+Y
+Z+X+Y	+Z-X-Y	-Z+X-Y	-Z-X+Y
+Y+X+Z	+Y-X-Z	-Y+X-Z	-Y-X+Z
+Y+Z+X	+Y-Z-X	-Y+Z-X	-Y-Z+X
+Z+Y+X	+Z-Y-X	-Z+Y-X	-Z-Y+X

SpinDiag rotates Axis
SpinDiagPrev(XYZ) = ZXY

FlipDiag swaps 2 Axis
FlipDiagX(XYZ) = XZY

FlipAxis "Invertes" 2 Axis
FlipAxisX(+++) = +--
*/

/*
+X+Y+Z	None
+Z+X+Y	SpinDiagPrev
+Y+Z+X	SpinDiagNext
+X+Z+Y	FlipDiagX
+Z+Y+X	FlipDiagY
+Y+X+Z	FlipDiagZ

FlipAxisX
+X-Y-Z
+X-Z-Y
+Z-X-Y
+Y-X-Z
+Y-Z-X
+Z-Y-X

FlipAxisY
-X+Y-Z
-X+Z-Y
-Z+X-Y
-Y+X-Z
-Y+Z-X
-Z+Y-X

FlipAxisZ
-X-Y+Z
-X-Z+Y
-Z-X+Y
-Y-X+Z
-Y-Z+X
-Z-Y+X
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

enum class Flip : unsigned char
{
	None,
	FlipX,
	FlipY,
	FlipZ,
}; // 4 Values ; 2 Bits

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

struct VoxelOrientation
{
	private:
	unsigned char Value;
	public:

	::Diag	GetDiag() const;
	::Flip	GetFlip() const;

	void	SetDiag(::Diag diag);
	void	SetFlip(::Flip flip);

//	::Diag	Diag;
//	::Flip	Flip;

//	::Axis	Origin0;
//	::Axis	Target0;
//	::Axis	Origin1;
//	::Axis	Target1;

	void	make(::Diag diag, ::Flip flip);
	void	make(::Axis origin0, ::Axis target0, ::Axis origin1, ::Axis target1);
/*
	make a struct to store Axises
	just loop what Orientations does
	then Loop over those to find Orientations for Axises
*/

	~VoxelOrientation();
	VoxelOrientation();

	VoxelOrientation(const VoxelOrientation & other);
	VoxelOrientation & operator=(const VoxelOrientation & other);

	VectorF3	orient(VectorF3 v) const;
};

#endif