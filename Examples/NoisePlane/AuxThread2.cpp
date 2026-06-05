#include "AuxThread2.hpp"

#include "Voxel/ChunkManager.hpp"
#include "Voxel/Chunk.hpp"
#include "Voxel/AccessLockedChunk.hpp"
#include "Voxel/VoxelPallet.hpp"
#include "Voxel/Structure.hpp"



AuxThread2::~AuxThread2()
{ }
AuxThread2::AuxThread2(ChunkManager & manager)
	: AuxThreadBase()
	, Manager(manager)
	, GenerationNoise()
	, TimeGenerateFind("TimeGenerateFind")
	, TimeGenerate("TimeGenerate")
	, Loop2(VectorU2(), VectorU2(CHUNK_VALUES_PER_SIDE))
	, Loop3(VectorU3(), VectorU3(CHUNK_VALUES_PER_SIDE))
{
	GenerationNoise.Plane = Perlin2D::Random(VectorU2(8, 8));
	GenerationNoise.Cave0 = Perlin3D::Random(VectorU3(8, 8, 8));
	GenerationNoise.Cave1 = Perlin3D::Random(VectorU3(8, 8, 8));
	GenerationNoise.Cave2 = Perlin3D::Random(VectorU3(8, 8, 8));
}




void AuxThread2::Func()
{
	AuxThreadBase::ThreadName = "AuxThread2";
	while (!Term)
	{
		StopWatch sw;
		AccessLockedChunk chunk;

		std::unique_lock<std::mutex> lk(ConditionVarMutex);
		ConditionVar.wait(lk, [&]
		{
			if (Term) { return true; }
			if (DoIdle) { return false; }

			Manager.ChunksLock.AccessL(sw, TimeGenerateFind);
			chunk = Find();
			Manager.ChunksLock.AccessU(sw, TimeGenerateFind);

			if (chunk.Is())
			{
				IsIdle = false;
				return true;
			}
			IsIdle = true;
			return false;
		});

		if (Term) { return; }

		if (!chunk.Is()) { continue; }

		// Generate Voxels into seperate Voxel Array. then assign new Array into chunk
		AssignLockedChunk chunk2 = chunk.ToAssign();

		sw.Clear();
		sw.Start();
		GenerateTerrain(*chunk2, GenerationNoise);
		GenerateDecoration(*chunk2, GenerationNoise.Plane, GenerationNoise.Cave0);
		sw.Stop();
		TimeGenerate.DoTime.NewValue(sw.ElapsedTime());
		TimeGenerate.ThreadName = AuxThreadBase::ThreadName;
	}
}





AccessLockedChunk AuxThread2::Find()
{
	/* loop takes longer the longer it goes on
		save what chunks are fully complete
		then start at the end of those
		reset when Center changes ?
		what if a random chunk needs to be regenerated ?
		just reset and loop over everything again
		it would only need to loop once, which should be fine
	*/

	CenterIndexLoop3D	loop = FindLoop;
	FindCandidateCount = 0;
	for (loop.New(Manager.CareSize); !loop.Done(); loop.Continue())
	{
		Chunk * ptr = Manager.Chunks[Manager.relative(loop.Index() + Manager.Center)];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		ptr -> AccessL();
		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); FindLoop = loop; continue; }
		//if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

		return AccessLockedChunk(ptr);
	}
	return AccessLockedChunk();

//	AccessLockedChunk found;
	Chunk * found = nullptr;
	float dist;
	for (unsigned int i = 0; i < Manager.Chunks.Length(); i++)
	{
		Chunk * ptr = Manager.Chunks[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		//AccessLockedChunk chunk = ptr -> ToAccess();
		ptr -> AccessL();

		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); continue; }
		if (!Manager.CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

		VectorF3 rel = ref.Index - Manager.Center;
		float d = rel.length2();
		//if (!found.Is() || d < dist)
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> AccessU(); }
			found = ptr;
			dist = d;
		}
		else { ptr -> AccessU(); }
	}

	//return found;
	return AccessLockedChunk(found);
}





void AuxThread2::GenerateTerrain(Chunk & chunk, const ChunkGenerationNoise & noise)
{
	(void)noise;

	if (chunk.TerrainDone) { return; }

	chunk.MakeNull();

	ChunkData data(chunk);
//	TerrainFlat(data, 0, 0);
//	TerrainPillars(data);
	TerrainPlane(data, noise.Plane);
//	TerrainCaveNoodle(data, noise.Cave0, noise.Cave1);
//	TerrainCaveBlob(data, noise.Cave2);

	chunk.TerrainDone = true;
	Manager.AuxThread3.Poke();
}

AuxThread2::ChunkData::ChunkData(Chunk & chunk)
	: Index(chunk.Index)
	, Offset(chunk.Index * CHUNK_VALUES_PER_SIDE)
	, Voxels(chunk.Voxels)
{ }



/*
Condition: Y <= 0
Place: ConcreteCube
*/
void AuxThread2::TerrainFlat(ChunkData & data, int y_chunk, unsigned int y_voxel)
{
	// 0.016s

	const VoxelPallet & pallet_dirt = VoxelPalletMap::All["Dirt"];
	const VoxelPallet & pallet_grass = VoxelPalletMap::All["Grass"];

	(void)pallet_dirt;
	(void)pallet_grass;

	if (data.Index.Y == y_chunk)
	{
		for (VectorU3 u = Loop3.Min(); Loop3.Check(u).All(true); Loop3.Next(u))
		{
			if (u.Y == y_voxel)
			{
				data.Voxels[u] = pallet_grass.ToVoxel();
			}
			else if (u.Y < y_voxel)
			{
				data.Voxels[u] = pallet_dirt.ToVoxel();
			}
		}
	}
	else if (data.Index.Y < y_chunk)
	{
		for (VectorU3 u = Loop3.Min(); Loop3.Check(u).All(true); Loop3.Next(u))
		{
			data.Voxels[u] = pallet_dirt.ToVoxel();
		}
	}
}
/*
Condition: Y == 0 || Y == 31
Place: ConcreteCube

Condition: ((X == 7 || X == 24) && (Z == 7 || Z == 24))
Place: ConcreteCylinder
*/
void AuxThread2::TerrainPillars(ChunkData & data)
{
	//0123456789ABCDEF0123456789ABCDEF
	//       #                #       

	const VoxelPallet & pallet0 = VoxelPalletMap::All["ConcreteCube"];
	const VoxelPallet & pallet1 = VoxelPalletMap::All["ConcreteCylinder"];

	for (VectorU3 u = Loop3.Min(); Loop3.Check(u).All(true); Loop3.Next(u))
	{
		if (u.Y == 0 || u.Y == 31)
		{ data.Voxels[u] = pallet0.ToVoxel(); }
		//else if ((u.X == 7 || u.X == 24) && (u.Z == 7 || u.Z == 24))
		else if ((u.X == 1 || u.X == 30) && (u.Z == 1 || u.Z == 30))
		{ data.Voxels[u] = pallet1.ToVoxel(); }
	}
}

void AuxThread2::TerrainPlane(ChunkData & data, const Perlin2D & noise)
{
	const VoxelPallet & pallet_gray = VoxelPalletMap::All["Gray"];
	const VoxelPallet & pallet_dirt = VoxelPalletMap::All["Dirt"];
	const VoxelPallet & pallet_grass = VoxelPalletMap::All["Grass"];
	const VoxelPallet & pallet_water = VoxelPalletMap::All["Water"];

	(void)pallet_gray;
	(void)pallet_dirt;
	(void)pallet_grass;
	(void)pallet_water;

	for (VectorU2 u = Loop2.Min(); Loop2.Check(u).All(true); Loop2.Next(u))
	{
		VectorF2 abs_2(
			data.Offset.X + (int)u.X,
			data.Offset.Z + (int)u.Y
		);

		float val = 0.0f;

		//val += noise.Calculate(abs_2 / 128.0f) * 128;
		//val += noise.Calculate(abs_2 / 64.0f) * 64;
		//val += noise.Calculate(abs_2 / 32.0f) * 32;
		//val += noise.Calculate(abs_2 / 16.0f) * 16;
		//val += noise.Calculate(abs_2 / 8.0f) * 8;
		//val += noise.Calculate(abs_2 / 4.0f) * 4;
		//val += noise.Calculate(abs_2 / 2.0f) * 2;
		//val += noise.Calculate(abs_2 / 1.0f) * 1;

		//val += noise.Calculate(abs_2 / 1.0f) * 1.0f;
		//val += noise.Calculate(abs_2 / 2.0f) * 2.0f;
		//val += noise.Calculate(abs_2 / 4.0f) * 4.0f;
		//val += noise.Calculate(abs_2 / 8.0f) * 8.0f;
		//val += noise.Calculate(abs_2 / 16.0f) * 16.0f;
		//val += noise.Calculate(abs_2 / 32.0f) * 32.0f;
		//val += noise.Calculate(abs_2 / 64.0f) * 64.0f;
		//val += noise.Calculate(abs_2 / 128.0f) * 128.0f;
		//val += noise.Calculate(abs_2 / 256.0f) * 256.0f;

		val += noise.Calculate(abs_2 / 256.0f) * 64;

		for (unsigned int y = 0; y < CHUNK_VALUES_PER_SIDE; y++)
		{
			int abs_y = y + data.Offset.Y;
			unsigned int voxel_u = VectorU3::Convert(CHUNK_VALUES_PER_SIDE, VectorU3(u.X, y, u.Y));
			float diff = val - abs_y;
			if (diff < 0.0f)
			{
				data.Voxels[voxel_u] = Voxel();
				//if (abs_y < 0)
				//{ chunk.Voxels[voxel_u] = pallet_water.ToVoxel(); }
			}
			else if (diff < 1.0f)
			{
				{ data.Voxels[voxel_u] = pallet_grass.ToVoxel(); }
				//if (abs_y >= 0)
				//{ chunk.Voxels[voxel_u] = pallet_grass.ToVoxel(); }
				//else
				//{ chunk.Voxels[voxel_u] = pallet_dirt.ToVoxel(); }
			}
			else if (diff < 4.0f) { data.Voxels[voxel_u] = pallet_dirt.ToVoxel(); }
			else                  { data.Voxels[voxel_u] = pallet_gray.ToVoxel(); }
		}
	}
}

void AuxThread2::TerrainCaveNoodle(ChunkData & data, const Perlin3D & noise0, const Perlin3D & noise1)
{
	//if (Index.Y >= 0) { return; }
	//if (Index.Y != -1) { return; }
	if (data.Voxels.IsNull()) { return; }

	(void)noise0;
	(void)noise1;

	const VoxelPallet & pallet_r = VoxelPalletMap::All["DebugR"];
	const VoxelPallet & pallet_g = VoxelPalletMap::All["DebugG"];
	const VoxelPallet & pallet_b = VoxelPalletMap::All["DebugB"];

	(void)pallet_r;
	(void)pallet_g;
	(void)pallet_b;

	const float range = 4.0f;
	const float center = 0.0f;
	const float min = center - range;
	const float max = center + range;

	for (VectorU3 u = Loop3.Min(); Loop3.Check(u).All(true); Loop3.Next(u))
	{
		//if (u.Y != 31) { continue; }
		VectorF3 p(
			data.Offset.X + u.X,
			data.Offset.Y + u.Y,
			data.Offset.Z + u.Z
		);

		const float factor = 128.0f;
		float val0 = noise0.Calculate(p / factor) * factor;
		float val1 = noise1.Calculate(p / factor) * factor;

		//if (!(val0 > min && val0 < max)) { chunk.Voxels[u] = pallet_r.ToVoxel(); }
		//if (!(val1 > min && val1 < max)) { chunk.Voxels[u] = pallet_b.ToVoxel(); }
		if ((val0 > min && val0 < max) && (val1 > min && val1 < max)) { data.Voxels[u] = pallet_g.ToVoxel(); }
		//if ((val0 > min && val0 < max) && (val1 > min && val1 < max)) { chunk.Voxels[u] = Voxel(); }

		/*float val0 = 0.0f;
		//val += noise.Calculate(p / 32.0f) * 32.0f;
		//val += noise.Calculate(p / 64.0f) * 64.0f;
		//val += noise.Calculate(p / 128.0f) * 128.0f;
		val0 += noise0.Calculate(p / 256.0f) * 256.0f;
		//val += noise.Calculate(p / 512.0f) * 512.0f;

		if (val0 > min && val0 < max)
		{
			chunk.Voxels[u] = pallet_g.ToVoxel();
		}
		else if (val0 < 0.0f)
		{
			//Voxels[u] = pallet_b.ToVoxel();
		}
		else if (val0 > 0.0f)
		{
			//Voxels[u] = pallet_r.ToVoxel();
		}*/
	}
}

/*
Condition:
Place: OrientationCube
*/
void AuxThread2::TerrainGrid(ChunkData & data)
{
	for (VectorU3 u = Loop3.Min(); Loop3.Check(u).All(true); Loop3.Next(u))
	{
		VectorI3 voxel_idx = data.Offset + u;
		VectorF3 voxel_pos = voxel_idx;

		VectorF3 grid_pos = voxel_pos.round(256);
		VectorF3 grid_rel = voxel_pos - grid_pos + VectorF3(0.5f);

		if (grid_rel.length() < 4.0f) { data.Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
		if (VectorF3(grid_rel.X, grid_rel.Y, 0.0f).length() < 2.0f) { data.Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
		if (VectorF3(grid_rel.X, 0.0f, grid_rel.Z).length() < 2.0f) { data.Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
		if (VectorF3(0.0f, grid_rel.Y, grid_rel.Z).length() < 2.0f) { data.Voxels[u] = VoxelPalletMap::All["OrientationCube"].ToVoxel(); }
	}
}

void AuxThread2::TerrainCity(ChunkData & data)
{
	const VoxelPallet & pallet = VoxelPalletMap::All["ConcreteCube"];

	for (VectorU3 u = Loop3.Min(); Loop3.Check(u).All(true); Loop3.Next(u))
	{
		if ((u.X == 8 || u.X == 11 || u.X == 14 || u.X == 17 || u.X == 20 || u.X == 23) &&
			(u.Z == 8 || u.Z == 11 || u.Z == 14 || u.Z == 17 || u.Z == 20 || u.Z == 23))
		{
			data.Voxels[u] = pallet.ToVoxel();
		}
		if ((u.X >= 8 && u.X <= 23) && (u.Z >= 8 && u.Z <= 23) &&
			(u.Y == 4 || u.Y == 27))
		{
			data.Voxels[u] = pallet.ToVoxel();
		}
	}
}





void AuxThread2::GenerateDecoration(Chunk & chunk, const Perlin2D & noise2, const Perlin3D & noise3)
{
	(void)noise2;
	(void)noise3;

	if (chunk.DecorationsGenerated) { return; }

	DecorateTreesCenter(chunk);
	//DecorateTreesLines(chunk);
	//DecorateTrees(chunk, noise2);

	chunk.DecorationsGenerated = true;
	Manager.AuxThread3.Poke();
}

bool AuxThread2::FindMinYNull(Chunk & chunk, VectorU3 & udx) const
{
	udx.Y = CHUNK_VALUES_PER_SIDE - 1;
	if (!chunk.Voxels[udx].IsEmpty())
	{
		return false;
	}
	for (; udx.Y < CHUNK_VALUES_PER_SIDE; udx.Y--)
	{
		if (!chunk.Voxels[udx].IsEmpty())
		{
			udx.Y++;
			return true;
		}
	}
	udx.Y = CHUNK_VALUES_PER_SIDE;
	return false;
}
void AuxThread2::DecorateTreesCenter(Chunk & chunk)
{
	if ((chunk.Index.X % 2 == 0) && (chunk.Index.Z % 2 == 0))
	{
		StructureObject obj;
		obj.Structure = &Structure::Tree1;
		obj.Origin = VectorU3(15, 0, 15);
		if (FindMinYNull(chunk, obj.Origin))
		{ chunk.Decorations.Insert(obj); }
	}
}
void AuxThread2::DecorateTreesLines(Chunk & chunk)
{
	for (unsigned int z = 1; z < CHUNK_VALUES_PER_SIDE; z += 4)
	{
		for (unsigned int x = 1; x < CHUNK_VALUES_PER_SIDE; x += 4)
		{
			StructureObject obj;
			obj.Structure = &Structure::Tree0;
			obj.Origin = VectorU3(x, 0, z);
			if (FindMinYNull(chunk, obj.Origin))
			{ chunk.Decorations.Insert(obj); }
		}
		z += 4;
		for (unsigned int x = 3; x < CHUNK_VALUES_PER_SIDE; x += 4)
		{
			StructureObject obj;
			obj.Structure = &Structure::Tree0;
			obj.Origin = VectorU3(x, 0, z);
			if (FindMinYNull(chunk, obj.Origin))
			{ chunk.Decorations.Insert(obj); }
		}
	}
}
void AuxThread2::DecorateTrees(Chunk & chunk, const Perlin2D & noise)
{
//	if (Index.Z < 1) { return; }
//	if (Index.Y < 0) { return; }
//	if (Index.Y > 0) { return; }

	(void)noise;

	const VoxelPallet & pallet_r = VoxelPalletMap::All["DebugR"];
	const VoxelPallet & pallet_g = VoxelPalletMap::All["DebugG"];
	const VoxelPallet & pallet_b = VoxelPalletMap::All["DebugB"];

	(void)pallet_r;
	(void)pallet_g;
	(void)pallet_b;

	//const float range = 0.1f;
	//const float center = 0.0f;
	//const float min = center - range;
	//const float max = center + range;

	const VoxelPallet & pallet = VoxelPalletMap::All["OrientationCube"];
	(void)pallet;

	VectorI3 Offset = chunk.Index * (int)CHUNK_VALUES_PER_SIDE;
	for (unsigned int z = 0; z < CHUNK_VALUES_PER_SIDE; z++)
	{
		for (unsigned int x = 0; x < CHUNK_VALUES_PER_SIDE; x++)
		{
			//VectorF2 pos(Offset.X + (int)x, Offset.Z + (int)z);

			//float val = 0.0f;

			//val += noise.Calculate(pos / 001.0f) * 1.0f;
			//val += noise.Calculate(pos / 002.0f) * 1.0f;
			//val += noise.Calculate(pos / 003.0f) * 1.0f;
			//val += noise.Calculate(pos / 005.0f) * 1.0f;
			//val += noise.Calculate(pos / 007.0f) * 1.0f;
			//val += noise.Calculate(pos / 011.0f) * 1.0f;
			//val += noise.Calculate(pos / 013.0f) * 1.0f;

			//val += noise.Calculate(pos / 001.0f) * 1.0f;
			//val += noise.Calculate(pos / 002.0f) * 1.0f;
			//val += noise.Calculate(pos / 004.0f) * 1.0f;
			//val += noise.Calculate(pos / 008.0f) * 1.0f;
			//val += noise.Calculate(pos / 016.0f) * 1.0f;
			//val += noise.Calculate(pos / 032.0f) * 1.0f;
			//val += noise.Calculate(pos / 064.0f) * 1.0f;
			//val += noise.Calculate(pos / 128.0f) * 1.0f;
			//val += noise.Calculate(pos / 256.0f) * 1.0f;

			//if (val == 0.0f)
			//if (val > -0.01f && val < +0.01f)
			{
				//for (unsigned int y = 0; y < CHUNK_VALUES_PER_SIDE; y++)
				{
					//VectorU3 u(x, 0, z);

					//if (val >= min && val <= max) { chunk.Voxels[u] = pallet_g.ToVoxel(); }
					//else if (val > 0.0f) { chunk.Voxels[u] = pallet_r.ToVoxel(); }
					//else if (val < 0.0f) { chunk.Voxels[u] = pallet_b.ToVoxel(); }

					//Voxels[VectorU3(x, y, z)] = pallet.ToVoxel();
					/*if ((Offset.Y + y) < val)
					{
						chunk.Voxels[VectorU3(x, y, z)] = pallet.ToVoxel();
					}*/
				}
				/*VectorU3 origin = TopVoxel(*this, VectorU3(x, 0, z));
				if (origin.Y < CHUNK_VALUES_PER_SIDE)
				{
					chunk.Voxels[origin] = pallet.ToVoxel();
				}*/
				//StructureObject obj;
				//obj.Structure = &Structure::Tree0;
				//obj.Origin = TopVoxel(*this, VectorU3(x, 0, z));
				//Decorations.Insert(obj);
			}
		}
	}
}
