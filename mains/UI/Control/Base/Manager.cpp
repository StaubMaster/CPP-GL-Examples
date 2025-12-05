#include "Manager.hpp"
#include "../Window.hpp"

#include "DataInclude.hpp"

#include "OpenGL/openGL.h"
#include <iostream>



UI::Control::Manager::Manager(const DirectoryContext & dir) :
	Shader(dir),
	BufferArray(),
	Main_Data_Container(),
	Inst_Data_Container(),
	ViewPortSize(),
	Window(new UI::Control::Window(*this))
{
	std::cout << "  ++++  " << "Manager()" << "\n";

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

	delete Window;
}



void UI::Control::Manager::Draw()
{
	if (!Inst_Data_Container.IsCompact())
	{
		Inst_Data_Container.CompactHere();
	}

	BufferArray.Use();

	BufferArray.Main.BindData(GL_ARRAY_BUFFER, 0,
		sizeof(UI::Control::Main_Data) * Main_Data_Container.Count(),
		Main_Data_Container.Data(), GL_STREAM_DRAW);
	BufferArray.Main.Count = Main_Data_Container.Count();

	BufferArray.Inst.BindData(GL_ARRAY_BUFFER, 0,
		sizeof(UI::Control::Inst_Data) * Inst_Data_Container.Count(),
		Inst_Data_Container.Data(), GL_STREAM_DRAW);
	BufferArray.Inst.Count = Inst_Data_Container.Count();

	Shader.Use();
	BufferArray.Use();
	BufferArray.Draw();
}


void UI::Control::Manager::UpdateSize(Point2D size)
{
	ViewPortSize = size;
	Window -> UpdateBox(AxisBox2D(Point2D(), size));
}
void UI::Control::Manager::UpdateMouse(Point2D mouse)
{
	UI::Control::Base * control = Window -> CheckHover(mouse);

	if (control != Hovering)
	{
		if (Hovering != NULL)
		{
			//	Hover Leave
		}
		if (control != NULL)
		{
			//	Hover Enter
		}
		Hovering = control;
	}
	if (Hovering != NULL)
	{
		//	Hover Over
	}
}





void UI::Control::Manager::Click(unsigned char action, unsigned char code)
{
	if (Hovering != NULL)
	{
		Hovering -> Click(code, action);
	}
	Selected = Hovering;
}
void UI::Control::Manager::Key(int key, int scancode, int action, int mods)
{
	if (Selected != NULL)
	{
		Selected -> Key(key, scancode, action, mods);
	}
}
void UI::Control::Manager::DoText(unsigned int codepoint)
{
	if (Selected != NULL)
	{
		Selected -> DoText(codepoint);
	}
}
