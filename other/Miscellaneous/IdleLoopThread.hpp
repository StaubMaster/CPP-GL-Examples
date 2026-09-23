#ifndef  IDLE_LOOP_THREAD_HPP
# define IDLE_LOOP_THREAD_HPP

# include <thread>
# include <mutex>
# include <condition_variable>

struct IdleLoopThread
{
	public:
	static thread_local const char *	ThreadName;

	public:
	~IdleLoopThread() = default;
	IdleLoopThread() = delete;
	IdleLoopThread(const IdleLoopThread & other) = delete;
	IdleLoopThread & operator=(const IdleLoopThread & other) = delete;
	IdleLoopThread(const char * name);

	private:
	std::thread		Thread;
	const char *	Name;

	private:
	void	ThreadFunc();

	public:
	void	Join();

	private:
	bool	_Terminate = false;
	bool	_Done = false;
	public:
	void	DoTerminate();
	bool	IsDone() const;

	private:
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;
	private:
	bool	_Waiting = false;
	public:
	bool	IsWaiting() const;
	public:
	void	Poke();

	public:
	bool	DoIdle = true;
	public:
	//bool	IsIdle();
	//void	MakeIdle();
	//void	DontIdle();

	protected:
	// true  : condition met, do
	// false : condition not met, keep waiting
	virtual bool	CheckFunc() = 0;
	virtual void	DoFunc() = 0;
};

#endif