#include "Manager.hpp"

#include "DataInclude.hpp"

#include "OpenGL/openGL.h"
#include <iostream>



UI::Control::Manager::Manager(const DirectoryContext & dir) :
	Shader(dir),
	BufferArray(),
	Main_Data_Container(),
	Inst_Data_Container(),
	ViewPortSize()
{
	std::cout << "  ++++  " << "Manager()" << "\n";

	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Control::Main_Data(Point2D(+1, +1)));

	Hovering = NULL;
	Selected = NULL;
}
UI::Control::Manager::~Manager()
{
	std::cout << "  ----  " << "~Manager()" << "\n";
}



void UI::Control::Manager::BufferUpdate()
{
	if (!Inst_Data_Container.IsCompact())
	{
		Inst_Data_Container.CompactHere();
	}

	BufferArray.Use();
	BufferArray.Main.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI::Control::Main_Data) * Main_Data_Container.Count(), Main_Data_Container.Data(), GL_STREAM_DRAW);
	BufferArray.Inst.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI::Control::Inst_Data) * Inst_Data_Container.Count(), Inst_Data_Container.Data(), GL_STREAM_DRAW);
	BufferArray.Main.Count = Main_Data_Container.Count();
	BufferArray.Inst.Count = Inst_Data_Container.Count();
}
void UI::Control::Manager::BufferDraw()
{
	BufferArray.Use();
	BufferArray.Draw();
}



void UI::Control::Manager::ChangeHover(Base * control)
{
	if (Hovering != NULL)
	{
		//	change Hovering Color to DefaultColor
		Hovering = NULL;
	}
	if (control != NULL)
	{
		//	change Hovering Color to HoverColor
		Hovering = control;
	}
}
void UI::Control::Manager::Click(unsigned char clickType, unsigned char clickButton)
{
	if (Hovering != NULL)
	{
		if (Hovering -> ClickFunc != NULL)
		{
			Hovering -> ClickFunc(clickType, clickButton);
		}
	}
	Selected = Hovering;
}
