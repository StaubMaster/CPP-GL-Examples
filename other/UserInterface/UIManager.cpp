#include "UIManager.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"





#include "Image.hpp"



UI::Manager::~Manager()
{ }
UI::Manager::Manager()
	: Window()
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
	GraphManager.MakeCurrent();
//	Window.Show();
}




#include "Control/Form.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "HoverArgs.hpp"
void UI::Manager::MouseMove(MoveArgs args)
{
	(void)args;
	//UpdateMouse(args.Position);
}
void UI::Manager::MouseClick(ClickArgs args)
{
	if (Window.Hovering() != nullptr)
	{
		if (Window.Hovering() -> Hovering() != nullptr)
		{
			Window.Hovering() -> Hovering() -> RelayClick(args);
		}
	}
	Window.SelectedUpdate();
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
	if (Window.Hovering() != nullptr)
	{
		UI::Control::Base * control = dynamic_cast<UI::Control::Base *>(Window.Hovering() -> Hovering());
		while (control != nullptr)
		{
			control -> RelayScroll(args);
			control = control -> Parent;
		}
	}
	if (Window.Selected() != nullptr)
	{
		UI::Control::Base * control = dynamic_cast<UI::Control::Base *>(Window.Selected() -> Selected());
		while (control != nullptr)
		{
			control -> RelayScroll(args);
			control = control -> Parent;
		}
	}
}
void UI::Manager::MouseDrag(DragArgs args)
{
	if (Window.Selected() != nullptr)
		Window.Selected() -> RelayDrag(args);
}
void UI::Manager::KeyBoardKey(KeyArgs args)
{
	if (Window.Selected() != nullptr)
		Window.Selected() -> RelayKey(args);
}
void UI::Manager::KeyBoardText(TextArgs args)
{
	if (Window.Selected() != nullptr)
		Window.Selected() -> RelayText(args);
}



// put this in Window ?
void UI::Manager::UpdateMouse(DisplayPosition display_pos)
{
	Cursor.Position = display_pos.Buffer.Corner;

	// do this in Mouse Move
	Window.HoveringUpdate(display_pos);
}
void UI::Manager::Resize(DisplaySize display_size)
{
	TextManager.Shader.Bind();
	TextManager.ShaderLayout.DisplaySize.Put(display_size);

	ControlManager.Shader.Bind();
	ControlManager.ShaderLayout.DisplaySize.Put(display_size);

	GraphManager.Shader.Bind();
	GraphManager.ShaderLayout.DisplaySize.Put(display_size);

	Window.SizeChange(display_size);
}
void UI::Manager::Update()
{
	Window.Update();
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

	//Window.AssignPointerRecursive(this);
	Window.Manager_ = this;
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

void UI::Manager::GraphicsClear()
{
	ControlManager.InstancesClear();
	TextManager.InstancesClear();
	GraphManager.InstancesClear();
}
void UI::Manager::GraphicsMake()
{
	//ControlManager.InstancesMake();
	TextManager.InstancesMake();
	GraphManager.InstancesMake();
	//Window.DisplayPutRecursive();
	Window.DisplayPut();
}
void UI::Manager::GraphicsDone()
{
	//ControlManager.
	TextManager.InstancesDone();
	//GraphManager
}

void UI::Manager::GraphicsDraw()
{
	GL::Disable(GL::Capability::DepthClamp);
	ControlManager.GraphicsDraw();

	GL::Enable(GL::Capability::DepthClamp);
	TextManager.GraphicsDraw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GraphManager.Draw();
}
