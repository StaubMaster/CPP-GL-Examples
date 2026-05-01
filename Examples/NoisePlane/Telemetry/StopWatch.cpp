#include "StopWatch.hpp"
#include "Time.hpp"


//	bool	Watching;
//	double	Time0;
//	double	Time1;

bool StopWatch::IsWatching() const { return Watching; }
double StopWatch::ElapsedTime() const
{
	if (Watching)
	{
		return TimeNow() - Time0;
	}
	else
	{
		return Time1 - Time0;
	}
}



StopWatch::~StopWatch() { }
StopWatch::StopWatch()
	: Watching(false)
	, Time0(0.0)
	, Time1(0.0)
{ }



void StopWatch::Stop()
{
	if (Watching)
	{
		Watching = false;
		Time1 = TimeNow();
	}
}
void StopWatch::Start()
{
	if (!Watching)
	{
		Watching = true;
		Time0 = TimeNow();
	}
}

void StopWatch::ReStart()
{
	Watching = true;
	Time0 = TimeNow();
}
