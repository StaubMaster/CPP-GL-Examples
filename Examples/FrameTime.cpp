#include "FrameTime.hpp"

FrameTime::FrameTime(float frames_per_second)
	: WantedFramesPerSecond(frames_per_second)
	, WantedFrameTime(1.0f / frames_per_second)
	, ActualFrameTime(0.0f)
	, ActualFramesPerSecond(0.0f)
	, Delta(0.0f)
{ }
void FrameTime::Update(float framer_time)
{
	ActualFrameTime = framer_time;
	ActualFramesPerSecond = 1.0 / framer_time;

	if (ActualFrameTime < WantedFrameTime)
	{ Delta = ActualFrameTime; }
	else
	{ Delta = WantedFrameTime; }
}
