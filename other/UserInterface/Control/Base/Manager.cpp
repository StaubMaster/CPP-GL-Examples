#include "Manager.hpp"
#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "../Window.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueTypeInclude.hpp"

#include <iostream>

//#include "OpenGL/Errors.hpp"
//#include "Debug.hpp"
//#include "DataShow.hpp"



UI::Control::Manager::Manager() :
	Shader(),
	BufferArray(),
	Main_Data_Container(),
	Inst_Data_Container(),
	WindowSize(),
	Window()
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, +1)));

	Window.Show();

	Hovering = NULL;
	Selected = NULL;
}
UI::Control::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Control::Manager::~Manager()" << "\n";

	BufferArray.Delete();
	Shader.Delete();
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


void UI::Control::Manager::UpdateSize(const DisplaySize & window_size)
{
	WindowSize = window_size;
	Window.UpdateWindowSize(WindowSize.Buffer.Full);
}
void UI::Control::Manager::UpdateMouse(Point2D mouse)
{
	UI::Control::Base * control = Window.CheckHover(mouse);

	if (control != Hovering)
	{
		if (Hovering != NULL) { Hovering -> HoverLeave(); }
		Hovering = control;
		if (Hovering != NULL) { Hovering -> HoverEnter(); }
	}
	if (Hovering != NULL) { /* Hover Over */ }
}





void UI::Control::Manager::RelayClick(ClickArgs params)
{
	if (Hovering != NULL)
	{
		Hovering -> RelayClick(params);
	}
	Selected = Hovering;
}
void UI::Control::Manager::RelayScroll(ScrollArgs params)
{
	if (Selected != NULL)
	{
		Selected -> RelayScroll(params);
	}
}
void UI::Control::Manager::RelayCursorDrag(DragArgs params)
{
	if (Selected != NULL)
	{
		Selected -> RelayCursorDrag(params);
	}
}
void UI::Control::Manager::RelayKey(KeyArgs params)
{
	if (Selected != NULL)
	{
		Selected -> RelayKey(params);
	}
}
void UI::Control::Manager::RelayText(TextArgs params)
{
	if (Selected != NULL)
	{
		Selected -> RelayText(params);
	}
}
