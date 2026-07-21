#include "GraphicsData.hpp"

#include "Chunk.hpp"
#include "Manager.hpp"
#include "Neighbours.hpp"

#include "Voxel.hpp"
#include "Voxel/GeometryPallet.hpp"
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

void ChunkGraphicsData::ClearU()
{
	ArrayU.Clear();
}
void ChunkGraphicsData::CatU(const VectorI3 & chunk, const VectorU3 & u, AxisRel axis, const AxisOrientation & orientation, const VoxelPallet & pallet)
{
	if (axis == AxisRel::Here || axis == AxisRel::None) { return; }
	CountData++;

	#ifdef MEASURE_TIME
	TimeDataRetrieveData.Start();
	#endif

	// axis needs to be rotated
	VoxelGeometryDataU::Face axis_data_u = pallet.GeometryPallet -> AxisDataU(axis);

	#ifdef MEASURE_TIME
	TimeDataRetrieveData.Stop();
	TimeDataAbsoluteVertex.Start();
	#endif

	//axis_data_u.Data[0].Pos = orientation.absolute(axis_data_u.Data[0].Pos) + u;
	//axis_data_u.Data[1].Pos = orientation.absolute(axis_data_u.Data[1].Pos) + u;
	//axis_data_u.Data[2].Pos = orientation.absolute(axis_data_u.Data[2].Pos) + u;
	//axis_data_u.Data[3].Pos = orientation.absolute(axis_data_u.Data[3].Pos) + u;

	//AxisOrientation::SwizzlerU_Ref func = orientation.absoluteU_Func();
	//axis_data_u.Data[0].Pos = func(axis_data_u.Data[0].Pos) + u;
	//axis_data_u.Data[1].Pos = func(axis_data_u.Data[1].Pos) + u;
	//axis_data_u.Data[2].Pos = func(axis_data_u.Data[2].Pos) + u;
	//axis_data_u.Data[3].Pos = func(axis_data_u.Data[3].Pos) + u;

	#ifdef MEASURE_TIME
	TimeDataAbsoluteVertex.Stop();
	TimeDataAbsoluteAxis.Start();
	#endif

	axis = orientation.absolute(axis);

	#ifdef MEASURE_TIME
	TimeDataAbsoluteAxis.Stop();
	TimeDataTexture.Start();
	#endif

	axis_data_u.Data[0].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[0].Tex.Z]).Index;
	axis_data_u.Data[1].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[1].Tex.Z]).Index;
	axis_data_u.Data[2].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[2].Tex.Z]).Index;
	axis_data_u.Data[3].Tex.Z = (pallet.Textures[(int)axis_data_u.Data[3].Tex.Z]).Index;

	#ifdef MEASURE_TIME
	TimeDataTexture.Stop();
	TimeDataCompress.Start();
	#endif

	VoxelGraphicsDataU::Vertex data[4];
	data[0] = VoxelGraphicsDataU::Vertex(u, axis_data_u.Data[0].Pos, axis_data_u.Data[0].Tex, axis, chunk);
	data[1] = VoxelGraphicsDataU::Vertex(u, axis_data_u.Data[1].Pos, axis_data_u.Data[1].Tex, axis, chunk);
	data[2] = VoxelGraphicsDataU::Vertex(u, axis_data_u.Data[2].Pos, axis_data_u.Data[2].Tex, axis, chunk);
	data[3] = VoxelGraphicsDataU::Vertex(u, axis_data_u.Data[3].Pos, axis_data_u.Data[3].Tex, axis, chunk);

	#ifdef MEASURE_TIME
	TimeDataCompress.Stop();
	TimeInsert.Start();
	#endif

	BlockU.Insert(VoxelGraphicsDataU::Face(data));

	#ifdef MEASURE_TIME
	TimeInsert.Stop();
	#endif
}
void ChunkGraphicsData::MakeU(const Chunk & chunk, const ChunkNeighbour & neighbours)
{
	Array3D<unsigned char> is_empty(VectorU3(CHUNK_VALUES_PER_SIDE));
	for (unsigned int u = 0; u < CHUNK_VALUES_PER_VOLM; u++)
	{
		is_empty.At(u) = chunk.Voxels.At(u).IsEmpty();
	}

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

		if (is_empty.At(u))
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

		#ifdef MEASURE_TIME
		TimeVoxelRetrieveData.TakeOver(TimeVisibleTotal);
		#endif

		bool is_visible_prev_x = neighbours.IsVisiblePrevX(is_empty, udx);
		bool is_visible_prev_y = neighbours.IsVisiblePrevY(is_empty, udx);
		bool is_visible_prev_z = neighbours.IsVisiblePrevZ(is_empty, udx);
		bool is_visible_next_x = neighbours.IsVisibleNextX(is_empty, udx);
		bool is_visible_next_y = neighbours.IsVisibleNextY(is_empty, udx);
		bool is_visible_next_z = neighbours.IsVisibleNextZ(is_empty, udx);

		#ifdef MEASURE_TIME
		TimeVisibleTotal.TakeOver(TimeDataTotal);
		#endif

		if (is_visible_prev_x || is_visible_prev_y || is_visible_prev_z ||
			is_visible_next_x || is_visible_next_y || is_visible_next_z)
		{
			const Voxel & voxel = chunk.Voxels.At(u);
			const AxisOrientation & orientation = voxel.Orientation;
			const VoxelPallet & pallet = VoxelPalletMap::All[voxel.Pallet];

			if (is_visible_prev_x) { CatU(chunk.Index, udx, AxisRel::PrevX, orientation, pallet); }
			if (is_visible_prev_y) { CatU(chunk.Index, udx, AxisRel::PrevY, orientation, pallet); }
			if (is_visible_prev_z) { CatU(chunk.Index, udx, AxisRel::PrevZ, orientation, pallet); }
			if (is_visible_next_x) { CatU(chunk.Index, udx, AxisRel::NextX, orientation, pallet); }
			if (is_visible_next_y) { CatU(chunk.Index, udx, AxisRel::NextY, orientation, pallet); }
			if (is_visible_next_z) { CatU(chunk.Index, udx, AxisRel::NextZ, orientation, pallet); }
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
void ChunkGraphicsData::DoneU()
{
	ArrayU = BlockU.ToArray();
	BlockU.Clear();
}
const Container::Array<VoxelGraphicsDataU::Face> & ChunkGraphicsData::GraphicsDataU() const { return ArrayU; }



void ChunkGraphicsData::ClearF()
{
	ArrayF.Clear();
}
void ChunkGraphicsData::DoneF()
{
	ArrayF = BlockF.ToArray();
	BlockF.Clear();
}
const Container::Array<VoxelGraphicsDataF::Face> & ChunkGraphicsData::GraphicsDataF() const { return ArrayF; }



void ChunkGraphicsData::Make(const Chunk & chunk, const ChunkNeighbour & neighbours)
{
	TimeClear();

	if (!chunk.IsEmpty())
	{
		MakeU(chunk, neighbours);
	}

	// could unlock Chunk here

	ArrayLock.lock();
	DoneU();
	ArrayLock.unlock();

	ShowTime();
}
