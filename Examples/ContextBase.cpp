#include "ContextBase.hpp"

#include "Debug.hpp"
#include <iostream>
#include <sstream>

// Contexts
#include "Context0/new.hpp"
#include "Context1/new.hpp"
#include "NoisePlane/new.hpp"
#include "TestTextAlignment/new.hpp"



::Window *						ContextBase::WindowPointer = nullptr;
::StaticFunction<ContextBase*>	ContextBase::NewContext;

void ContextBase::Quit()
{
	NewContext.Assign(nullptr);
	if (WindowPointer != nullptr)
	{
		WindowPointer -> ExitLoop();
	}
}
void ContextBase::Change(StaticFunction<ContextBase*>::FunctionType new_context)
{
	NewContext.Assign(new_context);
	if (WindowPointer != nullptr)
	{
		WindowPointer -> ExitLoop();
	}
}

void ContextBase::ChangeToContext0()
{
	Change(newContext0);
}
void ContextBase::ChangeToContext1()
{
	Change(newContext1);
}
void ContextBase::ChangeToNoisePlane()
{
	Change(newContextNoisePlane);
}
void ContextBase::ChangeToTestTextAlignment()
{
	Change(newContextTestTextAlignment);
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

	window.MouseManager.Callback_MoveEvent.Assign<ContextBase>(this, &ContextBase::MouseMove);
	window.MouseManager.Callback_ClickEvent.Assign<ContextBase>(this, &ContextBase::MouseClick);
	window.MouseManager.Callback_ScrollEvent.Assign<ContextBase>(this, &ContextBase::MouseScroll);
	window.MouseManager.Callback_DragEvent.Assign<ContextBase>(this, &ContextBase::MouseDrag);

	window.KeyBoardManager.CallBack_KeyEvent.Assign<ContextBase>(this, &ContextBase::KeyBoardKey);
	window.KeyBoardManager.CallBack_TextEvent.Assign<ContextBase>(this, &ContextBase::KeyBoardText);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.RunLoop();
	Debug::Log << ">>>> Run Window" << Debug::Done;
}
