#include "ContainerLock.hpp"
#include "Telemetry/ThreadInfo.hpp"
//#include <iostream>

//#define LOG_THREAD_INFO



unsigned int ContainerLock::Count() const { return AccessCount.load(); }



ContainerLock::~ContainerLock() { }
ContainerLock::ContainerLock()
	: AssignMutex()
	, AccessMutex()
	, AccessCount(0)
{ }



void ContainerLock::AccessL()
{
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " wait AccessL" << '\n';
#endif
	AccessMutex.lock();
	AccessCount++;
	AccessMutex.unlock();
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AccessL" << '\n';
#endif
}
void ContainerLock::AccessU()
{
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AccessU" << '\n';
#endif
	AccessCount--;
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " done AccessU" << '\n';
#endif
}
void ContainerLock::AssignL()
{
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " wait AssignL" << '\n';
#endif
	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AssignL" << '\n';
#endif
}
void ContainerLock::AssignU()
{
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AssignU" << '\n';
#endif
	AccessMutex.unlock();
	AssignMutex.unlock();
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " done AssignU" << '\n';
#endif
}



void ContainerLock::AccessL(StopWatch & watch, WaitDoTime & time)
{
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " wait AccessL" << '\n' << std::flush;
#endif
	time.ThreadName = ThreadInfo::ThreadName;
	watch.Clear(); watch.Start();

	AccessMutex.lock();
	AccessCount++;
	AccessMutex.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AccessL" << '\n' << std::flush;
#endif
}
void ContainerLock::AccessU(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AccessU" << '\n' << std::flush;
#endif
	AccessCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " done AccessU" << '\n' << std::flush;
#endif
}
void ContainerLock::AssignL(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " wait AssignL" << '\n';
#endif
	watch.Clear(); watch.Start();

	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AssignL" << '\n';
#endif
}
void ContainerLock::AssignU(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = ThreadInfo::ThreadName;
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " have AssignU" << '\n';
#endif
	AccessMutex.unlock();
	AssignMutex.unlock();
	
	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
#ifdef LOG_THREAD_INFO
	std::cerr << ThreadInfo::ThreadName << " done AssignU" << '\n';
#endif
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
