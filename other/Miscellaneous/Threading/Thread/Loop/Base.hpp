#ifndef  THREAD_LOOP_BASE_HPP
# define THREAD_LOOP_BASE_HPP

# include <thread>

struct BaseLoopThread
{
	public:
	static thread_local const char *	ThreadName;

	protected:
	enum class EState
	{
		None,
		Running,
		Joining,
		Done,
	};
	EState	State = EState::None;
	public:
	void	Run();
	void	JoinRequest();
	bool	JoinCan() const;
	void	Join();

	//public:
	//bool	DoIdle = false;
	//public:
	//bool	IsIdle();
	//void	MakeIdle();
	//void	DontIdle();

	private:
	const char *	Name;
	std::thread		Thread;

	public:
	virtual ~BaseLoopThread() = default;
	BaseLoopThread() = delete;
	BaseLoopThread(const BaseLoopThread & other) = delete;
	BaseLoopThread & operator=(const BaseLoopThread & other) = delete;

	public:
	BaseLoopThread(const char * name);

	private:
	void	ThreadFunc();
	private:
	virtual void	LoopFunc() = 0;
	public:
	virtual void	Poke() = 0;

};

#endif