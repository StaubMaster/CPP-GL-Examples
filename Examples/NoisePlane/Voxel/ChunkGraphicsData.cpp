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



static ValueAverager<float> TimeAbsoluteAxis(0xFFFFFF);
static ValueAverager<float> TimeVisible(0xFFFFFF);
static ValueAverager<float> TimeAbsoluteVector(0xFFFFFF);
static ValueAverager<float> TimeAssign(0xFFFFFF);
static ValueAverager<float> TimeTexture(0xFFFFFF);
static ValueAverager<float> TimeInsert(0xFFFFFF);
static ValueAverager<float> TimeLoop(0xFFFFFF);

static void TimeClear()
{
	TimeAbsoluteAxis.Clear();
	TimeVisible.Clear();
	TimeAbsoluteVector.Clear();
	TimeAssign.Clear();
	TimeTexture.Clear();
	TimeInsert.Clear();
	TimeLoop.Clear();
}
static void ShowNameCountValue(const char * name, unsigned int count, float value)
{
	std::cout << name << ' ';
	std::cout << std::setw(6) << std::setfill(' ') << count << ' ';
	std::cout << std::fixed << std::setprecision(12) << value << ' ';
	std::cout << (value / count) << '\n';
}
static void ShowNameCountValue(const char * name, const ValueAverager<float> & value)
{
	ShowNameCountValue(name, value.Count, value.Sum());
}
static void ShowTime(float total)
{
	return;
	ShowNameCountValue("Total   ", CHUNK_VALUES_PER_VOLM, total);
	ShowNameCountValue("Absolute", TimeAbsoluteAxis);
	ShowNameCountValue("Visible ", TimeVisible);
	ShowNameCountValue("Absolute", TimeAbsoluteVector);
	ShowNameCountValue("Texture ", TimeTexture);
	ShowNameCountValue("Insert  ", TimeInsert);
	ShowNameCountValue("Loop    ", TimeLoop);
	std::cout << '\n' << std::flush;
}



void ChunkGraphicsData::ClearU()
{
	DataU.Clear();
	ArrayU.Clear();
}
void ChunkGraphicsData::ClearF()
{
	DataF.Clear();
	ArrayF.Clear();
}



void ChunkGraphicsData::Concatnate(VectorU3 u, const VoxelOrientation & orientation, const VoxelPallet & pallet, AxisRel axis)
{
//	const VoxelAxisGraphicsDataF & axis_data_f = pallet.GeometryPallet -> AxisDataF(axis);

	StopWatch sw;
	/*for (unsigned int i = 0; i < axis_data_f.Data.Count(); i++)
	{
		sw.ReStart();
		VoxelGraphics::MainFaceF face = axis_data_f.Data[i];
		sw.Stop();
		TimeAssign.NewValue(sw.ElapsedTime());

		sw.ReStart();
		face.Vertexes[0].Pos = orientation.absolute(face.Vertexes[0].Pos) + u;
		face.Vertexes[1].Pos = orientation.absolute(face.Vertexes[1].Pos) + u;
		face.Vertexes[2].Pos = orientation.absolute(face.Vertexes[2].Pos) + u;
		sw.Stop();
		TimeAbsoluteVector.NewValue(sw.ElapsedTime());

		sw.ReStart();
		face.Vertexes[0].Tex.Z = (pallet.Textures[(int)face.Vertexes[0].Tex.Z]).Index;
		face.Vertexes[1].Tex.Z = (pallet.Textures[(int)face.Vertexes[1].Tex.Z]).Index;
		face.Vertexes[2].Tex.Z = (pallet.Textures[(int)face.Vertexes[2].Tex.Z]).Index;
		sw.Stop();
		TimeTexture.NewValue(sw.ElapsedTime());

		sw.ReStart();
		DataF.Insert(face);
		sw.Stop();
		TimeInsert.NewValue(sw.ElapsedTime());
	}*/

	if (axis != AxisRel::Here && axis != AxisRel::None)
	{
		VoxelAxisGraphicsDataU axis_data_u = pallet.GeometryPallet -> AxisDataU(axis);

		axis_data_u.Data[0].Pos = orientation.absolute(axis_data_u.Data[0].Pos) + u;
		axis_data_u.Data[1].Pos = orientation.absolute(axis_data_u.Data[1].Pos) + u;
		axis_data_u.Data[2].Pos = orientation.absolute(axis_data_u.Data[2].Pos) + u;
		axis_data_u.Data[3].Pos = orientation.absolute(axis_data_u.Data[3].Pos) + u;

		axis_data_u.Data[0].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[0].Tex.Z]).Index;
		axis_data_u.Data[1].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[1].Tex.Z]).Index;
		axis_data_u.Data[2].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[2].Tex.Z]).Index;
		axis_data_u.Data[3].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[3].Tex.Z]).Index;

		axis = orientation.absolute(axis);

		VoxelGraphics::MainFaceU face_u;
		face_u.Vertexes[0] = VoxelGraphics::MainDataU(axis_data_u.Data[0].Pos, axis_data_u.Data[0].Tex, axis);
		face_u.Vertexes[1] = VoxelGraphics::MainDataU(axis_data_u.Data[1].Pos, axis_data_u.Data[1].Tex, axis);
		face_u.Vertexes[2] = VoxelGraphics::MainDataU(axis_data_u.Data[2].Pos, axis_data_u.Data[2].Tex, axis);
		face_u.Vertexes[3] = VoxelGraphics::MainDataU(axis_data_u.Data[2].Pos, axis_data_u.Data[2].Tex, axis);
		face_u.Vertexes[4] = VoxelGraphics::MainDataU(axis_data_u.Data[1].Pos, axis_data_u.Data[1].Tex, axis);
		face_u.Vertexes[5] = VoxelGraphics::MainDataU(axis_data_u.Data[3].Pos, axis_data_u.Data[3].Tex, axis);
		DataU.Insert(face_u);
	}

	(void)orientation;
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
		Concatnate(u, orientation, pallet, axis);
	}
}

void ChunkGraphicsData::Make(const Chunk & chunk)
{
	ClearU();
	ClearF();
	if (!chunk.IsEmpty())
	{
		TimeClear();

		ChunkNeighbour neighbours = chunk.Manager.FindNeighbours(chunk);

		StopWatch sw;
		StopWatch sw_loop;
		sw.Start();
		LoopU3 loop(VectorU3(), VectorU3(CHUNK_VALUES_PER_SIDE));
		sw_loop.Start();
		for (VectorU3 udx = loop.Min(); loop.Check(udx).All(true); loop.Next(udx))
		{
			const Voxel & voxel = chunk[udx];
			if (voxel.IsEmpty())
			{
				sw_loop.Stop();
				TimeLoop.NewValue(sw_loop.ElapsedTime());
				sw_loop.ReStart();
				continue;
			}
			const VoxelOrientation & orientation = voxel.Orientation;
			const VoxelPallet & pallet = VoxelPalletMap::All[voxel.Pallet];
			sw_loop.Stop();
			TimeLoop.NewValue(sw_loop.ElapsedTime());

			Concatnate(udx, orientation, pallet, AxisRel::Here, neighbours);
			Concatnate(udx, orientation, pallet, AxisRel::PrevX, neighbours);
			Concatnate(udx, orientation, pallet, AxisRel::PrevY, neighbours);
			Concatnate(udx, orientation, pallet, AxisRel::PrevZ, neighbours);
			Concatnate(udx, orientation, pallet, AxisRel::NextX, neighbours);
			Concatnate(udx, orientation, pallet, AxisRel::NextY, neighbours);
			Concatnate(udx, orientation, pallet, AxisRel::NextZ, neighbours);

			sw_loop.ReStart();
		}
		sw.Stop();
		ShowTime(sw.ElapsedTime());
	}
//	std::cout << "Chunk Graphics Data Data: " << DataF.Count() << ' ' << DataU.Count() << '\n';
	DoneU();
	DoneF();
//	std::cout << "Chunk Graphics Data Array: " << ArrayF.Count() << ' ' << ArrayU.Count() << '\n';
}



void ChunkGraphicsData::DoneU()
{
	unsigned int limit = DataU.Count();
	ArrayU.Allocate(limit, limit);
	unsigned int count = 0;
	for (unsigned int b = 0; b < DataU.BlockCount(); b++)
	{
		const BlockList<1024, VoxelGraphics::MainFaceU>::Block & block = DataU.BlockIndex(b);
		for (unsigned int i = 0; i < 1024; i++)
		{
			if (count < limit)
			{
				ArrayU[count] = block.Data[i];
				count++;
			}
		}
	}
	DataU.Clear();
}
void ChunkGraphicsData::DoneF()
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
