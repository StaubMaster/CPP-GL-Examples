#ifndef  AUX_THREAD_BASE_HPP
# define AUX_THREAD_BASE_HPP

# include <thread>

/* put condision_var here
	Poke to unIdle
	dont want all the ones that want ThreadName to include all the Thread stuff
	put threadName into its own thing
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