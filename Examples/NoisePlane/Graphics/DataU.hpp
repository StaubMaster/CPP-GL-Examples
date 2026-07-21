#ifndef  VOXEL_GRAPHICS_DATA_U_HPP
# define VOXEL_GRAPHICS_DATA_U_HPP

# include "ValueType/Vector/I3.hpp"

struct VectorU3;
enum class AxisRel : unsigned char;

namespace VoxelGraphicsDataU
{
/* Vertex
	|------||------||------||------| 32 Bits in 4 Bytes
	[--PX--][--PY--][--PZ--]TTNNNVVV
							XY   XYZ
	8Bit [0;255] Voxel Position X (only {5} [0;31] are used)
	8Bit [0;255] Voxel Position Y (only {5} [0;31] are used)
	8Bit [0;255] Voxel Position Z (only {5} [0;31] are used)
	1Bit [0;1] Texture X
	1Bit [0;1] Texture Y
	3Bit [0;7] Normal
	1Bit [0;1] Voxel Vertex Position X
	1Bit [0;1] Voxel Vertex Position Y
	1Bit [0;1] Voxel Vertex Position Z
	4Byte (uint) Texture Z
	4Byte (sint) Chunk Position X
	4Byte (sint) Chunk Position Y
	4Byte (sint) Chunk Position Z
*/
struct Vertex
{
	unsigned int	Voxel = 0;
	unsigned int	Texture = 0;
	VectorI3		Chunk;

	~Vertex() = default;
	Vertex() = default;
	Vertex(const Vertex & other) = default;
	Vertex & operator=(const Vertex & other) = default;

	// take GeometryDataU Vertex ?
	Vertex(const VectorU3 & pos, const VectorU3 & vert, const VectorU3 & tex, const AxisRel & axis, const VectorI3 & chunk);
};
struct Face
{
	Vertex	Vertexes[6];

	~Face() = default;
	Face() = default;
	Face(const Face & other) = default;
	Face & operator=(const Face & other) = default;

	Face(const Vertex data[4]);
};
};

#endif