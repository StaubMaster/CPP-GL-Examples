#include "VoxelGraphicsData.hpp"
#include "VoxelGraphicsTemplate.hpp"
#include "VoxelTemplate.hpp"
#include "Voxel.hpp"

#include "ValueType/VectorU3.hpp"



void VoxelGraphicsData::Concatnate(VectorU3 u, const VoxelOrientation & orientation, unsigned int tex, const VoxelGraphicsData & other)
{
	for (unsigned int i = 0; i < other.Data.Count(); i++)
	{
		VoxelGraphics::MainTriangle v = other.Data[i];
		v.Corners[0].Pos = orientation.absolute(v.Corners[0].Pos) + u;
		v.Corners[1].Pos = orientation.absolute(v.Corners[1].Pos) + u;
		v.Corners[2].Pos = orientation.absolute(v.Corners[2].Pos) + u;
		v.Corners[0].Tex.Z = tex;
		v.Corners[1].Tex.Z = tex;
		v.Corners[2].Tex.Z = tex;
		Data.Insert(v);
	}
}
void VoxelGraphicsData::Concatnate(VectorU3 u, const VoxelOrientation & orientation, unsigned int tex, const VoxelGraphicsTemplate & graphics_temp, AxisRel axis)
{
	Concatnate(u, orientation, tex, graphics_temp.AxisData(axis));
}
void VoxelGraphicsData::Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelTemplate & temp, AxisRel axis)
{
	Concatnate(u, orientation, temp.TextureIndex, temp.GraphicsTemplate, axis);
}
void VoxelGraphicsData::Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis)
{
	if (voxel.Template != nullptr)
	{
		Concatnate(u, voxel.Orientation, *voxel.Template, axis);
	}
}
