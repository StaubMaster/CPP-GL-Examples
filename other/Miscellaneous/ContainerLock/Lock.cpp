#include "ContainerLock/Lock.hpp"
#include "AuxThreadBase.hpp"
//#include <iostream>

//#define LOG_THREAD_INFO



bool ContainerLock::InUse() const { return (UseCount.load() != 0); }



ContainerLock::~ContainerLock()
{ }
ContainerLock::ContainerLock()
	: UseCount(0)
	, AssignMutex()
	, AccessMutex()
	, AccessCount(0)
{ }



void ContainerLock::AccessL()
{
	UseCount++;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " wait AccessL" << '\n';
#endif
	AccessMutex.lock();
	AccessCount++;
	AccessMutex.unlock();
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AccessL" << '\n';
#endif
}
void ContainerLock::AccessU()
{
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AccessU" << '\n';
#endif
	AccessCount--;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " done AccessU" << '\n';
#endif
	UseCount--;
}

bool ContainerLock::AccessT()
{
	UseCount++;
	if (AccessMutex.try_lock())
	{
		AccessCount++;
		AccessMutex.unlock();
		return true;
	}
	UseCount--;
	return false;
}
void ContainerLock::AccessToAssign()
{
	AccessCount--;
	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }
}

void ContainerLock::AssignL()
{
	UseCount++;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " wait AssignL" << '\n';
#endif
	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AssignL" << '\n';
#endif
}
void ContainerLock::AssignU()
{
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AssignU" << '\n';
#endif
	AccessMutex.unlock();
	AssignMutex.unlock();
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " done AssignU" << '\n';
#endif
	UseCount--;
}



void ContainerLock::AccessL(StopWatch & watch, WaitDoTime & time)
{
	UseCount++;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " wait AccessL" << '\n' << std::flush;
#endif
	time.ThreadName = AuxThreadBase::ThreadName;
	watch.Clear(); watch.Start();

	AccessMutex.lock();
	AccessCount++;
	AccessMutex.unlock();

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AccessL" << '\n' << std::flush;
#endif
}
void ContainerLock::AccessU(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = AuxThreadBase::ThreadName;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AccessU" << '\n' << std::flush;
#endif
	AccessCount--;

	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " done AccessU" << '\n' << std::flush;
#endif
	UseCount--;
}

void ContainerLock::AssignL(StopWatch & watch, WaitDoTime & time)
{
	UseCount++;
	time.ThreadName = AuxThreadBase::ThreadName;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " wait AssignL" << '\n';
#endif
	watch.Clear(); watch.Start();

	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }

	watch.Stop();
	time.WaitTime.NewValue(watch.ElapsedTime());
	watch.Clear(); watch.Start();
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AssignL" << '\n';
#endif
}
void ContainerLock::AssignU(StopWatch & watch, WaitDoTime & time)
{
	time.ThreadName = AuxThreadBase::ThreadName;
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " have AssignU" << '\n';
#endif
	AccessMutex.unlock();
	AssignMutex.unlock();
	
	watch.Stop();
	time.DoTime.NewValue(watch.ElapsedTime());
#ifdef LOG_THREAD_INFO
	std::cerr << AuxThreadBase::ThreadName << " done AssignU" << '\n';
#endif
	UseCount--;
}
