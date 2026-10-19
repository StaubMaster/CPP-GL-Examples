#include "Threading/Thread/Loop/Tick.hpp"



TickLoopThread::TickLoopThread(const char * name, std::chrono::milliseconds tick_time)
	: BaseLoopThread(name)
	, TickTime(tick_time)
{
	TickTimePoint = std::chrono::steady_clock::now();
}



void TickLoopThread::LoopFunc()
{
	std::chrono::milliseconds time_wait = std::chrono::duration_cast<std::chrono::milliseconds>((TickTimePoint + TickTime) - std::chrono::steady_clock::now());

	std::unique_lock<std::mutex> lk(ConditionVarMutex);
	std::cv_status status = ConditionVar.wait_for(lk, time_wait);

	if (State == EState::Joining) { return; }

	if (status == std::cv_status::timeout)
	{
		TickTimePoint = std::chrono::steady_clock::now();
		DoFunc();
	}
}

void TickLoopThread::Poke()
{
	ConditionVar.notify_all();
}
