#include "AuxThread2.hpp"

#include "Voxel/ChunkManager.hpp"
#include "Voxel/Chunk.hpp"
#include "Voxel/AccessLockedChunk.hpp"



AuxThread2::~AuxThread2()
{ }
AuxThread2::AuxThread2(ChunkManager & manager)
	: AuxThreadBase()
	, Manager(manager)
	, GenerationNoise()
	, TimeGenerateFind("TimeGenerateFind")
	, TimeGenerate("TimeGenerate")
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

		AssignLockedChunk chunk2 = chunk.ToAssign();

		sw.Clear();
		sw.Start();
		(*chunk2).GenerateTerrain(GenerationNoise);
		(*chunk2).GenerateDecoration(GenerationNoise.Plane, GenerationNoise.Cave0);
		sw.Stop();
		TimeGenerate.DoTime.NewValue(sw.ElapsedTime());
		TimeGenerate.ThreadName = AuxThreadBase::ThreadName;
	}
}





void AuxThread2::Poke()
{
	ConditionVar.notify_all();
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
		Chunk * ptr = Manager.Chunks[Manager.relative(loop.Index())];
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
