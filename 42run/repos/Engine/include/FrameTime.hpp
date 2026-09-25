#ifndef  FRAME_TIME_HPP
# define FRAME_TIME_HPP

struct FrameTime
{
	float	TimeNow;

	float	WantedFramesPerSecond;
	float	WantedFrameTime;

	float	ActualFramesPerSecond;
	float	ActualFrameTime;

	float	DeltaLimit;
	float	Delta;

	bool				Ready; // stupid name
	unsigned long long	Number;

	FrameTime(float wanted_frames_per_second, float delta_limit);

	void	Change(float wanted_frames_per_second);
	void	Update(float time_now);
};

#endif