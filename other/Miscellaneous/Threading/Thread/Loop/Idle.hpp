#ifndef  THREAD_LOOP_IDLE_HPP
# define THREAD_LOOP_IDLE_HPP

# include "Threading/Thread/Loop/Base.hpp"

# include <mutex>
# include <condition_variable>

struct IdleLoopThread : public BaseLoopThread
{
	public:
	~IdleLoopThread() = default;
	IdleLoopThread() = delete;
	IdleLoopThread(const IdleLoopThread & other) = delete;
	IdleLoopThread & operator=(const IdleLoopThread & other) = delete;

	protected:
	IdleLoopThread(const char * name);

	private:
	void	LoopFunc() override;

	private:
	bool	_Waiting = false;
	public:
	bool	IsWaiting() const;

	private:
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;
	public:
	void	Poke() override;

	private:
	// true  : condition met, do
	// false : condition not met, keep waiting
	virtual bool	CheckFunc() = 0;
	virtual void	DoFunc() = 0;
};

#endif