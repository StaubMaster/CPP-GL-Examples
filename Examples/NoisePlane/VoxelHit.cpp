#include "VoxelHit.hpp"

#include "Chunk.hpp"
#include "Chunk/Manager.hpp"

#include "General/ContainerLock/AccessTypeGuard.hpp"



#include <math.h>
#include "PolyHedra/Object.hpp"
//static PolyHedra * ViewRayPolyHedra;
//static PolyHedra * VoxelBoxPolyHedra;
//static PolyHedra * ChunkBoxPolyHedra;
/*static void ShowRay(RayF3 ray)
{
	if (ViewRayPolyHedra == nullptr) { return; }
	PolyHedraObject obj(ViewRayPolyHedra);
	obj.Trans().Position = ray.Pos;
	obj.Trans().Rotation = EulerAngle3D::PointToZ(ray.Dir);
}*/
/*static void ShowVoxel(VectorI3 idx)
{
	if (VoxelBoxPolyHedra == nullptr) { return; }
	PolyHedraObject obj(VoxelBoxPolyHedra);
	obj.Trans().Position = idx;
	obj.ShowWire();
}*/
/*static void ShowChunk(VectorI3 idx)
{
	PolyHedraObject obj(ChunkBoxPolyHedra);
	obj.Trans().Position = idx * CHUNK_VALUES_PER_SIDE;
	obj.ShowWire();
}*/

GridCast3D::Hit VoxelHit::Hit(const Chunk & chunk, RayF3 ray3D, float limit)
{
	//ShowRay(RayF3(ray3D.Pos, ray3D.Dir));
	BoxI3 box(VectorI3(-1), VectorI3(CHUNK_VALUES_PER_SIDE));
	GridCast3D::Data data(ray3D, limit, 1.0f);
	do
	{
		//ShowRay(data.Ray());
		//ShowVoxel(data.Index());
		VectorI3 idx = data.Index() - (chunk.Index * CHUNK_VALUES_PER_SIDE);
		if (box.IntersectVecInclusive(idx).All(false)) { return GridCast3D::Hit(); }
		if (box.IntersectVecExclusive(idx).All(true))
		{
			if (!chunk.Voxels[idx].IsEmpty())
			{
				return GridCast3D::Hit(data);
			}
		}
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}
GridCast3D::Hit VoxelHit::Hit(ChunkManager & manager, RayF3 ray3D, float limit)
{
	GridCast3D::Data data(ray3D, limit, CHUNK_VALUES_PER_SIDE);
	do
	{
		ContainerAccessTypeGuard<Chunk> chunk = manager.FindAccess(data.Index());
		if (!chunk.Is()) { return GridCast3D::Hit(); }
		if (!((*chunk).GenerationDone())) { return GridCast3D::Hit(); }
		if (((*chunk).IsEmpty())) { continue; }
		GridCast3D::Hit hit = VoxelHit::Hit(*chunk, data.Ray(), data.Limit());
		if (hit.cardinal != AxisRel::None) { return hit; }
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}



bool VoxelHit::Valid() const { return Side != AxisRel::None; }

VoxelHit::VoxelHit()
	: Side(AxisRel::None)
{ }
