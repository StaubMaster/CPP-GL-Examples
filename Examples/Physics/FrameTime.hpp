#ifndef  FRAME_TIME_HPP
# define FRAME_TIME_HPP

struct FrameTime
{
	float	WantedFramesPerSecond;
	float	WantedFrameTime;
	float	ActualFrameTime;
	float	ActualFramesPerSecond;

	float	Delta;

	FrameTime(float frames_per_second);
	void Update(float framer_time);
};

#endif