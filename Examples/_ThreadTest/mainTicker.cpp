#include <iostream>
#include <chrono>
#include <thread>

#include "Threading/Thread/Loop/Tick.hpp"

struct Ticker : public TickLoopThread
{
	Ticker()
		: TickLoopThread("TickThread", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)) / 1)
	{ }

	void DoFunc() override
	{
		std::cout << "Tick\n";
	}
};

//#define TEST_FRAMETIME

#ifdef TEST_FRAMETIME
# include "FrameTime.hpp"
# include "OpenGL.hpp"
#endif

int main()
{
#ifdef TEST_FRAMETIME
	glfwInit();
	FrameTime frame_time(1.0f, 4 / 1.0f);
	frame_time.TimeNow = glfwGetTime();
#endif
	Ticker ticker;
	std::cout << "Ticker ....\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	ticker.DoIdle = false;
	ticker.Poke();
	std::cout << "Ticker done\n";
	//std::chrono::time_point<std::chrono::steady_clock> tick_point = std::chrono::steady_clock::now();
	//std::chrono::milliseconds tick_time = std::chrono::milliseconds(1000);
	while (1)
	{
		//std::chrono::milliseconds time_wait = std::chrono::duration_cast<std::chrono::milliseconds>((tick_point + tick_time) - std::chrono::steady_clock::now());
		//if (time_wait.count() < 0)
		//{
		//	std::cout << "MainThread\n";
		//	tick_point = std::chrono::steady_clock::now();
		//}
#ifdef TEST_FRAMETIME
		frame_time.Update(glfwGetTime());
		if (frame_time.Ready)
		{
			std::cout << "MainThread\n";
			frame_time.Ready = false;
		}
#endif
		//std::this_thread::sleep_for(std::chrono::seconds(3));
		//std::cout << "MainThread\n";
		//ticker.Poke();
	}
	return 0;
}
