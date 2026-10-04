#include "AuxThread/3.hpp"
#include "AuxThread/Collection.hpp"

#include "3D/Chunk.hpp"
#include "3D/Chunk/Manager.hpp"

#include "3D/Structure.hpp"

#include "ValueType/Loop/U3.hpp"

#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
#include "Threading/ObjectTypeAssignUniqueGuard.hpp"

#include "Telemetry/StopWatch.hpp"



AuxThread3::AuxThread3(ChunkContainer & container)
	: IdleLoopThread("AuxThread3")
	, Container(container)
	, TimeAssambleFind("TimeAssambleFind")
	, TimeAssamble("TimeAssamble")
{ }



bool AuxThread3::CheckFunc()
{
	Container.ChunksLock.AccessL(sw, TimeAssambleFind);
	chunk = Find();
	Container.ChunksLock.AccessU(sw, TimeAssambleFind);

	return (chunk.Is());
}
void AuxThread3::DoFunc()
{
	if (!chunk.Is()) { return; }

	AssignLockedChunk chunk2 = chunk.ToAssign();

	sw.Clear();
	sw.Start();
	AssambleDecoration(*chunk2);
	sw.Stop();
	TimeAssamble.DoTime.NewValue(sw.ElapsedTime());
	TimeAssamble.ThreadName = IdleLoopThread::ThreadName;

	chunk = AccessLockedChunk();
}





AccessLockedChunk AuxThread3::Find()
{
	AccessLockedChunk found;
	float dist;
	FindCandidateCount = 0;
	for (unsigned int i = 0; i < Container.Chunks.Length(); i++)
	{
		Chunk * ptr = Container.Chunks[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;

		AccessLockedChunk guard = ptr -> ToAccessMake();

		if (!ref.TerrainDone || !ref.DecorationsGenerated || ref.DecorationsAssambled) { continue; }
		if (!Container.AbsoluteCheckCareBox(ref.Index)) { continue; }
		if (!ref.Neighbours.CanAssamble()) { continue; }

		FindCandidateCount++;
		VectorF3 rel = Container.AbsoluteToCentered(ref.Index).ToF();
		float d = rel.length2();
		if (found.Object == nullptr || d < dist)
		{
			found.Transfer(guard);
			dist = d;
		}
	}

	return found;
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

	chunk.Neighbours.BufferDataWantAll();
}
void AuxThread3::AssambleDecoration(Chunk & chunk, const StructureObject & obj, const VectorI3 & offset)
{
	if (obj.Structure == nullptr) { return; }

	const Structure & structure = *obj.Structure;
	LoopU3 loop(VectorU3(), structure.Voxels.Size());
	for (VectorU3 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorU3 p = ((obj.Origin - structure.Center + u).ToI() + offset).ToU();
		if ((p < chunk.Voxels.Size()).All(true))
		{
			if (!structure.Voxels[u].IsEmpty())
			{
				chunk.Voxels[p] = structure.Voxels[u];
			}
		}
	}
}
