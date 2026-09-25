#include "User/MouseManager.hpp"

#include "Window.hpp"
//#include <GLFW/glfw3.h>



const MouseState & MouseManager::operator[](const MouseButtons & button) const
{
	for (unsigned int i = 0; i < StateNum; i++)
	{
		if (MouseStates[i].Button == button)
		{
			return MouseStates[i];
		}
	}
	throw "MouseManager[]: MouseButton not found.";
}



MouseManager::~MouseManager() { }
MouseManager::MouseManager(Window & win)
	: window(win)
	, MouseStates{
		MouseState(MouseButtons::Mouse1),
		MouseState(MouseButtons::Mouse2),
		MouseState(MouseButtons::Mouse3),
		MouseState(MouseButtons::Mouse4),
		MouseState(MouseButtons::Mouse5),
		MouseState(MouseButtons::Mouse6),
		MouseState(MouseButtons::Mouse7),
		MouseState(MouseButtons::Mouse8),
	}
{ }



bool MouseManager::CursorModeIsLocked() const
{
	return (glfwGetInputMode(window.glfw_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED);
}
void MouseManager::CursorModeLock()
{
	glfwSetInputMode(window.glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window.glfw_window, 0, 0);
}
void MouseManager::CursorModeFree()
{
	glfwSetCursorPos(window.glfw_window, 0, 0);
	glfwSetInputMode(window.glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void MouseManager::CursorModeToggle()
{
	if (CursorModeIsLocked())
	{
		CursorModeFree();
	}
	else
	{
		CursorModeLock();
	}
}

// Cache CursorPosition when Tick is called ?
// or only Calculate when Cursor Moves ?
DisplayPosition MouseManager::CursorPosition() const
{
	double x, y;
	glfwGetCursorPos(window.glfw_window, &x, &y);
	//return DisplayPosition::FromWindowCorner(VectorF2(x, y), window.Size);
	return window.Size.PosFromWindowFull(VectorF2(x, y));
}
void MouseManager::CursorPositionTick()
{
	if (CursorModeIsLocked())
	{
		glfwSetCursorPos(window.glfw_window, 0, 0);
	}
}



void MouseManager::Tick()
{
	for (unsigned int i = 0; i < StateNum; i++)
	{
		MouseStates[i].Tick();
	}
}
void MouseManager::Update(MouseButtons button, Action action)
{
	for (unsigned int i = 0; i < StateNum; i++)
	{
		if (MouseStates[i].Button == button)
		{
			MouseStates[i].Update(CursorPosition(), action);
		}
	}
}



void MouseManager::Invoke_ClickEvent(int button, int action, int mods)
{
	Update((MouseButtons)button, (Action)action);

	//Callback_ClickEvent(ClickArgs((Modifier)mods, (Action)action, (MouseButtons)button, CursorPosition()));
	Callback_ClickEvent.TryInvoke(ClickArgs(mods, action, button, CursorPosition()));

	for (unsigned int i = 0; i < StateNum; i++)
	{
		MouseState & state = MouseStates[i];
		if (state.State == State::Release)
		{
			if (state.IsDragging)
			{
				state.IsDragging = false;
				//DragArgs args;
				//args.Button = MouseStates[i].Button;
				//args.Action = Action::Release;
				//args.Position = MouseStates[i].LastReleasePosition;
				//Callback_DragEvent(args);
				Callback_DragEvent.TryInvoke(DragArgs(Modifier::None, Action::Release, state.Button, state.LastReleasePosition));
			}
		}
	}
}
void MouseManager::Invoke_ScrollEvent(float offset_x, float offset_y)
{
	Callback_ScrollEvent.TryInvoke(ScrollArgs(Modifier::None, offset_x, offset_y, CursorPosition()));
}
void MouseManager::Invoke_MoveEvent(double x_pos, double y_pos)
{
	//DisplayPosition pos = DisplayPosition::FromWindowCorner(VectorF2(x_pos, y_pos), window.Size);
	DisplayPosition pos = window.Size.PosFromWindowFull(VectorF2(x_pos, y_pos));

	Callback_MoveEvent.TryInvoke(MoveArgs(pos));

	for (unsigned int i = 0; i < StateNum; i++)
	{
		MouseState & state = MouseStates[i];
		if (state.State == State::Down)
		{
			if (!state.IsDragging)
			{
				state.IsDragging = true;
				Callback_DragEvent.TryInvoke(DragArgs(Modifier::None, Action::Press, state.Button, state.LastPressPosition));
			}
			if (state.IsDragging)
			{
				Callback_DragEvent.TryInvoke(DragArgs(Modifier::None, Action::Repeat, state.Button, pos));
			}
		}
	}
}
