#include "UIManager.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"





#include "Image.hpp"



UI::Manager::~Manager()
{ }
UI::Manager::Manager()
	: WindowSize()
	, WindowControl()
	, Hovering(nullptr)
	, Selected(nullptr)
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
	GraphManager.MakeCurrent();
	WindowControl.Show();
}





void UI::Manager::MouseMove(MoveArgs args)
{
	(void)args;
}
void UI::Manager::MouseClick(ClickArgs args)
{
	if (Hovering != nullptr)
	{
		Hovering -> RelayClick(args);
	}
	Selected = Hovering;
}
void UI::Manager::MouseScroll(ScrollArgs args)
{
	/*
		try scroll on Hovering
		if no scroll
			try scroll Parent
			loop until scroll or no Parent
		if no Parent
			try scroll Selected
			if no scroll
				try scroll Parent
				loop until scroll or no Parent
	currently no way to determin if have scroll */

	// do loop in Base::RelayScroll
	// no. RelayScroll gets overridden
	// would need a seperate InvokeRelayScroll
	{
		UI::Control::Base * control = Hovering;
		while (control != nullptr)
		{
			control -> RelayScroll(args);
			control = control -> Parent;
		}
	}
	{
		UI::Control::Base * control = Selected;
		while (control != nullptr)
		{
			control -> RelayScroll(args);
			control = control -> Parent;
		}
	}
}
void UI::Manager::MouseDrag(DragArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayDrag(args);
	}
}
void UI::Manager::KeyBoardKey(KeyArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayKey(args);
	}
}
void UI::Manager::KeyBoardText(TextArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayText(args);
	}
}



void UI::Manager::UpdateMouse(DisplayPosition mouse_pos)
{
	Cursor.Position = mouse_pos.Buffer.Corner;
	UI::Control::Base * control = WindowControl.FindHover(mouse_pos.Buffer.Corner);

	if (control != Hovering)
	{
		if (Hovering != nullptr)
		{
			Hovering -> ColorUpdateRequest();
			Hovering -> RelayHover(HoverArgs(HoverType::Leave, mouse_pos));
		}
		Hovering = control;
		if (Hovering != nullptr)
		{
			Hovering -> ColorUpdateRequest();
			Hovering -> RelayHover(HoverArgs(HoverType::Enter, mouse_pos));
		}
	}
	else
	{
		if (Hovering != nullptr)
		{
			Hovering -> RelayHover(HoverArgs(HoverType::Move, mouse_pos));
		}
	}
}
void UI::Manager::Resize(DisplaySize display_size)
{
	TextManager.Shader.Bind();
	TextManager.ShaderLayout.DisplaySize.Put(display_size);

	ControlManager.Shader.Bind();
	ControlManager.ShaderLayout.DisplaySize.Put(display_size);

	GraphManager.Shader.Bind();
	GraphManager.ShaderLayout.DisplaySize.Put(display_size);

	WindowSize = display_size;
	WindowControl.UpdateWindowSize(WindowSize.Buffer.Full);
}
void UI::Manager::Update()
{
	WindowControl.UpdateRecursive();
	WindowControl.DepthUpdateResolve();
}



void UI::Manager::ChangeMedia(const DirectoryInfo & dir, GLFWwindow * glfw_window)
{
	ControlManager.ChangeMedia(dir);

	TextManager.ChangeMedia(dir);
	TextManager.Font = UI::Text::Font::Parse(
		dir.File("Text/Font0.atlas")
	);

	GraphManager.ChangeMedia(dir);

	Cursor.Create(dir, glfw_window);

	WindowControl.ChangeManagerRecursive(this);
}



void UI::Manager::GraphicsCreate()
{
	ControlManager.GraphicsCreate();
	TextManager.GraphicsCreate();
	TextManager.InitFont();
	GraphManager.GraphicsCreate();
}
void UI::Manager::GraphicsDelete()
{
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	GraphManager.GraphicsDelete();
	Cursor.Delete();
}
void UI::Manager::GraphicsInit()
{
	ControlManager.GraphicsInit();
	TextManager.GraphicsInit();
}

void UI::Manager::GraphicsMake()
{
	ControlManager.InstancesClear();
	ControlManager.InstancesMake();
	WindowControl.PutDisplay();

	TextManager.MakeInstances();

	GraphManager.MakeInstances();
}

void UI::Manager::GraphicsDraw()
{
	GL::Disable(GL::Capability::DepthClamp);
	ControlManager.Draw();

	GL::Enable(GL::Capability::DepthClamp);
	TextManager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GraphManager.Draw();
}
