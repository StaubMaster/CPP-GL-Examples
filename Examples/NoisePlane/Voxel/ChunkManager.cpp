#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"
#include "VoxelOrientation.hpp"
#include "VoxelIndex.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI3.hpp"

#include "ValueType/Ray3D.hpp"

#include "GridCast/GridCast3D.hpp"



ChunkManager::~ChunkManager() { }
ChunkManager::ChunkManager()
	: Shader()
	, Chunks()
	, GraphicsExist(false)
{ }



unsigned int ChunkManager::FindChunkUndex(Chunk * chunk) const
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == chunk)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
unsigned int ChunkManager::FindChunkUndex(VectorI3 idx) const
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (((*Chunks[i]).Index == idx).All(true))
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}
Chunk * ChunkManager::FindChunkOrNull(VectorI3 idx) const
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (((*Chunks[i]).Index == idx).All(true))
		{
			return Chunks[i];
		}
	}
	return nullptr;
}

VoxelIndex ChunkManager::FindVoxelIndex(VoxelIndex idx) const
{
	idx.ChunkMan = FindChunkUndex(idx.Chunk);
	return idx;
}
VoxelIndex ChunkManager::FindVoxelIndex(VectorI3 idx) const
{
	return FindVoxelIndex(VoxelIndex(idx));
}

const Voxel * ChunkManager::FindVoxelOrNull(VoxelIndex idx) const
{
	if (!idx.Valid()) { return nullptr; }
	Chunk * chunk = Chunks[idx.ChunkMan];
	if (chunk == nullptr) { return nullptr; }
	if (!(chunk -> Done())) { return nullptr; }
	if (chunk -> IsEmpty()) { return nullptr; }
	return &(*chunk)[idx.Voxel];
}
const Voxel * ChunkManager::FindVoxelOrNull(VectorI3 idx) const
{
	return FindVoxelOrNull(FindVoxelIndex(idx));
}



#include <iostream>
#include "ValueType/_Show.hpp"
#include <math.h>
#include "PolyHedra/Object.hpp"
static PolyHedra *	ViewRayPolyHedra;
static PolyHedra *	VoxelBoxPolyHedra;
//static PolyHedra *	ChunkBoxPolyHedra;
static void ShowRay(Ray3D ray)
{
	if (ViewRayPolyHedra == nullptr) { return; }
	PolyHedraObject obj(ViewRayPolyHedra);
	obj.Trans().Position = ray.Pos;
	obj.Trans().Rotation = EulerAngle3D::PointToZ(ray.Dir);
}
static void ShowVoxel(VectorI3 idx)
{
	if (VoxelBoxPolyHedra == nullptr) { return; }
	PolyHedraObject obj(VoxelBoxPolyHedra);
	obj.Trans().Position = idx;
	obj.ShowWire();
}
/*static void ShowChunk(VectorI3 idx)
{
	PolyHedraObject obj(ChunkBoxPolyHedra);
	obj.Trans().Position = idx * CHUNK_VALUES_PER_SIDE;
	obj.ShowWire();
}*/

static GridCast3D::Hit hit_ray(const Chunk & chunk, Ray3D ray3D, float limit)
{
	ShowRay(Ray3D(ray3D.Pos, ray3D.Dir));
	BoxI3 box(VectorI3(-1), VectorI3(CHUNK_VALUES_PER_SIDE));
	GridCast3D::Data data(ray3D, limit, 1.0f);
	do
	{
		ShowRay(data.Ray());
		ShowVoxel(data.Index());
		VectorI3 idx = data.Index() - (chunk.Index * CHUNK_VALUES_PER_SIDE);
		if (box.IntersectVecInclusive(idx).All(false)) { return GridCast3D::Hit(); }
		if (box.IntersectVecExclusive(idx).All(true))
		{
			if (chunk[idx].Template != nullptr) { return GridCast3D::Hit(data); }
		}
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}
static GridCast3D::Hit hit_ray(const ChunkManager & manager, Ray3D ray3D, float limit)
{
	GridCast3D::Data data(ray3D, limit, CHUNK_VALUES_PER_SIDE);
	do
	{
		Chunk * chunk = manager.FindChunkOrNull(data.Index());
		if (chunk == nullptr) { return GridCast3D::Hit(); }
		if (!(chunk -> Done())) { return GridCast3D::Hit(); }
		if (!(chunk -> IsEmpty()))
		{
			GridCast3D::Hit hit = hit_ray(*chunk, data.Ray(), data.Limit());
			if (hit.cardinal != AxisRel::None) { return hit; }
		}
	}
	while (data.Iterate());
	return GridCast3D::Hit();
}

bool VoxelHit::Valid() const { return Side != AxisRel::None; }
VoxelHit::VoxelHit()
	: Side(AxisRel::None)
{ }

VoxelHit ChunkManager::HitVoxel(Ray3D ray) const
{
	::ViewRayPolyHedra = ViewRayPolyHedra;
	::VoxelBoxPolyHedra = VoxelBoxPolyHedra;
//	::ChunkBoxPolyHedra = ChunkBoxPolyHedra;

	//ShowRay(ray);
	GridCast3D::Hit _hit = hit_ray(*this, ray, 10.0f);

	VoxelHit hit;
	if (_hit.cardinal == AxisRel::None) { return hit; }

	//hit.Position = ray.Pos + (ray.Dir * _hit.dist);
	hit.Position = _hit.pos;

	switch (_hit.cardinal)
	{
		case AxisRel::PrevX: hit.Normal = VectorF3(-1, 0, 0); break;
		case AxisRel::PrevY: hit.Normal = VectorF3(0, -1, 0); break;
		case AxisRel::PrevZ: hit.Normal = VectorF3(0, 0, -1); break;
		case AxisRel::NextX: hit.Normal = VectorF3(+1, 0, 0); break;
		case AxisRel::NextY: hit.Normal = VectorF3(0, +1, 0); break;
		case AxisRel::NextZ: hit.Normal = VectorF3(0, 0, +1); break;
		default: hit.Normal = VectorF3(0, 0, 0); break;
	}

	hit.Side = _hit.cardinal;
	hit.Index = _hit.idx;
	return hit;
}



bool ChunkManager::ClearVoxel(VoxelIndex idx, Voxel & vox)
{
	if (!idx.Valid()) { return false; }

	Chunk & chunk = *Chunks[idx.ChunkMan];
	if (!(chunk.Done())) { return false; }

	if (chunk.IsEmpty()) { return false; }

	Voxel & voxel = chunk[idx.Voxel];
	if (voxel.Template == nullptr) { return false; }

	vox = voxel;
	voxel.Template = nullptr;

	if (chunk.IsNullOrEmpty()) { chunk.MakeEmpty(); }

	chunk.Neighbours.UpdateBufferMain(); // only update effected
	return true;
}
bool ChunkManager::ClearVoxel(VectorI3 idx, Voxel & vox)
{
	return ClearVoxel(FindVoxelIndex(idx), vox);
}

bool ChunkManager::PlaceVoxel(VoxelIndex idx, Voxel & vox)
{
	if (!idx.Valid()) { return false; }

	Chunk & chunk = *Chunks[idx.ChunkMan];
	if (!(chunk.Done())) { return false; }

	if (chunk.IsEmpty()) { chunk.MakeNull(); }

	Voxel & voxel = chunk[idx.Voxel];
	if (voxel.Template != nullptr) { return false; }

	voxel = vox;
	vox.Template = nullptr;

	chunk.Neighbours.UpdateBufferMain(); // only update effected
	return true;
}
bool ChunkManager::PlaceVoxel(VectorI3 idx, Voxel & vox)
{
	return PlaceVoxel(FindVoxelIndex(idx), vox);
}



void ChunkManager::Clear()
{
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		Chunk & chunk = *Chunks[i];
		chunk.GraphicsDelete();
		delete Chunks[i];
	}
	Chunks.Clear();
}

void ChunkManager::InsertAround(VectorF3 pos, unsigned int size)
{
	if (DontInsert) { return; }

	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);

	LoopI3 loop(chunk_idx - (int)size, chunk_idx + (int)size);
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		InsertChunk(i);
	}
}
void ChunkManager::InsertChunk(VectorI3 idx)
{
	if (DontInsert) { return; }

	Chunk * chunk = FindChunkOrNull(idx);
	if (chunk == nullptr)
	{
		chunk = new Chunk(idx, GraphicsExist);
		//chunk -> Index = idx;

		Chunks.Insert(chunk);
		NeighbourInsert(*chunk);

		/*chunk -> Buffer.Main.Pos.Change(0);
		chunk -> Buffer.Main.Tex.Change(1);
		chunk -> Buffer.Inst.Pos.Change(2);
		if (GraphicsExist)
		{
			chunk -> GraphicsCreate();
		}*/
	}
}

void ChunkManager::RemoveAround(VectorF3 pos, unsigned int size)
{
	if (DontRemove) { return; }

	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];
		if (chunk_box.IntersectVecInclusive(chunk.Index).All(true)) { continue; }
		RemoveChunk(i);
		i--;
	}
}
void ChunkManager::RemoveChunk(unsigned int idx)
{
	if (DontRemove) { return; }

	Chunk * chunk = Chunks[idx];
	Chunks.Remove(idx); // this might be slow. set to null and then remove all at once. maybe make Containers delete all items that match something
	/*if (chunk != nullptr)
	{
		chunk -> GraphicsDelete();
	}*/
	delete chunk;
}

void ChunkManager::GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3, VectorF3 pos, unsigned int size, unsigned int count)
{
	if (DontGenerate) { return; }

	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	for (unsigned int c = 0; c < count; c++)
	{
		unsigned int idx = 0xFFFFFFFF;
		float dist;
		for (unsigned int i = 0; i < Chunks.Count(); i++)
		{
			if (Chunks[i] == nullptr) { continue; }
			Chunk & chunk = *Chunks[i];
			if (chunk.Done()) { continue; }
			if (!chunk_box.IntersectVecInclusive(chunk.Index).All(true)) { continue; }
			VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
			float d = rel.length2();
			if (idx == 0xFFFFFFFF || d < dist)
			{
				dist = d;
				idx = i;
			}
		}
		if (idx != 0xFFFFFFFF)
		{
			Chunk & chunk = *Chunks[idx];
			chunk.Generate(noise2, noise3);
			chunk.Neighbours.UpdateBufferMain();
		}
		else { break; } // return instead of break ?
	}
}

void ChunkManager::NeighbourInsert(Chunk & chunk)
{
	ChunkNeighbours & neighbours = chunk.Neighbours;
	neighbours.Here = &chunk;
	{
		neighbours.NextX = FindChunkOrNull(VectorI3(chunk.Index.X + 1, chunk.Index.Y, chunk.Index.Z));
		neighbours.NextY = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y + 1, chunk.Index.Z));
		neighbours.NextZ = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y, chunk.Index.Z + 1));
		neighbours.PrevX = FindChunkOrNull(VectorI3(chunk.Index.X - 1, chunk.Index.Y, chunk.Index.Z));
		neighbours.PrevY = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y - 1, chunk.Index.Z));
		neighbours.PrevZ = FindChunkOrNull(VectorI3(chunk.Index.X, chunk.Index.Y, chunk.Index.Z - 1));
	}
	neighbours.UpdateOthersHere();
}



void ChunkManager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Shader.Create();
	Texture.Create();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).GraphicsCreate();
	}

	GraphicsExist = true;
}
void ChunkManager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Shader.Delete();
	Texture.Delete();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).GraphicsDelete();
	}

	GraphicsExist = false;
}

void ChunkManager::GraphicsUpdateDataAround(VectorF3 pos, unsigned int count)
{
	if (!GraphicsExist) { return; }
	for (unsigned int c = 0; c < count; c++)
	{
		//std::cout << "Iteration: " << c << '|' << count << '\n';
		unsigned int idx = 0xFFFFFFFF;
		float dist;
		//std::cout << "Finding Candidate ...\n";
		for (unsigned int i = 0; i < Chunks.Count(); i++)
		{
			//std::cout << "chunks[" << i << "]: " << Chunks[i] << '\n';
			if (Chunks[i] == nullptr) { continue; }
			//std::cout << "line:" << __LINE__ << '\n';
			Chunk & chunk = *Chunks[i];
			//std::cout << "line:" << __LINE__ << '\n';
			if (chunk.MainBufferState != Chunk::BufferDataState::Needed) { continue; }
			//std::cout << "line:" << __LINE__ << '\n';
			VectorF3 rel = ((chunk.Index + VectorF3(0.5f)) * CHUNK_VALUES_PER_SIDE) - pos;
			//std::cout << "line:" << __LINE__ << '\n';
			float d = rel.length2();
			if (idx == 0xFFFFFFFF || d < dist)
			{
				dist = d;
				idx = i;
			}
			//std::cout << "line:" << __LINE__ << '\n';
		}
		if (idx != 0xFFFFFFFF)
		{
			//std::cout << "Found Candidate: " << idx << '\n';
			Chunk & chunk = *Chunks[idx];
			//std::cout << "Chunk: " << chunk.Index << '\n';
			//std::cout << "Chunk: " << (chunk.Data) << '\n';
			//std::cout << "Chunk: " << ((unsigned int)chunk.GenerationState) << '\n';
			//std::cout << "Chunk: " << ((unsigned int)chunk.MainBufferState) << '\n';
			chunk.GraphicsUpdateMainData();
		}
		else
		{
			//std::cout << "no Candidate found\n";
			break;
		}
	}
}

void ChunkManager::Draw()
{
	if (!GraphicsExist) { return; }

	Shader.Bind();
	Texture.Bind();
	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		(*Chunks[i]).Draw();
	}
}
