#include "IdleLoopThread.hpp"



thread_local const char * IdleLoopThread::ThreadName = "ThreadName";



IdleLoopThread::IdleLoopThread(const char * name)
	: Thread(&IdleLoopThread::ThreadFunc, this)
	, Name(name)
{ }



void IdleLoopThread::ThreadFunc()
{
	ThreadName = Name;
	while (!_Terminate)
	{
		_Waiting = true;
		std::unique_lock<std::mutex> lk(ConditionVarMutex);
		ConditionVar.wait(lk, [&]
		{
			if (_Terminate) { return true; }
			if (DoIdle) { return false; }

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

		if (_Terminate) { break; }

		DoFunc();
	}
	_Done = true;
}



void IdleLoopThread::Join()
{
	Thread.join();
}



void IdleLoopThread::DoTerminate()
{
	_Terminate = true;
}
bool IdleLoopThread::IsDone() const
{
	return _Done;
}



bool IdleLoopThread::IsWaiting() const
{
	return _Waiting;
}
void IdleLoopThread::Poke()
{
	ConditionVar.notify_all();
}
