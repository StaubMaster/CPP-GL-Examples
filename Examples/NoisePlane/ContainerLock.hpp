#ifndef  CONTAINER_LOCK_HPP
# define CONTAINER_LOCK_HPP

# include <mutex>
# include <atomic>

# include "Telemetry/WaitDoTime.hpp"
# include "Telemetry/StopWatch.hpp"

struct ContainerLock
{
	/* Container Mutex
		when you want to change Container Memory
		Inserting/Removing
	*/
	/* Item Mutex
		when you want to access Items
		this prevents Container Memory from changing
		Items can still be changed by multiple Threads
	*/

	/*
		changing Items while they are being checked in another part will technically not cause a program crash
		but it is undefined, so it should be avoided
		ItemAccess
			like const
		ItemAssign
			Container stays the same
			Items change
		Container
			Container changes

		ItemAssign and Container can never overlap ?
		so just split into access and assign ?
	*/

	private:
	std::mutex					AssignMutex;
	std::mutex					AccessMutex;
	std::atomic<unsigned int>	AccessCount;

	public:
	unsigned int	Count() const;

	public:
	~ContainerLock();
	ContainerLock();

	ContainerLock(const ContainerLock & other) = delete;
	ContainerLock & operator=(const ContainerLock & other) = delete;

	public:
	void	AccessL();
	void	AccessU();
	void	AssignL();
	void	AssignU();

	public:
	void	AccessL(StopWatch & watch, WaitDoTime & time);
	void	AccessU(StopWatch & watch, WaitDoTime & time);
	void	AssignL(StopWatch & watch, WaitDoTime & time);
	void	AssignU(StopWatch & watch, WaitDoTime & time);

	public:
	/*struct Object
	{
		private:
		ContainerLock &		Lock;
		bool				IsLocked;

		public:
		~Object();
		Object() = delete;
		Object(ContainerLock & lock);
		Object(const Object & other);
		Object & operator=(const Object & other) = delete;
		void	Dispose();
	};*/
};

#endif