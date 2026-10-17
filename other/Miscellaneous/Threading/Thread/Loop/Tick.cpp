#include "Threading/Thread/Loop/Tick.hpp"



TickLoopThread::TickLoopThread(const char * name, std::chrono::milliseconds tick_time)
	: BaseLoopThread(name)
	, TickTime(tick_time)
{
	TickTimePoint = std::chrono::steady_clock::now();
}

/*
'#'		TickFunc		(when TickFunc is invoked)
'|'		TickDone		(when TickFunc returns)
'-'		TickDuration
' '		TickWait

0---|   1---|   #
0       1       #

0----------|1-| #
0           1   #
0       1       #

Frames should not be on static fixed Intervals

so each frame should start at TickTime after the last one started

if that time already passed (because last frame took to long)
then TimeWait should be 0 (negative clamped)

time_wait = TickTime - (now() - TimePoint)
time_wait = (TimePoint + TickTime) - now()
*/
#include <iostream>

void TickLoopThread::LoopFunc()
{
	if (DoIdle)
	{
		std::unique_lock<std::mutex> lk(ConditionVarMutex);
		ConditionVar.wait(lk);
	}
	if (DoIdle) { return; }

	std::chrono::milliseconds time_wait = std::chrono::duration_cast<std::chrono::milliseconds>((TickTimePoint + TickTime) - std::chrono::steady_clock::now());

	static int idx = 0;
	std::cout << BaseLoopThread::ThreadName << " wait: [" << idx << "] " << time_wait.count() << "ms\n";

	std::unique_lock<std::mutex> lk(ConditionVarMutex);
	std::cv_status status = ConditionVar.wait_for(lk, time_wait);
	/*ConditionVar.wait_for(lk, time_wait, [&]
	{
		if (_Terminate) { return true; }
		if (DoIdle) { return false; }
		return true;
	});*/

	if (_Terminate) { return; }
	if (DoIdle) { return; }

	if (status == std::cv_status::timeout)
	{
		TickTimePoint = std::chrono::steady_clock::now();
		DoFunc();
		idx++;
	}
}

void TickLoopThread::Poke()
{
	ConditionVar.notify_all();
}
