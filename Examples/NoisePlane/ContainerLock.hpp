#ifndef  CONTAINER_LOCK_HPP
# define CONTAINER_LOCK_HPP

# include <mutex>
# include <atomic>

# include "Telemetry/WaitDoTime.hpp"
# include "Telemetry/StopWatch.hpp"

struct ContainerLock
{
	private:
	std::mutex					Changing;	// changing Items
	std::mutex					Checking;	// changing Container
	std::atomic<unsigned int>	CheckingCount;

	// terrible names
	// Changing changes the Container
	//  resize, assign Items
	// Checking changes Items

	public:
	unsigned int	Count() const;

	public:
	~ContainerLock();
	ContainerLock();
	ContainerLock(const ContainerLock & other) = delete;
	ContainerLock & operator=(const ContainerLock & other) = delete;

	public:
	void	Checking0();
	void	Checking1();
	void	Changing0();
	void	Changing1();

	void	Checking0(StopWatch & watch, WaitDoTime & time);
	void	Checking1(StopWatch & watch, WaitDoTime & time);
	void	Changing0(StopWatch & watch, WaitDoTime & time);
	void	Changing1(StopWatch & watch, WaitDoTime & time);
};

#endif