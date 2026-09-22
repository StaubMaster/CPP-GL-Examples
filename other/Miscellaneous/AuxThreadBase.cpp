#include "AuxThreadBase.hpp"



thread_local const char * AuxThreadBase::ThreadName = "ThreadName";



AuxThreadBase::AuxThreadBase(const char * name)
	: Thread(&AuxThreadBase::ThreadFunc, this)
	, Name(name)
{ }



void AuxThreadBase::Poke()
{
	ConditionVar.notify_all();
}
void AuxThreadBase::Join()
{
	Thread.join();
}



void AuxThreadBase::ThreadFunc()
{
	ThreadName = Name;
	while (!DoTerminate)
	{
		IsWaiting = true;
		std::unique_lock<std::mutex> lk(ConditionVarMutex);
		ConditionVar.wait(lk, [&]
		{
			if (DoTerminate) { return true; }
			if (DoIdle) { return false; }

			if (CheckFunc())
			{
				IsWaiting = false;
				return true;
			}
			else
			{
				IsWaiting = true;
				return false;
			}
		});

		if (DoTerminate) { break; }

		DoFunc();
	}
	IsDone = true;
}
