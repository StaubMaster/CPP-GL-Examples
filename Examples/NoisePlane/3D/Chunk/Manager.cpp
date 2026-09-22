#include "3D/Chunk/Manager.hpp"

#include "Telemetry/StopWatch.hpp"



WaitDoTime ChunkManager::TimeInsert("TimeInsert");
WaitDoTime ChunkManager::TimeInsertNew("TimeInsertNew");
WaitDoTime ChunkManager::TimeInsertPut("TimeInsertPut");
WaitDoTime ChunkManager::TimeRemove("TimeRemove");
WaitDoTime ChunkManager::TimeUpdate("TimeUpdate");
WaitDoTime ChunkManager::TimeUpdateInsert("TimeUpdateInsert");
WaitDoTime ChunkManager::TimeUpdateRemove("TimeUpdateRemove");
WaitDoTime ChunkManager::TimeGraphicsCreate("TimeGraphicsCreate");
WaitDoTime ChunkManager::TimeGraphicsDelete("TimeGraphicsDelete");
WaitDoTime ChunkManager::TimeDraw("TimeDraw");



ChunkManager::ChunkManager()
	: Container(*this)
	, AuxThread1(*this)
	, AuxThread2(*this)
	, AuxThread3(*this)
	, Graphics()
{ }



//#include <iostream>
void ChunkManager::Draw()
{
	StopWatch sw_total;

	StopWatch sw_lock;
	sw_total.Start();
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	Container.ChunksLock.AccessL(sw_lock, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	Graphics.DrawWait.NewValue(sw_lock.ElapsedTime());

	Graphics.Draw();

	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	Container.ChunksLock.AccessU(sw_lock, TimeDraw);
	//std::cout << ThreadInfo::ThreadName << " Draw " << __LINE__ << '\n';
	Graphics.DrawTotal.NewValue(sw_total.ElapsedTime());
}
