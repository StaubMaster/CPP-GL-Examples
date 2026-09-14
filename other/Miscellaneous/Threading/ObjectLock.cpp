#include "Threading/ObjectLock.hpp"
#include "AuxThreadBase.hpp"

#include "Telemetry/WaitDoTime.hpp"
#include "Telemetry/StopWatch.hpp"

//#define LOG_THREAD_INFO

#ifdef LOG_THREAD_INFO
# include <iostream>
#endif


bool ObjectLock::InUse() const { return (UseCount.load() != 0); }



ObjectLock::~ObjectLock()
{ }
ObjectLock::ObjectLock()
	: UseCount(0)
	, AssignMutex()
	, AccessMutex()
	, AccessCount(0)
{ }



void ObjectLock::AccessL()
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
void ObjectLock::AccessU()
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

bool ObjectLock::AccessT()
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
void ObjectLock::AccessToAssign()
{
	AccessCount--;
	AssignMutex.lock();
	AccessMutex.lock();
	while (AccessCount.load() != 0) { }
}

void ObjectLock::AssignL()
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
void ObjectLock::AssignU()
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



void ObjectLock::AccessL(StopWatch & watch, WaitDoTime & time)
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
void ObjectLock::AccessU(StopWatch & watch, WaitDoTime & time)
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

void ObjectLock::AssignL(StopWatch & watch, WaitDoTime & time)
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
void ObjectLock::AssignU(StopWatch & watch, WaitDoTime & time)
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
