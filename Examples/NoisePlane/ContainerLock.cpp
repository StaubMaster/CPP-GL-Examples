#include "ContainerLock.hpp"
#include "Telemetry/ThreadInfo.hpp"
//#include <iostream>



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
//	std::cout << "wait Checking0:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
	time.ThreadName = ThreadInfo::ThreadName;
	watch.ReStart();

	Checking.lock();
	CheckingCount++;
	Checking.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
//	std::cout << "have Checking0:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
}
void ContainerLock::Checking1(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cout << "have Checking1:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
	CheckingCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cout << "done Checking1:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
}
void ContainerLock::Changing0(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "wait Changing0:" << ThreadInfo::ThreadName << '\n';
	watch.ReStart();

	Changing.lock();
	Checking.lock();
	while (CheckingCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.ReStart();
//	std::cerr << "have Changing0:" << ThreadInfo::ThreadName << '\n';
}
void ContainerLock::Changing1(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "have Changing1:" << ThreadInfo::ThreadName << '\n';
	Checking.unlock();
	Changing.unlock();
	
	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cerr << "done Changing1:" << ThreadInfo::ThreadName << '\n';
}
