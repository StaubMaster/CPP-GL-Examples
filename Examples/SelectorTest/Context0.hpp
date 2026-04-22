#ifndef  CONTEXT_0_BASE_HPP
# define CONTEXT_0_BASE_HPP

# include "ContextBase.hpp"

#include "Control/Base/Manager.hpp"
#include "ControlsInclude.hpp"

#include "Text/Manager.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"

struct TestMenu0 : public UI::Control::Form
{
	UI::Control::TextBox	TitleText;

	UI::Control::TextBox	QuitText;
	UI::Control::Button		QuitButton;

	UI::Control::TextBox	Context0Text;
	UI::Control::Button		Context0Button;

	UI::Control::TextBox	Context1Text;
	UI::Control::Button		Context1Button;

	~TestMenu0() { }
	TestMenu0()
		: UI::Control::Form()
		, TitleText()
		, QuitText()
		, QuitButton()
		, Context0Text()
		, Context0Button()
		, Context1Text()
		, Context1Button()
	{
		float x = 0.0f;
		float y = 0.0f;

		QuitText.Anchor.X.AnchorMin(0.0f, 200);
		QuitText.Anchor.Y.AnchorMax(0.0f);
		QuitText.SetText("Quit");
		x = QuitText.Anchor.X.GetMinSize();
		QuitButton.Anchor.X.AnchorMin(x);
		QuitButton.Anchor.Y.AnchorMax(0.0f);
		QuitButton.ClickFunc.Assign(this, &TestMenu0::QuitFunc);

		TitleText.Anchor.X.AnchorBoth(0, 0);
		TitleText.Anchor.Y.AnchorMin(y);
		TitleText.SetText("This is Context0");
		y = TitleText.Anchor.Y.GetMinSize();

		Context0Text.Anchor.X.AnchorMin(0.0f, 200);
		Context0Text.Anchor.Y.AnchorMin(y);
		x = Context0Text.Anchor.X.GetMinSize();
		Context0Text.SetText("Context0");
		Context0Button.Anchor.X.AnchorMin(x);
		Context0Button.Anchor.Y.AnchorMin(y);
		Context0Button.ClickFunc.Assign(this, &TestMenu0::Context0Func);
		y = Context0Text.Anchor.Y.GetMinSize();

		Context1Text.Anchor.X.AnchorMin(0.0f, 200);
		Context1Text.Anchor.Y.AnchorMin(y);
		x = Context1Text.Anchor.X.GetMinSize();
		Context1Text.SetText("Context1");
		Context1Button.Anchor.X.AnchorMin(x);
		Context1Button.Anchor.Y.AnchorMin(y);
		Context1Button.ClickFunc.Assign(this, &TestMenu0::Context1Func);
		y = Context1Text.Anchor.Y.GetMinSize();

		ChildInsert(TitleText);
		ChildInsert(QuitText);
		ChildInsert(QuitButton);
		ChildInsert(Context0Text);
		ChildInsert(Context0Button);
		ChildInsert(Context1Text);
		ChildInsert(Context1Button);
	}

	void QuitFunc(ClickArgs args)
	{
		if (args.Action == Action::Press)
		{
			QuitContext();
		}
	}
	void Context0Func(ClickArgs args)
	{
		if (args.Action == Action::Press)
		{
			ChangeToContext0();
		}
	}
	void Context1Func(ClickArgs args)
	{
		if (args.Action == Action::Press)
		{
			ChangeToContext1();
		}
	}
};

struct Context0 : public ContextBase
{
UI::Control::Manager	ControlManager;
UI::Text::Manager		TextManager;

TestMenu0				Menu;

~Context0() { }
Context0(::Window & window)
	: ContextBase(window)
	, ControlManager()
	, TextManager()
	, Menu()
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
}

void Make()
{
	ControlManager.Window.ChildInsert(Menu);
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

	Make();
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