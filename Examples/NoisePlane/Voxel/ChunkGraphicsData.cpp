#include "ChunkGraphicsData.hpp"

#include "Chunk.hpp"

#include "VoxelGeometryPallet.hpp"
#include "VoxelPallet.hpp"
#include "Voxel.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/LoopU3.hpp"



void ChunkGraphicsData::Clear()
{
	DataF.Clear();
	DataU.Clear();
	ArrayF.Clear();
	ArrayU.Clear();
}
void ChunkGraphicsData::Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis)
{
	if (voxel.Pallet == nullptr) { return; }
	//const VoxelOrientation & orientation = voxel.Orientation;
	//unsigned int tex_idx = voxel.Template -> GraphicsTemplate;
	//unsigned int tex = voxel.Template -> TextureIndex;
	const VoxelAxisGraphicsData & axis_data = voxel.Pallet -> GeometryPallet -> AxisData(axis);

	for (unsigned int i = 0; i < axis_data.Data.Count(); i++)
	{
		VoxelGraphics::MainFaceF v = axis_data.Data[i];
		v.Vertexes[0].Pos = voxel.Orientation.absolute(v.Vertexes[0].Pos) + u;
		v.Vertexes[1].Pos = voxel.Orientation.absolute(v.Vertexes[1].Pos) + u;
		v.Vertexes[2].Pos = voxel.Orientation.absolute(v.Vertexes[2].Pos) + u;
		//v.Vertexes[0].Pos = v.Vertexes[0].Pos + u;
		//v.Vertexes[1].Pos = v.Vertexes[1].Pos + u;
		//v.Vertexes[2].Pos = v.Vertexes[2].Pos + u;
		v.Vertexes[0].Tex.Z = (voxel.Pallet -> Textures[(int)v.Vertexes[0].Tex.Z]).Index;
		v.Vertexes[1].Tex.Z = (voxel.Pallet -> Textures[(int)v.Vertexes[1].Tex.Z]).Index;
		v.Vertexes[2].Tex.Z = (voxel.Pallet -> Textures[(int)v.Vertexes[2].Tex.Z]).Index;
		DataF.Insert(v);
	}
}
void ChunkGraphicsData::Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis, const Chunk & chunk)
{
	if (chunk.Visible(u, voxel.Orientation.absolute(axis)))
	//if (chunk.Visible(u, axis))
	{
		Concatnate(u, voxel, axis);
	}
}
void ChunkGraphicsData::Make(const Chunk & chunk)
{
	Clear();
	if (!chunk.IsEmpty())
	{
		LoopU3 loop(VectorU3(), VectorU3(CHUNK_VALUES_PER_SIDE));
		for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			const Voxel & voxel = chunk[u];
			if (voxel.Pallet == nullptr) { continue; }
			Concatnate(u, voxel, AxisRel::Here, chunk);
			Concatnate(u, voxel, AxisRel::PrevX, chunk);
			Concatnate(u, voxel, AxisRel::PrevY, chunk);
			Concatnate(u, voxel, AxisRel::PrevZ, chunk);
			Concatnate(u, voxel, AxisRel::NextX, chunk);
			Concatnate(u, voxel, AxisRel::NextY, chunk);
			Concatnate(u, voxel, AxisRel::NextZ, chunk);
		}
	}
	Done();
}
void ChunkGraphicsData::Done()
{
	unsigned int limit = DataF.Count();
	ArrayF.Allocate(limit, limit);
	unsigned int count = 0;
	for (unsigned int b = 0; b < DataF.BlockCount(); b++)
	{
		const BlockList<1024, VoxelGraphics::MainFaceF>::Block & block = DataF.BlockIndex(b);
		for (unsigned int i = 0; i < 1024; i++)
		{
			if (count < limit)
			{
				ArrayF[count] = block.Data[i];
				count++;
			}
		}
	}
	DataF.Clear();
}
