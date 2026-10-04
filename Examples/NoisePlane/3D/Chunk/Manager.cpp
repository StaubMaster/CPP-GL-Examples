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



ChunkManager::ChunkManager(::AuxThreadCollection & aux_thread_collection)
	: AuxThreadCollection(aux_thread_collection)
	, Container(*this)
	, Graphics()
{ }



void ChunkManager::Draw()
{
	StopWatch sw_total;
	StopWatch sw_lock;

	sw_total.Start();

	Container.ChunksLock.AccessL(sw_lock, TimeDraw);
	Graphics.DrawWait.NewValue(sw_lock.ElapsedTime());

	Graphics.Draw();

	Container.ChunksLock.AccessU(sw_lock, TimeDraw);
	Graphics.DrawTotal.NewValue(sw_total.ElapsedTime());
}
