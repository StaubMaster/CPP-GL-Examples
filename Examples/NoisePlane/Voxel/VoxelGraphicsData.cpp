#include "VoxelGraphicsData.hpp"
#include "VoxelGraphicsTemplate.hpp"
#include "VoxelTemplate.hpp"
#include "Voxel.hpp"

#include "ValueType/VectorU3.hpp"



void ChunkGraphicsData::Clear()
{
	Data.Clear();
	Array.Clear();
}
void ChunkGraphicsData::Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis)
{
	if (voxel.Template == nullptr) { return; }
	//const VoxelOrientation & orientation = voxel.Orientation;
	unsigned int tex = voxel.Template -> TextureIndex;
	const VoxelAxisGraphicsData & axis_data = voxel.Template -> AxisData(axis);

	for (unsigned int i = 0; i < axis_data.Data.Count(); i++)
	{
		VoxelGraphics::MainTriangle v = axis_data.Data[i];
		//v.Corners[0].Pos = orientation.absolute(v.Corners[0].Pos) + u;
		//v.Corners[1].Pos = orientation.absolute(v.Corners[1].Pos) + u;
		//v.Corners[2].Pos = orientation.absolute(v.Corners[2].Pos) + u;
		v.Corners[0].Pos = v.Corners[0].Pos + u;
		v.Corners[1].Pos = v.Corners[1].Pos + u;
		v.Corners[2].Pos = v.Corners[2].Pos + u;
		v.Corners[0].Tex.Z = tex;
		v.Corners[1].Tex.Z = tex;
		v.Corners[2].Tex.Z = tex;
		Data.Insert(v);
	}
}
void ChunkGraphicsData::Done()
{
	unsigned int limit = Data.Count();
	Array.Allocate(limit, limit);
	unsigned int count = 0;
	for (unsigned int b = 0; b < Data.BlockCount(); b++)
	{
		const BlockList<1024, VoxelGraphics::MainTriangle>::Block & block = Data.BlockIndex(b);
		for (unsigned int i = 0; i < 1024; i++)
		{
			if (count < limit)
			{
				Array[count] = block.Data[i];
				count++;
			}
		}
	}
	Data.Clear();
}
