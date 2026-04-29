#include "Manager.hpp"
#include "ObjectData.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "../Window.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"

#include "ValueType/_Show.hpp"
#include <iostream>





UI::Control::Manager * UI::Control::Manager::CurrentPointer = nullptr;
UI::Control::Manager & UI::Control::Manager::Current() { return *CurrentPointer; }
bool UI::Control::Manager::CheckCurrent() { return (UI::Control::Manager::CurrentPointer != nullptr); }
void UI::Control::Manager::ClearCurrent() { UI::Control::Manager::CurrentPointer = nullptr; }
bool UI::Control::Manager::IsCurrent() const { return (UI::Control::Manager::CurrentPointer == this); }
void UI::Control::Manager::MakeCurrent() { UI::Control::Manager::CurrentPointer = this; }





UI::Control::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Control::Manager::~Manager()" << "\n";
}
UI::Control::Manager::Manager()
	: Shader()
	, Buffer()
	, WindowSize()
	, Window()
	, Hovering(nullptr)
	, Selected(nullptr)
	, GraphicsExist(false)
	, GraphicsNeedInit(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Window.Show();
}



UI::Control::ObjectData * UI::Control::Manager::PlaceObject()
{
	ObjectData * obj = new ObjectData();
	ObjectDatas.Insert(obj);
	return obj;
}
UI::Control::ObjectData * UI::Control::Manager::CopyObject(const ObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	ObjectData * ret = PlaceObject();
	*ret = *obj;
	return ret;
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

	Buffer.Main.Data(data);

	GraphicsNeedMain = false;
}
void UI::Control::Manager::GraphicsInst()
{
	Instances.Clear();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			if (obj.Display)
			{
				PlaceInstance(obj);
			}
			if (obj.Remove)
			{
				ObjectDatas.Remove(i);
				delete &obj;
				i--;
			}
		}
	}
	Buffer.Inst.Data(Instances);
}

void UI::Control::Manager::PlaceInstance(const ObjectData & obj)
{
	Inst_Data data;
	data.Min = obj.Box.Min;
	data.Max = obj.Box.Max;
	data.Layer = obj.Layer;
	data.Col = obj.Color;
	Instances.Insert(data);
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
		if (Hovering != nullptr) { Hovering -> HoverLeave(); }
		Hovering = control;
		if (Hovering != nullptr) { Hovering -> HoverEnter(); }
	}
	if (Hovering != nullptr) { /* Hover Over */ }
}





void UI::Control::Manager::RelayClick(ClickArgs args)
{
	if (Hovering != nullptr)
	{
		Hovering -> RelayClick(args);
	}
	Selected = Hovering;
}
void UI::Control::Manager::RelayScroll(ScrollArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayScroll(args);
	}
}
void UI::Control::Manager::RelayCursorDrag(DragArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayCursorDrag(args);
	}
}
void UI::Control::Manager::RelayKey(KeyArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayKey(args);
	}
}
void UI::Control::Manager::RelayText(TextArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayText(args);
	}
}
