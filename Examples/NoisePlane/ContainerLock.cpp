#include "ContainerLock.hpp"
//#include <iostream>



thread_local const char * ContainerLock::ThreadName	= "unnamed";



unsigned int ContainerLock::Count() const { return CheckingCount.load(); }



ContainerLock::~ContainerLock() { }
ContainerLock::ContainerLock()
	: Changing()
	, Checking()
	, CheckingCount(0)
{ }



void ContainerLock::Checking0()
{
//	std::cerr << "wait Checking0:" << ThreadName << '\n';
	Checking.lock();
	CheckingCount++;
	Checking.unlock();
//	std::cerr << "have Checking0:" << ThreadName << '\n';
}
void ContainerLock::Checking1()
{
//	std::cerr << "have Checking1:" << ThreadName << '\n';
	CheckingCount--;
//	std::cerr << "done Checking1:" << ThreadName << '\n';
}
void ContainerLock::Changing0()
{
//	std::cerr << "wait Changing0:" << ThreadName << '\n';
	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }
//	std::cerr << "have Changing0:" << ThreadName << '\n';
}
void ContainerLock::Changing1()
{
//	std::cerr << "have Changing1:" << ThreadName << '\n';
	Checking.unlock();
	Changing.unlock();
//	std::cerr << "done Changing1:" << ThreadName << '\n';
}



void ContainerLock::Checking0(StopWatch & watch, WaitDoTime & time)
{
//	std::cerr << "wait Checking0:" << ThreadName << '\n';
	time.ThreadName = ThreadName;
	watch.ReStart();

	Checking.lock();
	CheckingCount++;
	Checking.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
//	std::cerr << "have Checking0:" << ThreadName << '\n';
}
void ContainerLock::Checking1(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadName;
//	std::cerr << "have Checking1:" << ThreadName << '\n';
	CheckingCount--;
	
	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cerr << "done Checking1:" << ThreadName << '\n';
}
void ContainerLock::Changing0(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadName;
//	std::cerr << "wait Changing0:" << ThreadName << '\n';
	watch.ReStart();

	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
//	std::cerr << "have Changing0:" << ThreadName << '\n';
}
void ContainerLock::Changing1(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadName;
//	std::cerr << "have Changing1:" << ThreadName << '\n';
	Checking.unlock();
	Changing.unlock();
	
	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cerr << "done Changing1:" << ThreadName << '\n';
}
