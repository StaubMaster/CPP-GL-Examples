#include "ContextBase.hpp"

#include "Debug.hpp"

// Contexts
#include "Context0/Context0.hpp"
#include "Context1/Context1.hpp"
#include "../NoisePlane/main.cpp"



::Window *		ContextBase::WindowPointer = nullptr;
::ContextBase *	ContextBase::ContextToUse = nullptr;

void ContextBase::Quit()
{
	ContextToUse = nullptr;
	if (WindowPointer != nullptr)
	{
		WindowPointer -> ExitLoop();
	}
}
void ContextBase::Change(ContextBase * context)
{
	ContextToUse = context;
	if (WindowPointer != nullptr)
	{
		WindowPointer -> ExitLoop();
	}
}

void ContextBase::ChangeToContext0()
{
	Change(new Context0());
}
void ContextBase::ChangeToContext1()
{
	Change(new Context1());
}
void ContextBase::ChangeToNoisePlane()
{
	Change(new ContextNoisePlane());
}





ContextBase::~ContextBase() { }
ContextBase::ContextBase()
	: window(*WindowPointer)
	, MediaDirectory("../media/")
{ }

void ContextBase::Run()
{
	window.CallBack_Init.Assign<ContextBase>(this, &ContextBase::Init);
	window.CallBack_Free.Assign<ContextBase>(this, &ContextBase::Free);
	window.CallBack_Resize.Assign<ContextBase>(this, &ContextBase::Resize);
	window.CallBack_Frame.Assign<ContextBase>(this, &ContextBase::Frame);

	window.MouseManager.Callback_ScrollEvent.Assign<ContextBase>(this, &ContextBase::MouseScroll);
	window.MouseManager.Callback_ClickEvent.Assign<ContextBase>(this, &ContextBase::MouseClick);
	window.MouseManager.Callback_DragEvent.Assign<ContextBase>(this, &ContextBase::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign<ContextBase>(this, &ContextBase::KeyBoardKey);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.RunLoop();
	Debug::Log << ">>>> Run Window" << Debug::Done;
}
