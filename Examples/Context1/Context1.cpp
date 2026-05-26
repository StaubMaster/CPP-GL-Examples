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
	window.KeyBoardManager.CallBack_TextEvent.Assign(this, &Context1::KeyBoardText);
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
		

		ControlManager.LayoutMain.Pos.Change(0);
		ControlManager.LayoutInst.Min.Change(1);
		ControlManager.LayoutInst.Max.Change(2);
		ControlManager.LayoutInst.Layer.Change(3);
		ControlManager.LayoutInst.Col.Change(4);
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
	TextManager.ShaderLayout.DisplaySize.Put(display_size);
	ControlManager.ShaderLayout.DisplaySize.Put(display_size);
	ControlManager.UpdateSize(display_size);
}
void Context1::Frame(FrameTime frame_time)
{
	(void)frame_time;
	ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
//	ControlManager.Window.UpdateEntrys();
	ControlManager.Draw();
	TextManager.Draw();
}



void Context1::MouseClick(ClickArgs args) { ControlManager.RelayClick(args); }
void Context1::MouseDrag(DragArgs args) { ControlManager.RelayCursorDrag(args); }
void Context1::MouseScroll(ScrollArgs args) { ControlManager.RelayScroll(args); }
void Context1::KeyBoardKey(KeyArgs args) { ControlManager.RelayKey(args); }
void Context1::KeyBoardText(TextArgs args) { ControlManager.RelayText(args); }



ContextBase * newContext1()
{
	return new Context1();
}
