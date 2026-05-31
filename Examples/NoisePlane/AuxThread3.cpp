#include "AuxThread3.hpp"

#include "Voxel/ChunkManager.hpp"
#include "Voxel/Chunk.hpp"
#include "Voxel/AccessLockedChunk.hpp"



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

		if (Term) { return; }

		if (!chunk.Is()) { continue; }

		AssignLockedChunk chunk2 = chunk.ToAssign();

		sw.Clear();
		sw.Start();
		(*chunk2).AssambleDecoration();
		sw.Stop();
		TimeAssamble.DoTime.NewValue(sw.ElapsedTime());
		TimeAssamble.ThreadName = AuxThreadBase::ThreadName;
	}
}





void AuxThread3::Poke()
{
	ConditionVar.notify_all();
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
			found = ptr;
			dist = d;
		}
		else { ptr -> AccessU(); }
	}
	FindCandidateCount = candidate_count;

	//return found;
	return AccessLockedChunk(found);
}
