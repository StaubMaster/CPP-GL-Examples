#include "AuxThread/Collection.hpp"

#include "ContextNoisePlane.hpp"



AuxThreadCollection::AuxThreadCollection(ContextNoisePlane & context)
	: ThreadLoopCollection()
	, AuxThread0(context)
	, AuxThread1(context.ChunkManager.Container)
	, AuxThread2(context.ChunkManager)
	, AuxThread3(context.ChunkManager.Container)
{
	Threads.Insert(&AuxThread0);
	Threads.Insert(&AuxThread1);
	Threads.Insert(&AuxThread2);
	Threads.Insert(&AuxThread3);
}
