#ifndef  AUX_THREAD_BASE_HPP
# define AUX_THREAD_BASE_HPP

# include <thread>

/* Condition Var ?
*/

struct AuxThreadBase
{
	static thread_local const char *	ThreadName;
	
	std::thread		Thread;
	bool			Term;
	bool			DoIdle;
	bool			IsIdle;

	~AuxThreadBase();
	AuxThreadBase() ;
	AuxThreadBase(const AuxThreadBase & other) = delete;
	AuxThreadBase & operator=(const AuxThreadBase & other) = delete;

	void			Join();
	virtual void	Func() = 0;
};

#endif