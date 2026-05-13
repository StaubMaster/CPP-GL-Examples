#include "ChunkGraphicsData.hpp"

#include "Chunk.hpp"
#include "ChunkManager.hpp"
#include "ChunkNeighbours.hpp"

#include "VoxelGeometryPallet.hpp"
#include "VoxelPallet.hpp"
#include "Voxel.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/LoopU3.hpp"

#include "Telemetry/StopWatch.hpp"
#include "Telemetry/ValueAverager.hpp"

#include <iostream>
#include <iomanip>



static ValueAverager<float> TimeAbsoluteAxis(0xFFFF);
static ValueAverager<float> TimeVisible(0xFFFF);
static ValueAverager<float> TimeAbsoluteVector(0xFFFF);
static ValueAverager<float> TimeInsert(0xFFFF);



void ChunkGraphicsData::Clear()
{
	DataF.Clear();
	DataU.Clear();
	ArrayF.Clear();
	ArrayU.Clear();
}
void ChunkGraphicsData::Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelPallet & pallet, const VoxelAxisGraphicsDataF & axis_data)
{
//	if (voxel.Pallet == 0xFFFF) { return; }
//	const VoxelPallet & pallet = VoxelPalletMap::All[voxel.Pallet];
//	const VoxelAxisGraphicsData & axis_data = pallet.GeometryPallet -> AxisData(axis);

	StopWatch sw;
	for (unsigned int i = 0; i < axis_data.Data.Count(); i++)
	{
		VoxelGraphics::MainFaceF v = axis_data.Data[i];

		sw.ReStart();
		v.Vertexes[0].Pos = orientation.absolute(v.Vertexes[0].Pos) + u;
		v.Vertexes[1].Pos = orientation.absolute(v.Vertexes[1].Pos) + u;
		v.Vertexes[2].Pos = orientation.absolute(v.Vertexes[2].Pos) + u;
		sw.Stop();
		TimeAbsoluteVector.NewValue(sw.ElapsedTime());

		v.Vertexes[0].Tex.Z = (pallet.Textures[(int)v.Vertexes[0].Tex.Z]).Index;
		v.Vertexes[1].Tex.Z = (pallet.Textures[(int)v.Vertexes[1].Tex.Z]).Index;
		v.Vertexes[2].Tex.Z = (pallet.Textures[(int)v.Vertexes[2].Tex.Z]).Index;

		sw.ReStart();
		DataF.Insert(v);
		sw.Stop();
		TimeInsert.NewValue(sw.ElapsedTime());
	}
}
void ChunkGraphicsData::Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelPallet & pallet, AxisRel axis, const ChunkNeighbour & neighbours)
{
	StopWatch sw;

	sw.Start();
	AxisRel a = orientation.absolute(axis);
	sw.Stop();
	TimeAbsoluteAxis.NewValue(sw.ElapsedTime());

	sw.ReStart();
	bool visible = neighbours.Visible(u, a);
	sw.Stop();
	TimeVisible.NewValue(sw.ElapsedTime());

	if (visible)
	{
		const VoxelAxisGraphicsDataF & axis_data = pallet.GeometryPallet -> AxisData(axis);
		Concatnate(u, orientation, pallet, axis_data);
	}
}
void ChunkGraphicsData::Make(const Chunk & chunk)
{
	Clear();
	if (!chunk.IsEmpty())
	{
		TimeVisible.Clear();
		TimeAbsoluteAxis.Clear();
		TimeInsert.Clear();
		TimeAbsoluteVector.Clear();

		ChunkNeighbour neighbours = chunk.Manager.FindNeighbours(chunk);

		StopWatch sw;
		sw.Start();
		LoopU3 loop(VectorU3(), VectorU3(CHUNK_VALUES_PER_SIDE));
		for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
		{
			const Voxel & voxel = chunk[u];
			if (voxel.Pallet == 0xFFFF) { continue; }
			const VoxelOrientation & orientation = voxel.Orientation;
			const VoxelPallet & pallet = VoxelPalletMap::All[voxel.Pallet];

			Concatnate(u, orientation, pallet, AxisRel::Here, neighbours);
			Concatnate(u, orientation, pallet, AxisRel::PrevX, neighbours);
			Concatnate(u, orientation, pallet, AxisRel::PrevY, neighbours);
			Concatnate(u, orientation, pallet, AxisRel::PrevZ, neighbours);
			Concatnate(u, orientation, pallet, AxisRel::NextX, neighbours);
			Concatnate(u, orientation, pallet, AxisRel::NextY, neighbours);
			Concatnate(u, orientation, pallet, AxisRel::NextZ, neighbours);
		}
		sw.Stop();

		std::cout << "Total   : " << std::setw(5) << std::setfill(' ') << CHUNK_VALUES_PER_VOLM << ' ' << std::fixed << std::setprecision(12) << sw.ElapsedTime() << "s\n";
		std::cout << "Absolute: " << std::setw(5) << std::setfill(' ') << TimeAbsoluteAxis.Count << ' ' << std::fixed << std::setprecision(12) << TimeAbsoluteAxis.Sum() << "s\n";
		std::cout << "Visible : " << std::setw(5) << std::setfill(' ') << TimeVisible.Count << ' ' << std::fixed << std::setprecision(12) << TimeVisible.Sum() << "s\n";
		std::cout << "Absolute: " << std::setw(5) << std::setfill(' ') << TimeAbsoluteVector.Count << ' ' << std::fixed << std::setprecision(12) << TimeAbsoluteVector.Sum() << "s\n";
		std::cout << "Insert  : " << std::setw(5) << std::setfill(' ') << TimeInsert.Count << ' ' << std::fixed << std::setprecision(12) << TimeInsert.Sum() << "s\n";
		std::cout << '\n' << std::flush;
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
