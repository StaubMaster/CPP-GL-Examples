#include "VoxelHit.hpp"

#include "3D/Chunk.hpp"
//#include "3D/Chunk/Manager.hpp"
#include "3D/Chunk/Container.hpp"

#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
//#include "Threading/ObjectTypeAccessSharedGuard.hpp"

#include "Axis/3D/Enums.hpp"



#include <math.h>
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
		if (box.ContainsInclusive(idx).All(false)) { return GridCast3D::Hit(); }
		if (box.ContainsExclusive(idx).All(true))
		{
			if (!chunk[idx.ToU()].IsEmpty())
			{
				return GridCast3D::Hit(data);
			}
		}
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}
GridCast3D::Hit VoxelHit::Hit(ChunkContainer & container, RayF3 ray3D, float limit)
{
	GridCast3D::Data data(ray3D, limit, CHUNK_VALUES_PER_SIDE);
	do
	{
		AccessLockedChunk chunk = container.FindAbsoluteAccess(data.Index());
		if (!chunk.Is()) { return GridCast3D::Hit(); }
		if (!((*chunk).IsDone())) { return GridCast3D::Hit(); }
		if (((*chunk).IsEmpty())) { continue; }
		GridCast3D::Hit hit = VoxelHit::Hit(*chunk, data.Ray(), data.Limit());
		if (hit.cardinal != Axis3D::Rel::None) { return hit; }
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}



bool VoxelHit::Valid() const { return Side != Axis3D::Rel::None; }
