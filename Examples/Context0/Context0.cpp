#include "Context0.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



Context0::~Context0() { }
Context0::Context0()
	: ContextBase()
	, ControlManager(window.glfw_window)
	, TextManager()
	, Menu()
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
}

void Context0::Make()
{
	ControlManager.WindowControl.ChildInsert(Menu);
}

void Context0::Init()
{
	window.DefaultColor = ColorF4(0, 0, 0);
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.frag")),
		});
		ControlManager.Shader.Change(code);
	}
	{
		ControlManager.BufferLayoutMain.Pos.Change(0);
		ControlManager.BufferLayoutInst.Min.Change(1);
		ControlManager.BufferLayoutInst.Max.Change(2);
		ControlManager.BufferLayoutInst.Layer.Change(3);
		ControlManager.BufferLayoutInst.Col.Change(4);
		ControlManager.Buffer.MainBuffer.AttributeLayout = &ControlManager.BufferLayoutMain;
		ControlManager.Buffer.InstBuffer.AttributeLayout = &ControlManager.BufferLayoutInst;
	}
	{
		ControlManager.WindowControl.ChangeManager(&ControlManager);
		ControlManager.WindowControl.ChangeManager(&TextManager);
	}
	TextManager.InitMedia(MediaDirectory);
	TextManager.TextFont = UI::Text::Font::Parse(
		MediaDirectory.File("Text/Font0.atlas")
	);

	ControlManager.GraphicsCreate();
	TextManager.GraphicsCreate();
	TextManager.InitFont();

	Make();
}
void Context0::Free()
{
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
}

void Context0::Resize(DisplaySize display_size)
{
	TextManager.ShaderLayout.DisplaySize.Put(display_size);
	ControlManager.ShaderLayout.DisplaySize.Put(display_size);
	ControlManager.UpdateSize(display_size);
}
void Context0::Frame(FrameTime frame_time)
{
	(void)frame_time;
	ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
	ControlManager.Draw();
	TextManager.MakeInstances();
	TextManager.Draw();
}

void Context0::MouseScroll(ScrollArgs args) { (void)args; }
void Context0::MouseClick(ClickArgs args) { ControlManager.RelayClick(args); }
void Context0::MouseDrag(DragArgs args) { ControlManager.RelayCursorDrag(args); }
void Context0::KeyBoardKey(KeyArgs args) { (void)args; }



ContextBase * newContext0()
{
	return new Context0();
}
