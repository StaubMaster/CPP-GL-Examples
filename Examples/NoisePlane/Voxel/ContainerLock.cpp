#include "ContainerLock.hpp"
#include <iostream>



unsigned int ContainerLock::Count() const { return CheckingCount.load(); }



ContainerLock::~ContainerLock() { }
ContainerLock::ContainerLock()
{ }



void ContainerLock::Checking0()
{
//	std::cout << "Checking0:" << __LINE__ << '\n';
	Checking.lock();
//	std::cout << "Checking0:" << __LINE__ << '\n';
	CheckingCount++;
//	std::cout << "Checking0:" << __LINE__ << '\n';
	Checking.unlock();
//	std::cout << "Checking0:" << __LINE__ << '\n';
}
void ContainerLock::Checking1()
{
	CheckingCount--;
}
void ContainerLock::Changing0()
{
	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }
}
void ContainerLock::Changing1()
{
	Checking.unlock();
	Changing.unlock();
}



void ContainerLock::Checking0(StopWatch & watch, WaitDoTime & time)
{
	watch.ReStart();

	Checking.lock();
	CheckingCount++;
	Checking.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
}
void ContainerLock::Checking1(StopWatch & watch, WaitDoTime & time)
{
	CheckingCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
}
void ContainerLock::Changing0(StopWatch & watch, WaitDoTime & time)
{
	watch.ReStart();

	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
}
void ContainerLock::Changing1(StopWatch & watch, WaitDoTime & time)
{
	Checking.unlock();
	Changing.unlock();

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
}
