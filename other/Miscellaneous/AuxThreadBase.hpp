#ifndef  AUX_THREAD_BASE_HPP
# define AUX_THREAD_BASE_HPP

# include <thread>
# include <mutex>
# include <condition_variable>

struct AuxThreadBase // IdleThread
{
	public:
	static thread_local const char *	ThreadName;

	private:
	std::thread		Thread;
	const char *	Name;

	private:
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;

	public:
	bool	DoTerminate = false;
	bool	DoIdle = true;
	bool	IsWaiting = false;
	bool	IsDone = false;

	public:
	//void	Term();

	public:
	~AuxThreadBase() = default;
	AuxThreadBase() = delete;
	AuxThreadBase(const AuxThreadBase & other) = delete;
	AuxThreadBase & operator=(const AuxThreadBase & other) = delete;
	AuxThreadBase(const char * name);

	public:
	void	Poke();
	void	Join();

	private:
	void	ThreadFunc();

	protected:
	// true  : condition met, do
	// false : condition not met, keep waiting
	virtual bool	CheckFunc() = 0;
	virtual void	DoFunc() = 0;
};

#endif