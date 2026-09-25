#include "FrameTime.hpp"

FrameTime::FrameTime(float wanted_frames_per_second, float delta_limit)
	: TimeNow(0.0f)
	, WantedFramesPerSecond(wanted_frames_per_second)
	, WantedFrameTime(1.0f / wanted_frames_per_second)
	, ActualFramesPerSecond(0.0f)
	, ActualFrameTime(0.0f)
	, DeltaLimit(delta_limit)
	, Delta(0.0f)
	, Ready(false)
	, Number(0)
{ }

void FrameTime::Update(float time_now)
{
	ActualFrameTime = time_now - TimeNow;
	if (ActualFrameTime >= WantedFrameTime)
	{
		ActualFramesPerSecond = 1.0 / ActualFrameTime;
		if (ActualFrameTime < DeltaLimit)
			Delta = ActualFrameTime;
		else
			Delta = DeltaLimit;
		TimeNow = time_now;
		Ready = true;
	}
}
