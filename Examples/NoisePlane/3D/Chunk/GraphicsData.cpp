#include "GraphicsData.hpp"

#include "3D/Chunk.hpp"
#include "3D/Chunk/Manager.hpp"
#include "3D/Chunk/Neighbours.hpp"

#include "3D/Voxel.hpp"
#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"

#include "ValueType/Vector/U3.hpp"
#include "ValueType/Loop/U3.hpp"

#include "Telemetry/StopWatch.hpp"
#include "Telemetry/ValueAccumulator.hpp"

# include "Axis/3D/Enums.hpp"

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



void ChunkGraphicsData::CatU(const VoxelData & voxel_data, Axis3D::Rel axis)
{
	if (axis == Axis3D::Rel::Here || axis == Axis3D::Rel::None) { return; }
	CountData++;

	const VoxelGeometryDataU::Face & geom_face = voxel_data.Geometry.AxisDataU(voxel_data.Orientation.relative(axis));

	if (geom_face.Tex >= 6) { return; }

	VoxelGeometryDataU::Vertex vertexes[4];

	// this function stays the same per Voxel
	// get before CatU ?
	Axis3D::Orientation::SwizzlerU_Ref pos_func = voxel_data.Orientation.absolute_U_Func();
	vertexes[0].Pos = pos_func(geom_face.Vertexes[0].Pos);
	vertexes[1].Pos = pos_func(geom_face.Vertexes[1].Pos);
	vertexes[2].Pos = pos_func(geom_face.Vertexes[2].Pos);
	vertexes[3].Pos = pos_func(geom_face.Vertexes[3].Pos);

	unsigned int tex_idx;
	tex_idx = voxel_data.Pallet.Textures[geom_face.Tex].Index;

	const Axis2D::Orientation & tex_orientation = voxel_data.Pallet.TextureOrientations[geom_face.Tex];
	Axis2D::Orientation::SwizzlerU_Ref tex_func = tex_orientation.absolute_U_Func();
	vertexes[0].Tex = tex_func(geom_face.Vertexes[0].Tex);
	vertexes[1].Tex = tex_func(geom_face.Vertexes[1].Tex);
	vertexes[2].Tex = tex_func(geom_face.Vertexes[2].Tex);
	vertexes[3].Tex = tex_func(geom_face.Vertexes[3].Tex);

	VoxelGraphicsDataU::Vertex data[4];
	data[0] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, vertexes[0], axis, tex_idx, voxel_data.Chunk);
	data[1] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, vertexes[1], axis, tex_idx, voxel_data.Chunk);
	data[2] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, vertexes[2], axis, tex_idx, voxel_data.Chunk);
	data[3] = VoxelGraphicsDataU::Vertex(voxel_data.Undex, vertexes[3], axis, tex_idx, voxel_data.Chunk);

	BlockU.Insert(VoxelGraphicsDataU::Face(data));
}
void ChunkGraphicsData::CatF(const VoxelData & voxel_data, Axis3D::Rel axis)
{
	if (axis == Axis3D::Rel::None) { return; }

	const VoxelGeometryDataF::Axis geom_axis = voxel_data.Geometry.AxisDataF(voxel_data.Orientation.relative(axis));

	for (unsigned int i = 0; i < geom_axis.Data.Count(); i++)
	{
		const VoxelGeometryDataF::Face & geom_face = geom_axis.Data[i];

		if (geom_face.Tex >= 6) { continue; }

		VoxelGraphicsDataF::Face & graph_face = BlockF.MakeNext();

		Axis3D::Orientation::SwizzlerF_Ref pos_func = voxel_data.Orientation.absolute_F_Func();
		graph_face.Vertexes[0].Pos = pos_func(geom_face.Vertexes[0].Pos) + voxel_data.Offset;
		graph_face.Vertexes[1].Pos = pos_func(geom_face.Vertexes[1].Pos) + voxel_data.Offset;
		graph_face.Vertexes[2].Pos = pos_func(geom_face.Vertexes[2].Pos) + voxel_data.Offset;

		// Normal also needs to be Oriented
		graph_face.Vertexes[0].Normal = geom_face.Normal;
		graph_face.Vertexes[1].Normal = geom_face.Normal;
		graph_face.Vertexes[2].Normal = geom_face.Normal;

		unsigned int tex_idx;
		tex_idx = voxel_data.Pallet.Textures[geom_face.Tex].Index;

		const Axis2D::Orientation & tex_orientation = voxel_data.Pallet.TextureOrientations[geom_face.Tex];
		Axis2D::Orientation::SwizzlerF_Ref tex_func = tex_orientation.absolute_F_Func();

		VectorF2 tex;
		// use Texture Orientation

		tex = tex_func(geom_face.Vertexes[0].Tex);
		graph_face.Vertexes[0].Tex.X = tex.X;
		graph_face.Vertexes[0].Tex.Y = tex.Y;
		graph_face.Vertexes[0].Tex.Z = tex_idx;

		tex = tex_func(geom_face.Vertexes[1].Tex);
		graph_face.Vertexes[1].Tex.X = tex.X;
		graph_face.Vertexes[1].Tex.Y = tex.Y;
		graph_face.Vertexes[1].Tex.Z = tex_idx;

		tex = tex_func(geom_face.Vertexes[2].Tex);
		graph_face.Vertexes[2].Tex.X = tex.X;
		graph_face.Vertexes[2].Tex.Y = tex.Y;
		graph_face.Vertexes[2].Tex.Z = tex_idx;

		BlockF.Next();
	}
}
void ChunkGraphicsData::Cat(const VoxelData & voxel_data, Axis3D::Rel axis)
{
	switch (voxel_data.Orientation.relative(axis))
	{
		case Axis3D::Rel::PrevX: if (voxel_data.Geometry.UseF_PrevX) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case Axis3D::Rel::PrevY: if (voxel_data.Geometry.UseF_PrevY) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case Axis3D::Rel::PrevZ: if (voxel_data.Geometry.UseF_PrevZ) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case Axis3D::Rel::NextX: if (voxel_data.Geometry.UseF_NextX) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case Axis3D::Rel::NextY: if (voxel_data.Geometry.UseF_NextY) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
		case Axis3D::Rel::NextZ: if (voxel_data.Geometry.UseF_NextZ) { CatF(voxel_data, axis); } else { CatU(voxel_data, axis); } break;
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
		VectorF3 offset = (udx.ToI() + (chunk.Index * 32)).ToF();

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
			if (is_visible_prev_x) { Cat(voxel_data, Axis3D::Rel::PrevX); }
			if (is_visible_prev_y) { Cat(voxel_data, Axis3D::Rel::PrevY); }
			if (is_visible_prev_z) { Cat(voxel_data, Axis3D::Rel::PrevZ); }
			if (is_visible_next_x) { Cat(voxel_data, Axis3D::Rel::NextX); }
			if (is_visible_next_y) { Cat(voxel_data, Axis3D::Rel::NextY); }
			if (is_visible_next_z) { Cat(voxel_data, Axis3D::Rel::NextZ); }
			CatF(voxel_data, Axis3D::Rel::Here);
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
