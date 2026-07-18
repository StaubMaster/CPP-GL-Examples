#include "AuxThread3.hpp"

#include "Chunk.hpp"
#include "Chunk/Manager.hpp"

#include "Structure.hpp"

#include "ValueType/Loop/U3.hpp"

#include "ContainerLock/AssignTypeGuard.hpp"
#include "ContainerLock/AccessTypeGuard.hpp"



AuxThread3::~AuxThread3()
{ }
AuxThread3::AuxThread3(ChunkManager & manager)
	: AuxThreadBase()
	, Manager(manager)
	, TimeAssambleFind("TimeAssambleFind")
	, TimeAssamble("TimeAssamble")
{ }





void AuxThread3::Func()
{
	AuxThreadBase::ThreadName = "AuxThread3";
	while (!Term)
	{
		StopWatch sw;
		AccessLockedChunk chunk;

		std::unique_lock<std::mutex> lk(ConditionVarMutex);
		ConditionVar.wait(lk, [&]
		{
			if (Term) { return true; }
			if (DoIdle) { return false; }

			Manager.ChunksLock.AccessL(sw, TimeAssambleFind);
			//chunk = Manager.AssambleChunkFind();
			chunk = Find();
			Manager.ChunksLock.AccessU(sw, TimeAssambleFind);

			if (chunk.Is())
			{
				IsIdle = false;
				return true;
			}
			IsIdle = true;
			return false;
		});

		if (Term) { break; }

		if (!chunk.Is()) { continue; }

		AssignLockedChunk chunk2 = chunk.ToAssign();

		sw.Clear();
		sw.Start();
		//(*chunk2).AssambleDecoration();
		AssambleDecoration(*chunk2);
		sw.Stop();
		TimeAssamble.DoTime.NewValue(sw.ElapsedTime());
		TimeAssamble.ThreadName = AuxThreadBase::ThreadName;
	}
	Done = true;
}





AccessLockedChunk AuxThread3::Find()
{
	/*CenterIndexLoop3D	loop;
	for (loop.New(CareSize); !loop.Done(); loop.Continue())
	{
		Chunk * ptr = Chunks[relative(loop.Index())];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		ptr -> AccessL();
		if (ref.TerrainDone && ref.DecorationsGenerated) { ptr -> AccessU(); continue; }
		if (!CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }

		return AccessLockedChunk(ptr);
	}
	return AccessLockedChunk();*/

//	AccessLockedChunk found;
	Chunk * found = nullptr;
	float dist;
	unsigned int candidate_count = 0;
	for (unsigned int i = 0; i < Manager.Chunks.Length(); i++)
	{
		Chunk * ptr = Manager.Chunks[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		//AccessLockedChunk chunk = ptr -> ToAccess();
		ptr -> AccessL();

		if (!ref.TerrainDone || !ref.DecorationsGenerated || ref.DecorationsAssambled) { ptr -> AccessU(); continue; }
		if (!Manager.CareBox.IntersectVecInclusive(ref.Index).All(true)) { ptr -> AccessU(); continue; }
		if (!ref.Neighbours.CanAssamble()) { ptr -> AccessU(); continue; }

		candidate_count++;
		VectorF3 rel = ref.Index - Manager.Center;
		float d = rel.length2();
		//if (!found.Is() || d < dist)
		if (found == nullptr || d < dist)
		{
			if (found != nullptr) { found -> AccessU(); }
			//found = chunk;
			//std::cout << "Aux3 Find Can " << &(found -> Lock) << '\n' << std::flush;
			found = ptr;
			dist = d;
		}
		else { ptr -> AccessU(); }
	}
	FindCandidateCount = candidate_count;

	//return found;
	return Chunk::ToAccess(found);
}





void AuxThread3::AssambleDecoration(Chunk & chunk)
{
	if (chunk.DecorationsAssambled) { return; }

	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				const Chunk & other = *chunk.Neighbours.Cube[z][y][x];
				VectorI3 offset = VectorI3(x - 1, y - 1, z - 1) * CHUNK_VALUES_PER_SIDE;
				for (unsigned int i = 0; i < other.Decorations.Count(); i++)
				{
					AssambleDecoration(chunk, other.Decorations[i], offset);
				}
			}
		}
	}

	//Decorations.Clear();

	if (chunk.IsNullOrEmpty()) { chunk.MakeEmpty(); }

	chunk.DecorationsAssambled = true;

	chunk.Neighbours.BufferDataWant();
	Manager.AuxThread1.QueuePut(&chunk);
}
void AuxThread3::AssambleDecoration(Chunk & chunk, const StructureObject & obj, const VectorI3 & offset)
{
	if (obj.Structure == nullptr) { return; }

	const Structure & structure = *obj.Structure;
	LoopU3 loop(VectorU3(), structure.Voxels.Size());
	for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorU3 p = obj.Origin - structure.Center + u + offset;
		if ((p < chunk.Voxels.Size()).All(true))
		{
			if (!structure.Voxels[u].IsEmpty())
			{
				chunk.Voxels[p] = structure.Voxels[u];
			}
		}
	}
}
