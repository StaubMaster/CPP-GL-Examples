#include "Context1.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



Context1::~Context1() { }
Context1::Context1()
	: ContextBase()
	, ControlManager()
	, TextManager()
	, Menu()
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
}



void Context1::Make()
{
	ControlManager.Window.ChildInsert(Menu);
}

void Context1::Init()
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.frag")),
		});
		ControlManager.Shader.Change(code);
	}
	{
		ControlManager.Buffer.Main.Pos.Change(0);
		ControlManager.Buffer.Inst.Min.Change(1);
		ControlManager.Buffer.Inst.Max.Change(2);
		ControlManager.Buffer.Inst.Layer.Change(3);
		ControlManager.Buffer.Inst.Col.Change(4);
	}
	{
		ControlManager.Window.ChangeManager(&ControlManager);
		ControlManager.Window.ChangeManager(&TextManager);
	}
	TextManager.InitMedia(MediaDirectory);
	TextManager.TextFont = UI::Text::Font::Parse(
		MediaDirectory.File("Text/Font0.atlas")
	);

	ControlManager.GraphicsCreate();
	TextManager.GraphicsCreate();

	Make();
}
void Context1::Free()
{
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
}



void Context1::Resize(DisplaySize display_size)
{
	TextManager.Shader.DisplaySize.Put(display_size);
	ControlManager.Shader.DisplaySize.Put(display_size);
	ControlManager.UpdateSize(display_size);
}
void Context1::Frame(FrameTime frame_time)
{
	(void)frame_time;
	ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
	ControlManager.Window.UpdateEntrys();
	ControlManager.Draw();
	TextManager.Draw();
}



void Context1::MouseScroll(ScrollArgs args) { (void)args; }
void Context1::MouseClick(ClickArgs args) { ControlManager.RelayClick(args); }
void Context1::MouseDrag(DragArgs args) { ControlManager.RelayCursorDrag(args); }
void Context1::KeyBoardKey(KeyArgs args) { (void)args; }
