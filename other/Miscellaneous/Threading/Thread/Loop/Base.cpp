#include "Threading/Thread/Loop/Base.hpp"



thread_local const char * BaseLoopThread::ThreadName = "ThreadName";



void BaseLoopThread::DoTerminate()
{
	_Terminate = true;
}
bool BaseLoopThread::IsDone() const
{
	return _Done;
}



BaseLoopThread::BaseLoopThread(const char * name)
	: Name(name)
	, Thread(&BaseLoopThread::ThreadFunc, this)
{ }

void BaseLoopThread::Join()
{
	Thread.join();
}



void BaseLoopThread::ThreadFunc()
{
	BaseLoopThread::ThreadName = Name;
	while (!_Terminate)
	{
		LoopFunc();
	}
	_Done = true;
}
