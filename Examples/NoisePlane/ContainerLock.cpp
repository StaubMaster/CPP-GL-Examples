#include "ContainerLock.hpp"
#include "Telemetry/ThreadInfo.hpp"
//#include <iostream>



unsigned int ContainerLock::Count() const { return AccessCount.load(); }



ContainerLock::~ContainerLock() { }
ContainerLock::ContainerLock()
	: AssignMutex()
	, AccessMutex()
	, AccessCount(0)
{ }



void ContainerLock::AccessL()
{
//	std::cerr << "wait Checking0:" << ThreadInfo::ThreadName << '\n';
	AccessMutex.lock();
	AccessCount++;
	AccessMutex.unlock();
//	std::cerr << "have Checking0:" << ThreadInfo::ThreadName << '\n';
}
void ContainerLock::AccessU()
{
//	std::cerr << "have Checking1:" << ThreadInfo::ThreadName << '\n';
	AccessCount--;
//	std::cerr << "done Checking1:" << ThreadInfo::ThreadName << '\n';
}
void ContainerLock::AssignL()
{
//	std::cerr << "wait Changing0:" << ThreadInfo::ThreadName << '\n';
	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }
//	std::cerr << "have Changing0:" << ThreadInfo::ThreadName << '\n';
}
void ContainerLock::AssignU()
{
//	std::cerr << "have Changing1:" << ThreadInfo::ThreadName << '\n';
	AccessMutex.unlock();
	AssignMutex.unlock();
//	std::cerr << "done Changing1:" << ThreadInfo::ThreadName << '\n';
}



void ContainerLock::AccessL(StopWatch & watch, WaitDoTime & time)
{
//	std::cerr << "wait Checking0:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
	time.ThreadName = ThreadInfo::ThreadName;
	watch.Clear(); watch.Start();

	AccessMutex.lock();
	AccessCount++;
	AccessMutex.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
//	std::cerr << "have Checking0:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
}
void ContainerLock::AccessU(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "have Checking1:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
	AccessCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
//	std::cerr << "done Checking1:" << (const void *)ThreadInfo::ThreadName << '\n' << std::flush;
}
void ContainerLock::AssignL(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "wait Changing0:" << ThreadInfo::ThreadName << '\n';
	watch.Clear(); watch.Start();

	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
//	std::cerr << "have Changing0:" << ThreadInfo::ThreadName << '\n';
}
void ContainerLock::AssignU(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
//	std::cerr << "have Changing1:" << ThreadInfo::ThreadName << '\n';
	AccessMutex.unlock();
	AssignMutex.unlock();
	
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
