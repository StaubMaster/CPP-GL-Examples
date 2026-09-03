#include "3D/Voxel/Pallet/Geometry/Graphics/U/Data.hpp"
#include "ValueType/Vector/U3.hpp"
#include "Axis/Enums.hpp"



VoxelGraphicsDataU::Vertex::Vertex(const VectorU3 & udx, const VoxelGeometryDataU::Vertex & vert, const AxisRel & axis, const VectorI3 & chunk)
	: Voxel(0)
	, Texture(vert.Idx)
	, Chunk(chunk)
{
	Voxel |= (((udx.X) & 0xFF) << 0);
	Voxel |= (((udx.Y) & 0xFF) << 8);
	Voxel |= (((udx.Z) & 0xFF) << 16);
	Voxel |= (((vert.Tex.X) & 0b1) << 24);
	Voxel |= (((vert.Tex.Y) & 0b1) << 25);
	Voxel |= ((((unsigned char)axis) & 0b111) << 26);
	Voxel |= (((vert.Pos.X) & 0b1) << 29);
	Voxel |= (((vert.Pos.Y) & 0b1) << 30);
	Voxel |= (((vert.Pos.Z) & 0b1) << 31);
}



VoxelGraphicsDataU::Face::Face(const Vertex data[4])
	: Vertexes{
		data[0], data[1], data[2],
		data[2], data[1], data[3],
	}
{ }
