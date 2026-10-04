#include "AuxThread/1.hpp"

#include "3D/Chunk.hpp"
#include "3D/Chunk/Container.hpp"

#include "Threading/ObjectTypeAccessUniqueGuard.hpp"
//#include "Threading/ObjectTypeAccessSharedGuard.hpp"

#include "Telemetry/StopWatch.hpp"



AuxThread1::AuxThread1(ChunkContainer & container)
	: IdleLoopThread("AuxThread1")
	, Container(container)
	, TimeFind("TimeMakeBufferFind")
	, TimeDo("TimeMakeBuffer")
{ }



bool AuxThread1::CheckFunc()
{
	StopWatch sw;

	Container.ChunksLock.AccessL(sw, TimeFind);
	ChunkFind = Find();
	Container.ChunksLock.AccessU(sw, TimeFind);

	return (ChunkFind.Is());
}
void AuxThread1::DoFunc()
{
	if (!ChunkFind.Is()) { return; }

	TimeDo.ThreadName = IdleLoopThread::ThreadName;

	StopWatch sw;

	sw.Start();
	AssignLockedChunk assign_chunk = ChunkFind.ToAssign();
	TimeDo.WaitTime.NewValue(sw.ElapsedTime());

	sw.Clear();
	(*assign_chunk).GraphicsData_Make();
	TimeDo.DoTime.NewValue(sw.ElapsedTime());

	Completed++;

	ChunkFind = AccessLockedChunk();
	QueueClean();
}



// uint Binary::FindCount(item)
// bool Binary::FindZero(item)
template <typename TypeItem> static bool FindZero(const Container::Binary<TypeItem> & container, const TypeItem & item)
{
	for (unsigned int i = 0; i < container.Count(); i++)
	{
		if (container[i] == item)
		{
			return false;
		}
	}
	return true;
}



unsigned int AuxThread1::QueueCount()
{
	QueueMutex.lock();
	unsigned int c = Queue.Count();
	QueueMutex.unlock();
	return c;
}
void AuxThread1::QueuePut(Chunk & chunk)
{
	if (!chunk.GraphicsData_Make_Can()) { return; }

	QueueMutex.lock();

	if (!FindZero(Queue, &chunk))
	{
		QueueMutex.unlock();
		return;
	}
	Queue.Insert(&chunk);

	QueueMutex.unlock();

	Poke();
}
/*void AuxThread1::QueuePut(Chunk * chunk)
{
	if (chunk != nullptr)
	{
		QueuePut(*chunk);
	}
}*/
void AuxThread1::QueueClean()
{
	QueueMutex.lock();
	for (unsigned int i = 0; i < Queue.Count(); i++)
	{
		Chunk * ptr = Queue[i];
		if (ptr == nullptr) { RemovedNull++; Queue.RemoveAt(i); i--; continue; }
		QueueMutex.unlock();

		const Chunk & ref = *ptr;
		if (!ref.GraphicsData_Make_Can()) { RemovedCheck++; QueueMutex.lock(); Queue.RemoveAt(i); i--; continue; }
	}
	QueueMutex.unlock();
}

AccessLockedChunk AuxThread1::Find()
{
	QueueMutex.lock();
	for (unsigned int i = 0; i < Queue.Count(); i++)
	{
		Chunk * ptr = Queue[i];
		if (ptr == nullptr) { continue; }
		QueueMutex.unlock();

		AccessLockedChunk chunk = ptr -> ToAccessMake();
		const Chunk & ref = *ptr;
		if (!ref.GraphicsData_Make_Can()) { continue; }

		return chunk;
	}
	QueueMutex.unlock();
	return AccessLockedChunk();
}
