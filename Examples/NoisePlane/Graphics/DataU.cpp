#include "DataU.hpp"
#include "ValueType/Vector/U3.hpp"
#include "Axis/Enums.hpp"



VoxelGraphicsDataU::Vertex::Vertex(const VectorU3 & pos, const VectorU3 & vert, const VectorU3 & tex, const AxisRel & axis, const VectorI3 & chunk)
	: Voxel(0)
	, Texture(tex.Z)
	, Chunk(chunk)
{
	Voxel |= (((pos.X) & 0xFF) << 0);
	Voxel |= (((pos.Y) & 0xFF) << 8);
	Voxel |= (((pos.Z) & 0xFF) << 16);
	Voxel |= (((tex.X) & 0b1) << 24);
	Voxel |= (((tex.Y) & 0b1) << 25);
	Voxel |= ((((unsigned char)axis) & 0b111) << 26);
	Voxel |= (((vert.X) & 0b1) << 29);
	Voxel |= (((vert.Y) & 0b1) << 30);
	Voxel |= (((vert.Z) & 0b1) << 31);
}



VoxelGraphicsDataU::Face::Face(const Vertex data[4])
	: Vertexes{
		data[0], data[1], data[2],
		data[2], data[1], data[3],
	}
{ }
