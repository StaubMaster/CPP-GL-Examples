#ifndef  AUX_THREAD_BASE_HPP
# define AUX_THREAD_BASE_HPP

# include <thread>
# include <mutex>
# include <condition_variable>

/* Condition Var ?
*/

struct AuxThreadBase
{
	public:
	static thread_local const char *	ThreadName;

	private:
	std::thread		Thread;

	protected:
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;

	public:
	bool	Term;
	bool	DoIdle;
	bool	IsIdle;

	public:
	~AuxThreadBase();
	AuxThreadBase() ;
	AuxThreadBase(const AuxThreadBase & other) = delete;
	AuxThreadBase & operator=(const AuxThreadBase & other) = delete;

	public:
	void	Poke();
	void	Join();

	public:
	virtual void	Func() = 0;
};

#endif