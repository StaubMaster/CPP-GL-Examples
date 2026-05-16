#include "ContainerLock.hpp"
#include "Telemetry/ThreadInfo.hpp"
//#include <iostream>



unsigned int ContainerLock::Count() const { return ItemLockCount.load(); }



ContainerLock::~ContainerLock() { }
ContainerLock::ContainerLock()
	: ContainerMutex()
	, ItemMutex()
	, ItemLockCount(0)
{ }



void ContainerLock::LockItems()
{
//	std::cerr << "wait Checking0:" << ThreadName << '\n';
	ItemMutex.lock();
	ItemLockCount++;
	ItemMutex.unlock();
//	std::cerr << "have Checking0:" << ThreadName << '\n';
}
void ContainerLock::UnLockItems()
{
//	std::cerr << "have Checking1:" << ThreadName << '\n';
	ItemLockCount--;
//	std::cerr << "done Checking1:" << ThreadName << '\n';
}
void ContainerLock::LockContainer()
{
//	std::cerr << "wait Changing0:" << ThreadName << '\n';
	ContainerMutex.lock();
	ItemMutex.lock();
	while (ItemLockCount.load() != 0) { }
//	std::cerr << "have Changing0:" << ThreadName << '\n';
}
void ContainerLock::UnlockContainer()
{
//	std::cerr << "have Changing1:" << ThreadName << '\n';
	ItemMutex.unlock();
	ContainerMutex.unlock();
//	std::cerr << "done Changing1:" << ThreadName << '\n';
}



void ContainerLock::LockItems(StopWatch & watch, WaitDoTime & time)
{
//	std::cout << "wait Checking0:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
	time.ThreadName = ThreadInfo::ThreadName;
	watch.Clear(); watch.Start();

	ItemMutex.lock();
	ItemLockCount++;
	ItemMutex.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
//	std::cout << "have Checking0:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
}
void ContainerLock::UnLockItems(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cout << "have Checking1:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
	ItemLockCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cout << "done Checking1:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
}
void ContainerLock::LockContainer(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "wait Changing0:" << ThreadInfo::ThreadName << '\n';
	watch.Clear(); watch.Start();

	ContainerMutex.lock();
	ItemMutex.lock();
	while (ItemLockCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
//	std::cerr << "have Changing0:" << ThreadInfo::ThreadName << '\n';
}
void ContainerLock::UnlockContainer(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "have Changing1:" << ThreadInfo::ThreadName << '\n';
	ItemMutex.unlock();
	ContainerMutex.unlock();
	
	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cerr << "done Changing1:" << ThreadInfo::ThreadName << '\n';
}





/*ContainerLock::Object::~Object()
{
	if (IsLocked)
	{

	}
}
ContainerLock::Object::Object(ContainerLock & lock)
	: Lock(lock)
	, IsLocked(true)
{ }
ContainerLock::Object::Object(const Object & other)
{ }
void ContainerLock::Object::Dispose()*/
