#include "ValueType/_Include.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Voxel/GraphicsData.hpp"
#include "Voxel/GeometryPallet.hpp"
#include "Voxel/Pallet.hpp"



static void PolyHedraBoxEdges(PolyHedra & polyhedra, BoxF3 box)
{
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Min.Y, box.Min.Z))); // 000
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Min.Y, box.Min.Z))); // 001
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Max.Y, box.Min.Z))); // 010
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Max.Y, box.Min.Z))); // 011
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Min.Y, box.Max.Z))); // 100
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Min.Y, box.Max.Z))); // 101
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Min.X, box.Max.Y, box.Max.Z))); // 110
	polyhedra.Corners.Insert(PolyHedra::Corner(VectorF3(box.Max.X, box.Max.Y, box.Max.Z))); // 111

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b001));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b010, 0b011));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b100, 0b101));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b110, 0b111));

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b010));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b001, 0b011));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b100, 0b110));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b101, 0b111));

	polyhedra.Edges.Insert(PolyHedra::Edge(0b000, 0b100));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b001, 0b101));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b010, 0b110));
	polyhedra.Edges.Insert(PolyHedra::Edge(0b011, 0b111));
}

__attribute__((unused))
static void Toggle(bool & value) { value = !value; }

__attribute__((unused))
static void Toggle(::PolyHedra * & polyhedra, ::PolyHedra * other)
{
	if (polyhedra == nullptr)
	{
		polyhedra = other;
	}
	else
	{
		polyhedra = nullptr;
	}
}

#ifndef DISABLE_VIEW_TANGIBLE
static void DisplayBoxEntity(BoxEntity & box_entity)
{
	PolyHedraObject view_box_obj(box_entity.PolyHedra);
	view_box_obj.Trans().Position = box_entity.Pos;
	view_box_obj.ShowWire();
}
static void DisplayBoxEntityVoxels(unsigned int p, ::ChunkManager & manager, BoxEntity & box_entity, FrameTime frame_time)
{
//	unsigned int p = PolyHedraManager.FindPolyHedra(VoxelCube);

	BoxF3 box = box_entity.Box + box_entity.Pos;
	box.Consider(box_entity.Box.Min + box_entity.Pos + (box_entity.Vel * frame_time.Delta));
	box.Consider(box_entity.Box.Max + box_entity.Pos + (box_entity.Vel * frame_time.Delta));
	box = box - VectorF3(0.5f);

	LoopI3 loop(box.Min.round(), Bool3(false), box.Max.round(), Bool3(false));
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		ChunkVoxelIndex idx(i);
		AccessLockedChunk chunk = manager.FindAccess(idx.Chunk);
		if (!chunk.Is()) { continue; }
		const Voxel * voxel = (*chunk).FindVoxelOrNull(idx.Voxel);
		if (voxel != nullptr && !(voxel -> IsEmpty()))
		{
			PolyHedraObject voxel_obj(p);
			voxel_obj.Trans().Position = i;
			voxel_obj.ShowWire();
		}
	}
}
#endif
