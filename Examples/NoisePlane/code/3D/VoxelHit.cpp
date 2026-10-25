#include "VoxelHit.hpp"

#include "3D/Chunk.hpp"
#include "3D/Chunk/Container.hpp"

#include "Threading/Guard/Type/Access/Unique.hpp"
//#include "Threading/Guard/Type/Access/Shared.hpp"

#include "Axis/3D/Enums.hpp"

bool VoxelHit::Valid() const { return Side != Axis3D::Rel::None; }

VoxelHit VoxelHit::Hit(RayF3 ray, float limit, ChunkContainer & container)
{
	GridCast3D::Hit _hit = VoxelHit::HitGridCast(ray, limit, container);

	VoxelHit hit;
	if (_hit.cardinal == Axis3D::Rel::None) { return hit; }
	hit.Side = _hit.cardinal;
	hit.Position = _hit.pos;
	hit.Index = _hit.idx;
	return hit;
}

#include <math.h>

GridCast3D::Hit VoxelHit::HitGridCast(RayF3 ray, float limit, ChunkContainer & container)
{
	ObjectAccessUniqueGuard container_guard;
	container_guard.mMake(container.ChunksLock);
	GridCast3D::Data data(ray, limit, CHUNK_VALUES_PER_SIDE);
	do
	{
		AccessLockedChunk chunk = container.FindAbsoluteAccess(data.Index());
		if (!chunk.Is()) { return GridCast3D::Hit(); }
		if (!((*chunk).IsDone())) { return GridCast3D::Hit(); }
		if (((*chunk).IsEmpty())) { continue; }
		GridCast3D::Hit hit = VoxelHit::HitGridCast(data.Ray(), data.Limit(), *chunk);
		if (hit.cardinal != Axis3D::Rel::None) { return hit; }
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}
GridCast3D::Hit VoxelHit::HitGridCast(RayF3 ray, float limit, const Chunk & chunk)
{
	BoxI3 box(VectorI3(-1), VectorI3(CHUNK_VALUES_PER_SIDE));
	GridCast3D::Data data(ray, limit, 1.0f);
	do
	{
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
