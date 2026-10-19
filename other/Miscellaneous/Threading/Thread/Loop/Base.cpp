#include "Threading/Thread/Loop/Base.hpp"



thread_local const char * BaseLoopThread::ThreadName = "ThreadName";



void BaseLoopThread::Run()
{
	if (State == EState::None)
	{
		Thread = std::thread(&BaseLoopThread::ThreadFunc, this);
		State = EState::Running;
	}
}
void BaseLoopThread::JoinRequest()
{
	if (State == EState::Running)
	{
		State = EState::Joining;
	}
}
bool BaseLoopThread::JoinCan() const
{
	return State == EState::Done;
}
void BaseLoopThread::Join()
{
	if (State == EState::None)
	{
		return;
	}
	if (State == EState::Running)
	{
		JoinRequest();
	}
	if (State == EState::Joining)
	{
		while (!JoinCan())
		{
			//DoIdle = false;
			Poke();
		}
	}
	if (State == EState::Done)
	{
		Thread.join();
	}
}



BaseLoopThread::BaseLoopThread(const char * name)
	: Name(name)
{ }

void BaseLoopThread::ThreadFunc()
{
	BaseLoopThread::ThreadName = Name;
	while (State != EState::Joining)
	{
		LoopFunc();
	}
	State = EState::Done;
}
