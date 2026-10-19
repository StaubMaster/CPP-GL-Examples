#include "Threading/Thread/Loop/Idle.hpp"



IdleLoopThread::IdleLoopThread(const char * name)
	: BaseLoopThread(name)
{ }



void IdleLoopThread::LoopFunc()
{
	_Waiting = true;
	std::unique_lock<std::mutex> lk(ConditionVarMutex);
	ConditionVar.wait(lk, [&]
	{
		if (State == EState::Joining) { return true; }

		if (CheckFunc())
		{
			_Waiting = false;
			return true;
		}
		else
		{
			_Waiting = true;
			return false;
		}
	});

	if (State == EState::Joining) { return; }

	DoFunc();
}



bool IdleLoopThread::IsWaiting() const
{
	return _Waiting;
}
void IdleLoopThread::Poke()
{
	ConditionVar.notify_all();
}
