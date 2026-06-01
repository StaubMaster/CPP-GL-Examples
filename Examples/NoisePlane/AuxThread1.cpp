#include "AuxThread1.hpp"

#include "Voxel/ChunkManager.hpp"
#include "Voxel/Chunk.hpp"
#include "Voxel/AccessLockedChunk.hpp"



AuxThread1::~AuxThread1()
{ }
AuxThread1::AuxThread1(ChunkManager & manager)
	: AuxThreadBase()
	, Manager(manager)
	, TimeMakeBufferFind("TimeMakeBufferFind")
	, TimeMakeBuffer("TimeMakeBuffer")
{ }





void AuxThread1::Func()
{
	AuxThreadBase::ThreadName = "AuxThread1";
	while (!Term)
	{
		StopWatch sw;
		AccessLockedChunk chunk;

		std::unique_lock<std::mutex> lk(ConditionVarMutex);
		ConditionVar.wait(lk, [&]
		{
			if (Term) { return true; }
			if (DoIdle) { return false; }

			Manager.ChunksLock.AccessL(sw, TimeMakeBufferFind);
			chunk = Find();
			Manager.ChunksLock.AccessU(sw, TimeMakeBufferFind);

			if (chunk.Is())
			{
				IsIdle = false;
				return true;
			}
			//if (Manager.MakeBufferQueue.Count() != 0)
			//{
			//	IsIdle = false;
			//	return true;
			//}
			IsIdle = true;
			return false;
		});

		if (Term) { return; }

		if (!chunk.Is()) { continue; }

		sw.Clear();
		sw.Start();
		((Chunk*)&(*chunk)) -> BufferUData_Make();
		sw.Stop();
		TimeMakeBuffer.DoTime.NewValue(sw.ElapsedTime());
		TimeMakeBuffer.ThreadName = AuxThreadBase::ThreadName;
	}
}



unsigned int AuxThread1::QueueCount()
{
	QueueMutex.lock();
	unsigned int c = Queue.Count();
	QueueMutex.unlock();
	return c;
}
void AuxThread1::QueuePut(Chunk * chunk)
{
	if (chunk == nullptr) { return; }

	QueueMutex.lock();

	for (unsigned int i = 0; i < Queue.Count(); i++)
	{
		if (Queue[i] == chunk)
		{
			QueueMutex.unlock();
			return;
		}
	}
	chunk -> BufferUData_Want = true;
	Queue.Insert(chunk);

	QueueMutex.unlock();

	Poke();
}
AccessLockedChunk AuxThread1::Find()
{
	QueueMutex.lock();
	for (unsigned int i = 0; i < Queue.Count(); i++)
	{
		Chunk * ptr = Queue[i];
		if (ptr == nullptr) { Queue.RemoveAt(i); i--; continue; }
		QueueMutex.unlock();
		const Chunk & ref = *ptr;

		AccessLockedChunk chunk = ptr -> ToAccess();
		//AccessLockedChunk chunk = ptr -> ToAccessTry();
		//if (!chunk.Is()) { continue; }

		if (!ref.BufferUData_Want) { QueueMutex.lock(); Queue.RemoveAt(i); i--; continue; }
		if (!ref.GenerationDone()) { QueueMutex.lock(); Queue.RemoveAt(i); i--; continue; }
		if (!ref.Neighbours.CanMakeBuffer()) { QueueMutex.lock(); Queue.RemoveAt(i); i--; continue; }

		return chunk;
	}
	QueueMutex.unlock();
	return AccessLockedChunk();
}
