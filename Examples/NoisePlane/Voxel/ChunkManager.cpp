#include "ChunkManager.hpp"
#include "Chunk.hpp"
#include "Voxel.hpp"

#include "ValueType/Bool3.hpp"
#include "ValueType/BoxI3.hpp"
#include "ValueType/LoopI3.hpp"

#include "ValueType/Ray3D.hpp"



ChunkManager::~ChunkManager() { }
ChunkManager::ChunkManager()
	: Shader()
	, Chunks()
	, ShouldGenerate(true)
	, GraphicsExist(false)
{ }



const Voxel * ChunkManager::FindVoxelOrNull(VectorI3 idx) const
{
	VectorI3 chunk_idx = (VectorF3(idx) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	VectorU3 voxel_idx = idx - (chunk_idx * CHUNK_VALUES_PER_SIDE);

	Chunk * chunk = FindChunkOrNull(chunk_idx);
	if (chunk == nullptr) { return nullptr; }
	if (chunk -> Data == nullptr) { return nullptr; }
	if (chunk -> ChunkType == ChunkType::Filled)
	{
		return &(*chunk)[voxel_idx];
	}
	if (chunk -> ChunkType == ChunkType::Empty)
	{
		return (*chunk).Data;
	}
	return nullptr;
}



#include <iostream>
#include "ValueType/_Show.hpp"
#include <math.h>
#include "PolyHedra/Object.hpp"
//static PolyHedra *	VoxelBoxPolyHedra;
//static PolyHedra *	ChunkBoxPolyHedra;
//static PolyHedra *	ViewRayPolyHedra;
/*static void ShowRay(Ray3D ray)
{
	PolyHedraObject obj(ViewRayPolyHedra);
	obj.Trans().Position = ray.Pos;
	obj.Trans().Rotation = EulerAngle3D::PointToZ(ray.Dir);
}*/
/*static void ShowVoxel(VectorI3 idx)
{
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
// put these into their own class / namespace
// call generic function ?
struct t_hit
{
	VectorF3	pos;
	VectorF3	rel;
	VectorI3	idx;
	float		dist;
	AxisDirection	cardinal;
};
struct t_ray
{
	VectorF3	pos;
	VectorF3	dir;
	VectorF3	side_len;
	VectorF3	side_sum;
	VectorI3	grid_dir;
	VectorI3	grid_idx;
	float		sum;
	bool		solid;
	AxisDirection	cardinal_side_X;
	AxisDirection	cardinal_side_Y;
	AxisDirection	cardinal_side_Z;
	AxisDirection	cardinal_dir;
};
static t_ray ray_init_cardinal(t_ray ray)
{
	if (ray.dir.X > 0)
	{
		ray.grid_dir.X = +1;
		ray.side_sum.X = ((ray.grid_idx.X + 1) - ray.pos.X) * ray.side_len.X;
		ray.cardinal_side_X = AxisDirection::PrevX;
	}
	else
	{
		ray.grid_dir.X = -1;
		ray.side_sum.X = (ray.pos.X - ray.grid_idx.X) * ray.side_len.X;
		ray.cardinal_side_X = AxisDirection::NextX;
	}
	if (ray.dir.Y > 0)
	{
		ray.grid_dir.Y = +1;
		ray.side_sum.Y = ((ray.grid_idx.Y + 1) - ray.pos.Y) * ray.side_len.Y;
		ray.cardinal_side_Y = AxisDirection::PrevY;
	}
	else
	{
		ray.grid_dir.Y = -1;
		ray.side_sum.Y = (ray.pos.Y - ray.grid_idx.Y) * ray.side_len.Y;
		ray.cardinal_side_Y = AxisDirection::NextY;
	}
	if (ray.dir.Z > 0)
	{
		ray.grid_dir.Z = +1;
		ray.side_sum.Z = ((ray.grid_idx.Z + 1) - ray.pos.Z) * ray.side_len.Z;
		ray.cardinal_side_Z = AxisDirection::PrevZ;
	}
	else
	{
		ray.grid_dir.Z = -1;
		ray.side_sum.Z = (ray.pos.Z - ray.grid_idx.Z) * ray.side_len.Z;
		ray.cardinal_side_Z = AxisDirection::NextZ;
	}
	return (ray);
}
static t_ray ray_init(Ray3D ray3D)
{
	t_ray	ray;

	ray.pos = ray3D.Pos;
	ray.dir = ray3D.Dir;
	ray.grid_idx = ray3D.Pos.roundF();
	ray3D.Dir = !ray3D.Dir;

	ray.side_len.X = abs(1 / ray3D.Dir.X);
	ray.side_len.Y = abs(1 / ray3D.Dir.Y);
	ray.side_len.Z = abs(1 / ray3D.Dir.Z);

	ray.sum = 0;
	return (ray_init_cardinal(ray));
}
static t_hit return_hit(t_ray ray)
{
	t_hit	hit;

	hit.dist = ray.sum;
	hit.idx = ray.grid_idx;
	hit.pos = ray.pos + (ray.dir * hit.dist);
	hit.rel = hit.pos - hit.idx;
	hit.cardinal = ray.cardinal_dir;
	if (!ray.solid)
	{
		hit.cardinal = AxisDirection::None;
	}
	return (hit);
}
static t_hit hit_ray(const Chunk & chunk, Ray3D ray3D)
{
	t_ray	ray;

	//std::cout << "ray " << ray3D.Pos << ' ' << ray3D.Dir << '\n';
	ray = ray_init(ray3D);
	while (ray.sum < 100)
	{
		//ShowRay(Ray3D(ray.pos + (ray.dir * ray.sum), ray.dir));
		//ShowVoxel(ray.grid_idx);

		VectorI3 idx = ray.grid_idx - (chunk.Index * CHUNK_VALUES_PER_SIDE);
		//std::cout << "voxel " << idx << '\n';
		if ((idx >= VectorI3(0)).Any(false)) { break; }
		if ((idx < VectorI3(CHUNK_VALUES_PER_SIDE)).Any(false)) { break; }

		ray.solid = chunk[idx].IsSolid();
		if (ray.solid) { break; }

		if ((ray.side_sum.X < ray.side_sum.Y) && (ray.side_sum.X < ray.side_sum.Z))
		{
			ray.sum = ray.side_sum.X;
			ray.side_sum.X += ray.side_len.X;
			ray.grid_idx.X += ray.grid_dir.X;
			ray.cardinal_dir = ray.cardinal_side_X;
		}
		else if ((ray.side_sum.Y < ray.side_sum.Z) && (ray.side_sum.Y < ray.side_sum.X))
		{
			ray.sum = ray.side_sum.Y;
			ray.side_sum.Y += ray.side_len.Y;
			ray.grid_idx.Y += ray.grid_dir.Y;
			ray.cardinal_dir = ray.cardinal_side_Y;
		}
		else
		{
			ray.sum = ray.side_sum.Z;
			ray.side_sum.Z += ray.side_len.Z;
			ray.grid_idx.Z += ray.grid_dir.Z;
			ray.cardinal_dir = ray.cardinal_side_Z;
		}
	}
	return (return_hit(ray));
}
static t_hit hit_ray(const ChunkManager & manager, Ray3D ray3D)
{
	t_ray	ray;

	ray = ray_init(Ray3D(ray3D.Pos / (float)CHUNK_VALUES_PER_SIDE, ray3D.Dir / (float)CHUNK_VALUES_PER_SIDE));
	while (ray.sum < 100)
	{
		//std::cout << "chunk " << ray.grid_idx << '\n';

		//ShowChunk(ray.grid_idx);
		Chunk * chunk = manager.FindChunkOrNull(ray.grid_idx);
		if (chunk == nullptr) { break; }
		if (chunk -> Data == nullptr) { break; }
		if (chunk -> ChunkType == ChunkType::Filled)
		{
			t_hit hit = hit_ray(*chunk, Ray3D(ray3D.Pos + (ray3D.Dir * (ray.sum * CHUNK_VALUES_PER_SIDE + 0.01f)), ray3D.Dir));
			if (hit.cardinal != AxisDirection::None) { return hit; }
		}
		else if (chunk -> ChunkType != ChunkType::Empty) { break; }

		if ((ray.side_sum.X < ray.side_sum.Y) && (ray.side_sum.X < ray.side_sum.Z))
		{
			ray.sum = ray.side_sum.X;
			ray.side_sum.X += ray.side_len.X;
			ray.grid_idx.X += ray.grid_dir.X;
			ray.cardinal_dir = ray.cardinal_side_X;
		}
		else if ((ray.side_sum.Y < ray.side_sum.Z) && (ray.side_sum.Y < ray.side_sum.X))
		{
			ray.sum = ray.side_sum.Y;
			ray.side_sum.Y += ray.side_len.Y;
			ray.grid_idx.Y += ray.grid_dir.Y;
			ray.cardinal_dir = ray.cardinal_side_Y;
		}
		else
		{
			ray.sum = ray.side_sum.Z;
			ray.side_sum.Z += ray.side_len.Z;
			ray.grid_idx.Z += ray.grid_dir.Z;
			ray.cardinal_dir = ray.cardinal_side_Z;
		}
	}
	return (return_hit(ray));
}

bool ChunkManager::FindVoxelIndex(Ray3D ray, VectorI3 & idx, AxisDirection & side) const
{
//	::ViewRayPolyHedra = ViewRayPolyHedra;
//	::VoxelBoxPolyHedra = VoxelBoxPolyHedra;
//	::ChunkBoxPolyHedra = ChunkBoxPolyHedra;

	//std::cout << '\n';
	//ShowRay(ray);
	t_hit hit = hit_ray(*this, ray);

	if (hit.cardinal == AxisDirection::None) { return false; }
//	VectorF3 normal;
//	if (hit.cardinal == AxisDirection::NextX) { normal = VectorF3(+1, 0, 0); }
//	if (hit.cardinal == AxisDirection::PrevX) { normal = VectorF3(-1, 0, 0); }
//	if (hit.cardinal == AxisDirection::NextY) { normal = VectorF3(0, +1, 0); }
//	if (hit.cardinal == AxisDirection::PrevY) { normal = VectorF3(0, -1, 0); }
//	if (hit.cardinal == AxisDirection::NextZ) { normal = VectorF3(0, 0, +1); }
//	if (hit.cardinal == AxisDirection::PrevZ) { normal = VectorF3(0, 0, -1); }
	//ShowRay(Ray3D(hit.pos, normal));

	//std::cout << "hit " << hit.idx << '\n';
	idx = hit.idx;
	side = hit.cardinal;
	return true;

	Chunk * chunk = nullptr;
	hit_ray(*chunk, ray);
	hit_ray(*this, ray);
	return false;
}



bool ChunkManager::ClearVoxel(VectorI3 idx, Voxel & vox)
{
	VectorI3 chunk_idx = (VectorF3(idx) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	VectorU3 voxel_idx = idx - (chunk_idx * CHUNK_VALUES_PER_SIDE);

	Chunk * chunk = FindChunkOrNull(chunk_idx);
	if (chunk == nullptr) { return false; }
	if (chunk -> Data == nullptr) { return false; }
	if (chunk -> ChunkType == ChunkType::Filled)
	{
		Voxel & voxel = (*chunk)[voxel_idx];
		if (voxel.Value == 0) { return false; }

		vox = voxel;
		voxel.Value = 0;
		(*chunk).Neighbours.UpdateBufferMain(); // only update effected
		return true;
	}
	if (chunk -> ChunkType == ChunkType::Empty)
	{
		return false;
	}
	return false;
}
bool ChunkManager::PlaneVoxel(VectorI3 idx, Voxel & vox)
{
	VectorI3 chunk_idx = (VectorF3(idx) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	VectorU3 voxel_idx = idx - (chunk_idx * CHUNK_VALUES_PER_SIDE);

	Chunk * chunk = FindChunkOrNull(chunk_idx);
	if (chunk == nullptr) { return false; }
	if (chunk -> Data == nullptr) { return false; }
	if (chunk -> ChunkType == ChunkType::Filled)
	{
		Voxel & voxel = (*chunk)[voxel_idx];
		if (voxel.Value != 0) { return false; }

		voxel = vox;
		vox.Value = 0;
		(*chunk).Neighbours.UpdateBufferMain(); // only update effected
		return true;
	}
	if (chunk -> ChunkType == ChunkType::Empty)
	{
		return false;
	}
	return false;
}



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
	if (!ShouldGenerate) { return; }

	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);

	LoopI3 loop(chunk_idx - (int)size, chunk_idx + (int)size);
	for (VectorI3 i = loop.Min(); loop.Check(i).All(true); loop.Next(i))
	{
		InsertChunk(i);
	}
}
void ChunkManager::InsertChunk(VectorI3 idx)
{
	if (!ShouldGenerate) { return; }

	Chunk * chunk = FindChunkOrNull(idx);
	if (chunk == nullptr)
	{
		chunk = new Chunk();
		chunk -> Index = idx;

		Chunks.Insert(chunk);
		NeighbourInsert(*chunk);

		chunk -> Buffer.Main.Pos.Change(0);
		chunk -> Buffer.Main.Tex.Change(1);
		chunk -> Buffer.Inst.Pos.Change(2);
		if (GraphicsExist)
		{
			chunk -> GraphicsCreate();
		}
	}
}

void ChunkManager::RemoveAround(VectorF3 pos, unsigned int size)
{
	VectorI3 chunk_idx(pos.roundF() / (float)CHUNK_VALUES_PER_SIDE);
	BoxI3 chunk_box(chunk_idx - (int)size, chunk_idx + (int)size);

	for (unsigned int i = 0; i < Chunks.Count(); i++)
	{
		if (Chunks[i] == nullptr) { continue; }
		Chunk & chunk = *Chunks[i];
		if (chunk_box.IntersectVecInclusive(chunk.Index).All(true)) { continue; }
		RemoveChunk(i);
	}
}
void ChunkManager::RemoveChunk(unsigned int idx)
{
	Chunk * chunk = Chunks[idx];
	Chunks.Remove(idx);
	chunk -> GraphicsDelete();
	delete chunk;
}

void ChunkManager::GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3, VectorF3 pos, unsigned int size, unsigned int count)
{
	if (!ShouldGenerate) { return; }

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
			if (chunk.ChunkType != ChunkType::UnGenerated) { continue; }
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
