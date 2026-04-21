#ifndef  CONTEXT_0_BASE_HPP
# define CONTEXT_0_BASE_HPP

# include "ContextBase.hpp"

#include "Control/Base/Manager.hpp"
#include "ControlsInclude.hpp"

#include "Text/Manager.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"

struct Context0 : public ContextBase
{
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;

~Context0() { }
Context0(::Window & window)
	: ContextBase(window)
	, ControlManager()
	, TextManager()
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
}

void Init() override
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
}
void Free() override
{
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
}

void Resize(DisplaySize display_size) override
{
	TextManager.Shader.DisplaySize.Put(display_size);
	ControlManager.Shader.DisplaySize.Put(display_size);
	ControlManager.UpdateSize(display_size);
}
void Frame(FrameTime frame_time) override
{
	(void)frame_time;
	ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
	ControlManager.Window.UpdateEntrys();
	ControlManager.Draw();
	TextManager.Draw();
}

void MouseScroll(ScrollArgs args) override { (void)args; }
void MouseClick(ClickArgs args) override { ControlManager.RelayClick(args); }
void MouseDrag(DragArgs args) override { ControlManager.RelayCursorDrag(args); }
void KeyBoardKey(KeyArgs args) override { (void)args; }
};

#endif