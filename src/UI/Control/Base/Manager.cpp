#include "Manager.hpp"
#include "UserParameter/MouseInclude.hpp"
#include "../Window.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "DataInclude.hpp"

#include <iostream>

//#include "OpenGL/Errors.hpp"
//#include "Debug.hpp"
//#include "DataShow.hpp"



UI::Control::Manager::Manager(const DirectoryInfo & dir) :
	Shader(),
	BufferArray(),
	Main_Data_Container(),
	Inst_Data_Container(),
	WindowSize(),
	Window(new UI::Control::Window(this))
{
	std::cout << "  ++++  " << "Manager()" << "\n";

	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(dir.File("UI/Control.vert")));
		code.Insert(::Shader::Code(dir.File("UI/Control.frag")));
		Shader.Change(code);
	}
	Shader.Create();
	BufferArray.Create();

	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, +1)));

	Window -> Show();

	Hovering = NULL;
	Selected = NULL;
}
UI::Control::Manager::~Manager()
{
	std::cout << "  ----  " << "~Manager()" << "\n";

	BufferArray.Delete();
	Shader.Delete();

	delete Window;
}



void UI::Control::Manager::Draw()
{
	if (!Inst_Data_Container.IsCompact())
	{
		Inst_Data_Container.CompactHere();
	}

	BufferArray.Bind();
	BufferArray.Main.Change(Main_Data_Container);
	BufferArray.Inst.Change(Inst_Data_Container);

	Shader.Bind();
	BufferArray.Bind();
	BufferArray.Draw();
}


void UI::Control::Manager::UpdateSize(const WindowBufferSize2D & window_size)
{
	WindowSize = window_size;
	Window -> UpdateWindowSize(WindowSize.WindowSize);
}
void UI::Control::Manager::UpdateMouse(Point2D mouse)
{
	UI::Control::Base * control = Window -> CheckHover(mouse);

	if (control != Hovering)
	{
		if (Hovering != NULL) { Hovering -> HoverLeave(); }
		Hovering = control;
		if (Hovering != NULL) { Hovering -> HoverEnter(); }
	}
	if (Hovering != NULL) { /* Hover Over */ }
}





void UI::Control::Manager::RelayClick(UserParameter::Mouse::Click params)
{
	if (Hovering != NULL)
	{
		Hovering -> RelayClick(params);
	}
	Selected = Hovering;
}
void UI::Control::Manager::RelayScroll(UserParameter::Mouse::Scroll params)
{
	if (Selected != NULL)
	{
		Selected -> RelayScroll(params);
	}
}
void UI::Control::Manager::RelayCursorDrag(UserParameter::Mouse::Drag params)
{
	if (Selected != NULL)
	{
		Selected -> RelayCursorDrag(params);
	}
}
void UI::Control::Manager::RelayKey(UserParameter::KeyBoard::Key params)
{
	if (Selected != NULL)
	{
		Selected -> RelayKey(params);
	}
}
void UI::Control::Manager::RelayText(UserParameter::KeyBoard::Text params)
{
	if (Selected != NULL)
	{
		Selected -> RelayText(params);
	}
}
