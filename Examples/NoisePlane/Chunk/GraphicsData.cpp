#include "GraphicsData.hpp"

#include "Chunk.hpp"
#include "Manager.hpp"
#include "Neighbours.hpp"

#include "Voxel.hpp"
#include "Voxel/PalletGeometry.hpp"
#include "Voxel/Pallet.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/Loop/U3.hpp"

#include "Telemetry/StopWatch.hpp"
#include "Telemetry/ValueAccumulator.hpp"

#include <iostream>
#include <iomanip>



static ValueAccumulator<float> AverageTotal(1024);
static StopWatch TimeTotal;
static StopWatch TimeIteration;
static StopWatch TimeLoop;

static StopWatch TimeVoxelRetrieve;
static StopWatch TimeVoxelRetrieveData;

static ValueAccumulator<float> AverageVisible(1024);
static StopWatch TimeVisibleTotal;
static StopWatch TimeVisibleAbsolute;
static StopWatch TimeVisibleCheck;

static StopWatch TimeDataTotal;
static StopWatch TimeDataRetrieveData;
static StopWatch TimeDataAbsoluteVertex;
static StopWatch TimeDataAbsoluteAxis;
static StopWatch TimeDataTexture;
static StopWatch TimeDataCompress;
static StopWatch TimeDataAssign;

static StopWatch TimeInsert;

unsigned int	CountLoop;
unsigned int	CountVoxel;
unsigned int	CountVisible;
unsigned int	CountData;

static void TimeClear()
{
	TimeTotal.Clear();
	TimeIteration.Clear();
	TimeLoop.Clear();
	
	TimeVoxelRetrieve.Clear();
	TimeVoxelRetrieveData.Clear();

	TimeVisibleTotal.Clear();
	TimeVisibleAbsolute.Clear();
	TimeVisibleCheck.Clear();

	TimeDataTotal.Clear();
	TimeDataRetrieveData.Clear();
	TimeDataAbsoluteVertex.Clear();
	TimeDataAbsoluteAxis.Clear();
	TimeDataTexture.Clear();
	TimeDataCompress.Clear();
	TimeDataAssign.Clear();

	TimeInsert.Clear();

	CountLoop = 0;
	CountVoxel = 0;
	CountVisible = 0;
	CountData = 0;
}
static void ShowNameCountValue(const char * name, float value)
{
	std::cout << name << ' ';
	std::cout << std::fixed << std::setprecision(12) << value;
	std::cout << '\n';
}
static void ShowNameCountValue(const char * name, const StopWatch & sw)
{
	ShowNameCountValue(name, sw.ElapsedTime());
}
static void ShowTime()
{
	return;
	AverageTotal.NewValue(TimeTotal.ElapsedTime());
	std::cout << "Total: " << AverageTotal.Average() << '\n';
	ShowNameCountValue("Total             ", TimeTotal);
	ShowNameCountValue("Iteration         ", TimeIteration);

	std::cout << "Loop: " << CountLoop << '\n';
	ShowNameCountValue("Loop              ", TimeLoop);

	std::cout << "Voxel: " << CountVoxel << '\n';
	ShowNameCountValue("VoxelRetrieve     ", TimeVoxelRetrieve);
	ShowNameCountValue("VoxelRetrieveData ", TimeVoxelRetrieveData);

	AverageVisible.NewValue(TimeVisibleTotal.ElapsedTime());
	std::cout << "Visible: " << CountVisible << '\n';
	std::cout << "Visible: " << AverageVisible.Average() << '\n';
	ShowNameCountValue("VisibleTotal      ", TimeVisibleTotal);
	ShowNameCountValue("VisibleAbsolute   ", TimeVisibleAbsolute);
	ShowNameCountValue("VisibleCheck      ", TimeVisibleCheck);

	std::cout << "Data: " << CountData << '\n';
	ShowNameCountValue("DataTotal         ", TimeDataTotal);
	ShowNameCountValue("DataRetrieveData  ", TimeDataRetrieveData);
	ShowNameCountValue("DataAbsoluteVertex", TimeDataAbsoluteVertex);
	ShowNameCountValue("DataAbsoluteAxis  ", TimeDataAbsoluteAxis);
	ShowNameCountValue("DataTexture       ", TimeDataTexture);
	ShowNameCountValue("DataCompress      ", TimeDataCompress);
	ShowNameCountValue("DataAssign        ", TimeDataAssign);
	ShowNameCountValue("Insert            ", TimeInsert);

	std::cout << '\n' << std::flush;
}

//#define MEASURE_TIME

// 0.010

ChunkGraphicsData::VoxelData::VoxelData(const ::Voxel & voxel, const VectorI3 & chunk, const VectorU3 & undex, const VectorF3 & offset)
	: Voxel(voxel)
	, Orientation(voxel.Orientation)
	, Pallet(voxel.ToPallet())
	, Geometry(*Pallet.Geometry)
	, Chunk(chunk)
	, Undex(undex)
	, Offset(offset)
{ }



void ChunkGraphicsData::ClearU()
{
	ArrayU.Clear();
}
const Container::Array<VoxelGraphicsDataU::Face> & ChunkGraphicsData::DataU() const
{
	return ArrayU;
}

void ChunkGraphicsData::ClearF()
{
	ArrayF.Clear();
}
const Container::Array<VoxelGraphicsDataF::Face> & ChunkGraphicsData::DataF() const
{
	return ArrayF;
}



void ChunkGraphicsData::CatU(const VoxelData & voxel_data, AxisRel axis)
{
	if (axis == AxisRel::Here || axis == AxisRel::None) { return; }
	CountData++;

	#ifdef MEASURE_TIME
	TimeDataRetrieveData.Start();
	#endif

	VoxelGeometryDataU::Face geom_face = voxel_data.Geometry.AxisDataU(voxel_data.Orientation.relative(axis));

	AxisOrientation::SwizzlerU_Ref func = voxel_data.Orientation.absoluteU_Func();
	// this function stays the same per Voxel
	// get before CatU ?
	geom_face.Vertexes[0].Pos = func(geom_face.Vertexes[0].Pos);
	geom_face.Vertexes[1].Pos = func(geom_face.Vertexes[1].Pos);
	geom_face.Vertexes[2].Pos = func(geom_face.Vertexes[2].Pos);
	geom_face.Vertexes[3].Pos = func(geom_face.Vertexes[3].Pos);

	#ifdef MEASURE_TIME
	TimeDataRetrieveData.Stop();
	TimeDataAbsoluteVertex.Start();
	#endif

	#ifdef MEASURE_TIME
	TimeDataAbsoluteVertex.Stop();
	TimeDataAbsoluteAxis.Start();
	#endif

	#ifdef MEASURE_TIME
	TimeDataAbsoluteAxis.Stop();
	TimeDataTexture.Start();
	#endif

	geom_face.Vertexes[0].Idx = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[0].Idx).Index;
	geom_face.Vertexes[1].Idx = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[1].Idx).Index;
	geom_face.Vertexes[2].Idx = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[2].Idx).Index;
	geom_face.Vertexes[3].Idx = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[3].Idx).Index;

	#ifdef MEASURE_TIME
	TimeDataTexture.Stop();
	TimeDataCompress.Start();
	#endif

	VoxelGraphicsDataU::Vertex data[4];
	data[0] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, geom_face.Vertexes[0], axis, voxel_data.Chunk);
	data[1] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, geom_face.Vertexes[1], axis, voxel_data.Chunk);
	data[2] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, geom_face.Vertexes[2], axis, voxel_data.Chunk);
	data[3] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, geom_face.Vertexes[3], axis, voxel_data.Chunk);

	#ifdef MEASURE_TIME
	TimeDataCompress.Stop();
	TimeInsert.Start();
	#endif

	BlockU.Insert(VoxelGraphicsDataU::Face(data));

	#ifdef MEASURE_TIME
	TimeInsert.Stop();
	#endif
}
void ChunkGraphicsData::CatF(const VoxelData & voxel_data, AxisRel axis)
{
	if (axis == AxisRel::None) { return; }

	const VoxelGeometryDataF::Axis geom_axis = voxel_data.Geometry.AxisDataF(voxel_data.Orientation.relative(axis));

	for (unsigned int i = 0; i < geom_axis.Data.Count(); i++)
	{
		const VoxelGraphicsDataF::Face & geom_face = geom_axis.Data[i];

		VoxelGraphicsDataF::Face & graph_face = BlockF.MakeNext();

		graph_face.Vertexes[0].Pos = voxel_data.Orientation.absolute(geom_face.Vertexes[0].Pos) + voxel_data.Offset;
		graph_face.Vertexes[1].Pos = voxel_data.Orientation.absolute(geom_face.Vertexes[1].Pos) + voxel_data.Offset;
		graph_face.Vertexes[2].Pos = voxel_data.Orientation.absolute(geom_face.Vertexes[2].Pos) + voxel_data.Offset;

		graph_face.Vertexes[0].Normal = geom_face.Vertexes[0].Normal;
		graph_face.Vertexes[1].Normal = geom_face.Vertexes[1].Normal;
		graph_face.Vertexes[2].Normal = geom_face.Vertexes[2].Normal;

		graph_face.Vertexes[0].Tex = geom_face.Vertexes[0].Tex;
		graph_face.Vertexes[1].Tex = geom_face.Vertexes[1].Tex;
		graph_face.Vertexes[2].Tex = geom_face.Vertexes[2].Tex;

		graph_face.Vertexes[0].Tex.Z = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[0].Tex.Z).Index;
		graph_face.Vertexes[1].Tex.Z = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[1].Tex.Z).Index;
		graph_face.Vertexes[2].Tex.Z = voxel_data.Pallet.FindTextureFileIndex(geom_face.Vertexes[2].Tex.Z).Index;

		BlockF.Next();
	}
}
void ChunkGraphicsData::Cat(const VoxelData & voxel_data, AxisRel axis)
{
	switch (voxel_data.Orientation.relative(axis))
	{
		case AxisRel::PrevX: if (voxel_data.Geometry.UseF_PrevX) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case AxisRel::PrevY: if (voxel_data.Geometry.UseF_PrevY) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case AxisRel::PrevZ: if (voxel_data.Geometry.UseF_PrevZ) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case AxisRel::NextX: if (voxel_data.Geometry.UseF_NextX) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case AxisRel::NextY: if (voxel_data.Geometry.UseF_NextY) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case AxisRel::NextZ: if (voxel_data.Geometry.UseF_NextZ) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		default: break;
	}
}

void ChunkGraphicsData::Done()
{
	ArrayU = BlockU.ToArray();
	ArrayF = BlockF.ToArray();

	BlockU.Clear();
	BlockF.Clear();
}
void ChunkGraphicsData::Make(const Chunk & chunk, const Array3D<bool> & voxel_is_empty, const ChunkNeighbour & neighbours)
{
	//TimeTotal.Start();

	#ifdef MEASURE_TIME
	TimeLoop.Start();
	#endif

	for (unsigned int u = 0; u < CHUNK_VALUES_PER_VOLM; u++)
	{
		//CountLoop++;

		#ifdef MEASURE_TIME
		TimeLoop.TakeOver(TimeIteration);
		TimeVoxelRetrieve.Start();
		#endif

		if (voxel_is_empty.At(u))
		{
			#ifdef MEASURE_TIME
			TimeVoxelRetrieve.Stop();
			TimeIteration.TakeOver(TimeLoop);
			#endif

			continue;
		}
		//CountVoxel++;

		#ifdef MEASURE_TIME
		TimeVoxelRetrieve.TakeOver(TimeVoxelRetrieveData);
		#endif

		VectorU3 udx = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, u);
		VectorF3 offset = VectorI3(udx) + (chunk.Index * 32);

		#ifdef MEASURE_TIME
		TimeVoxelRetrieveData.TakeOver(TimeVisibleTotal);
		#endif

		bool is_visible_prev_x = neighbours.IsVisiblePrevX(voxel_is_empty, udx);
		bool is_visible_prev_y = neighbours.IsVisiblePrevY(voxel_is_empty, udx);
		bool is_visible_prev_z = neighbours.IsVisiblePrevZ(voxel_is_empty, udx);
		bool is_visible_next_x = neighbours.IsVisibleNextX(voxel_is_empty, udx);
		bool is_visible_next_y = neighbours.IsVisibleNextY(voxel_is_empty, udx);
		bool is_visible_next_z = neighbours.IsVisibleNextZ(voxel_is_empty, udx);

		#ifdef MEASURE_TIME
		TimeVisibleTotal.TakeOver(TimeDataTotal);
		#endif

		// this check only works if there is no Here
		/*if (is_visible_prev_x || is_visible_prev_y || is_visible_prev_z ||
			is_visible_next_x || is_visible_next_y || is_visible_next_z)*/
		{
			VoxelData voxel_data(chunk.Voxels.At(u), chunk.Index, udx, offset);
			if (is_visible_prev_x) { Cat(voxel_data, AxisRel::PrevX); }
			if (is_visible_prev_y) { Cat(voxel_data, AxisRel::PrevY); }
			if (is_visible_prev_z) { Cat(voxel_data, AxisRel::PrevZ); }
			if (is_visible_next_x) { Cat(voxel_data, AxisRel::NextX); }
			if (is_visible_next_y) { Cat(voxel_data, AxisRel::NextY); }
			if (is_visible_next_z) { Cat(voxel_data, AxisRel::NextZ); }
			CatF(voxel_data, AxisRel::Here);
		}

		#ifdef MEASURE_TIME
		TimeDataTotal.Stop();
		TimeIteration.TakeOver(TimeLoop);
		#endif
	}

	#ifdef MEASURE_TIME
	TimeLoop.Stop();
	#endif

	//TimeTotal.Stop();
}
void ChunkGraphicsData::Make(const Chunk & chunk, const ChunkNeighbour & neighbours)
{
	TimeClear();

	if (!chunk.IsEmpty())
	{
		Array3D<bool> voxel_is_empty (VectorU3(CHUNK_VALUES_PER_SIDE));
		for (unsigned int u = 0; u < CHUNK_VALUES_PER_VOLM; u++)
		{
			voxel_is_empty.At(u) = chunk.Voxels.At(u).IsEmpty();
		}
		Make(chunk, voxel_is_empty, neighbours);
	}
	// could unlock Chunk here

	ArrayLock.lock();
	Done();
	ArrayLock.unlock();

	ShowTime();
}
