#include "AuxThread/Collection.hpp"

#include "ContextNoisePlane.hpp"



bool AuxThreadCollection::AllDone() const
{
	for (unsigned int i = 0; i < Threads.Length(); i++)
	{
		if (!Threads[i] -> IsDone())
		{
			return false;
		}
	}
	return true;
}



AuxThreadCollection::AuxThreadCollection(ContextNoisePlane & context)
	: Threads(4)
	, AuxThread0(context)
	, AuxThread1(context.ChunkManager)
	, AuxThread2(context.ChunkManager)
	, AuxThread3(context.ChunkManager)
{
	Threads[0] = &AuxThread0;
	Threads[1] = &AuxThread1;
	Threads[2] = &AuxThread2;
	Threads[3] = &AuxThread3;
}



void AuxThreadCollection::Run()
{
	for (unsigned int i = 0; i < Threads.Length(); i++)
	{
		Threads[i] -> DoIdle = false;
		Threads[i] -> Poke();
	}
}
void AuxThreadCollection::Terminate()
{
	for (unsigned int i = 0; i < Threads.Length(); i++)
	{
		Threads[i] -> DoTerminate();
	}

	while (!AllDone())
	{
		for (unsigned int i = 0; i < Threads.Length(); i++)
		{
			if (!Threads[i] -> IsDone())
			{
				Threads[i] -> Poke();
			}
		}
	}

	for (unsigned int i = 0; i < Threads.Length(); i++)
	{
		Threads[i] -> Join();
	}
}
