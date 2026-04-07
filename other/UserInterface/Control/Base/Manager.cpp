#include "Manager.hpp"
#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "../Window.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"

#include <iostream>



UI::Control::Manager::Manager()
	: Shader()
	, Buffer()
	, Inst_Data_Container()
	, WindowSize()
	, Window()
	, GraphicsExist(false)
	, GraphicsNeedInit(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Window.Show();

	Hovering = NULL;
	Selected = NULL;
}
UI::Control::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Control::Manager::~Manager()" << "\n";
}



void UI::Control::Manager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();
	Shader.Create();

	GraphicsExist = true;

	GraphicsNeedInit = true;
	GraphicsNeedMain = true;
}
void UI::Control::Manager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();
	Shader.Delete();

	GraphicsExist = false;
}

void UI::Control::Manager::GraphicsInit()
{
	if (!(GraphicsNeedInit && GraphicsExist)) { return; }

	Buffer.Main.Init();
	Buffer.Inst.Init();

	GraphicsNeedInit = false;
}
void UI::Control::Manager::GraphicsMain()
{
	if (!(GraphicsNeedMain && GraphicsExist)) { return; }

	Container::Binary<Control::Main_Data> data;

	data.Insert(UI::Control::Main_Data(Point2D(-1, -1)));
	data.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	data.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	data.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	data.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	data.Insert(UI::Control::Main_Data(Point2D(+1, +1)));

	Buffer.Main.Change(data);

	GraphicsNeedMain = false;
}
void UI::Control::Manager::GraphicsInst()
{
	if (!Inst_Data_Container.IsCompact())
	{
		Inst_Data_Container.CompactHere();
	}
	Buffer.Inst.Change(Inst_Data_Container);
}



void UI::Control::Manager::Draw()
{
	GraphicsInit();
	GraphicsMain();
	GraphicsInst();

	Shader.Bind();
	Buffer.Bind();
	Buffer.Draw();
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





void UI::Control::Manager::RelayClick(ClickArgs args)
{
	if (Hovering != NULL)
	{
		Hovering -> RelayClick(args);
	}
	Selected = Hovering;
}
void UI::Control::Manager::RelayScroll(ScrollArgs args)
{
	if (Selected != NULL)
	{
		Selected -> RelayScroll(args);
	}
}
void UI::Control::Manager::RelayCursorDrag(DragArgs args)
{
	if (Selected != NULL)
	{
		Selected -> RelayCursorDrag(args);
	}
}
void UI::Control::Manager::RelayKey(KeyArgs args)
{
	if (Selected != NULL)
	{
		Selected -> RelayKey(args);
	}
}
void UI::Control::Manager::RelayText(TextArgs args)
{
	if (Selected != NULL)
	{
		Selected -> RelayText(args);
	}
}
