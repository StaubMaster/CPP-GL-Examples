#include "Threading/Thread/Loop/Collection.hpp"
#include "Threading/Thread/Loop/Base.hpp"



bool ThreadLoopCollection::IsDone() const
{
	for (unsigned int i = 0; i < Threads.Count(); i++)
	{
		if (!Threads[i] -> JoinCan())
		{
			return false;
		}
	}
	return true;
}
void ThreadLoopCollection::DoTerminate()
{
	for (unsigned int i = 0; i < Threads.Count(); i++)
	{
		Threads[i] -> JoinRequest();
	}
}
void ThreadLoopCollection::Join()
{
	for (unsigned int i = 0; i < Threads.Count(); i++)
	{
		Threads[i] -> Join();
	}
}



void ThreadLoopCollection::Run()
{
	for (unsigned int i = 0; i < Threads.Count(); i++)
	{
		Threads[i] -> Run();
	}
}
void ThreadLoopCollection::Terminate()
{
	DoTerminate();

	while (!IsDone())
	{
		for (unsigned int i = 0; i < Threads.Count(); i++)
		{
			if (!Threads[i] -> JoinCan())
			{
				Threads[i] -> Poke();
			}
		}
	}

	Join();
}
