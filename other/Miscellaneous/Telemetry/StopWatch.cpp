#include "StopWatch.hpp"
#include "Time.hpp"



bool StopWatch::IsRunning() const { return Running; }
double StopWatch::ElapsedTime() const
{
	if (Running)
	{
		return (TimeNow() - TimeStamp) + TimeSum;
	}
	else
	{
		return TimeSum;
	}
}



StopWatch::~StopWatch() { }
StopWatch::StopWatch()
	: Running(false)
	, TimeStamp(0.0)
	, TimeSum(0.0)
{ }



void StopWatch::Clear()
{
	TimeStamp = 0.0;
	TimeSum = 0.0;
}
void StopWatch::Stop()
{
	if (Running)
	{
		TimeSum += (TimeNow() - TimeStamp);
		Running = false;
	}
}
void StopWatch::Start()
{
	if (!Running)
	{
		TimeStamp = TimeNow();
		Running = true;
	}
}
void StopWatch::TakeOver(StopWatch & other)
{
	if (Running && !other.Running)
	{
		double time = TimeNow();
		TimeSum += (time - TimeStamp);
		Running = false;
		other.TimeStamp = time;
		other.Running = true;
	}
}
