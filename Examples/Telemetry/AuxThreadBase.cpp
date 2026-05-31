#include "AuxThreadBase.hpp"



AuxThreadBase::~AuxThreadBase()
{ }
AuxThreadBase::AuxThreadBase()
	: Thread(&AuxThreadBase::Func, this)
	, Term(false)
	, DoIdle(true)
	, IsIdle(false)
{ }





void AuxThreadBase::Join()
{
	Thread.join();
}
