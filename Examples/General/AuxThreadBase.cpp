#include "AuxThreadBase.hpp"



AuxThreadBase::~AuxThreadBase()
{ }
AuxThreadBase::AuxThreadBase()
	: Thread(&AuxThreadBase::Func, this)
	, ConditionVar()
	, ConditionVarMutex()
	, Term(false)
	, DoIdle(true)
	, IsIdle(false)
	, Done(false)
{ }





void AuxThreadBase::Poke()
{
	ConditionVar.notify_all();
}
void AuxThreadBase::Join()
{
	Thread.join();
}
