#ifndef  THREAD_LOOP_TICK_HPP
# define THREAD_LOOP_TICK_HPP

# include "Threading/Thread/Loop/Base.hpp"

# include <mutex>
# include <condition_variable>
# include <chrono>

struct TickLoopThread : public BaseLoopThread
{
	public:
	static thread_local const char *	ThreadName;

	public:
	~TickLoopThread() = default;
	TickLoopThread() = delete;
	TickLoopThread(const TickLoopThread & other) = delete;
	TickLoopThread & operator=(const TickLoopThread & other) = delete;

	protected:
	TickLoopThread(const char * name, std::chrono::milliseconds tick_time);

	private:
	void	LoopFunc() override;

	private:
	std::chrono::milliseconds								TickTime;
	std::chrono::time_point<std::chrono::steady_clock>		TickTimePoint;
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;
	public:
	void	Poke() override;

	private:
	virtual void	DoFunc() = 0;
};

#endif