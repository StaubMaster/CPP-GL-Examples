#include "TestTextAlignment.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



ContextTestTextAlignment::~ContextTestTextAlignment() { }
ContextTestTextAlignment::ContextTestTextAlignment()
	: ContextBase()
	, ControlManager()
	, TextManager()
{
	ControlManager.MakeCurrent();
	TextManager.MakeCurrent();
}



void ContextTestTextAlignment::Init()
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
void ContextTestTextAlignment::Free()
{
	ControlManager.GraphicsDelete();
	TextManager.GraphicsDelete();
}



void ContextTestTextAlignment::Resize(DisplaySize display_size)
{
	TextManager.Shader.DisplaySize.Put(display_size);
	ControlManager.Shader.DisplaySize.Put(display_size);
	ControlManager.UpdateSize(display_size);
}
/* DisplaySize Functions
	DisplayBound()
	TopLeft...
*/
void ContextTestTextAlignment::Frame(FrameTime frame_time)
{
	AxisBox2D bound(Point2D(), window.Size.Buffer.Full);

	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Top\nLeft";
		text.Bound() = bound;
		text.TextPosition() = Point2D(0, 0);
		text.AlignTopLeft();
		text.Color() = ColorF4(1, 0, 1);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Top\nMiddle";
		text.Bound() = bound;
		text.TextPosition() = Point2D(window.Size.Buffer.Half.X, 0);
		text.AlignTopMiddle();
		text.Color() = ColorF4(0, 1, 0);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Top\nRight";
		text.Bound() = bound;
		text.TextPosition() = Point2D(window.Size.Buffer.Full.X, 0);
		text.AlignTopRight();
		text.Color() = ColorF4(0, 1, 0);
	}

	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Middle\nLeft";
		text.Bound() = bound;
		text.TextPosition() = Point2D(0, window.Size.Buffer.Half.Y);
		text.AlignMiddleLeft();
		text.Color() = ColorF4(1, 0, 1);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Middle\nMiddle";
		text.Bound() = bound;
		text.TextPosition() = Point2D(window.Size.Buffer.Half.X, window.Size.Buffer.Half.Y);
		text.AlignMiddleMiddle();
		text.Color() = ColorF4(0, 1, 0);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Middle\nRight";
		text.Bound() = bound;
		text.TextPosition() = Point2D(window.Size.Buffer.Full.X, window.Size.Buffer.Half.Y);
		text.AlignMiddleRight();
		text.Color() = ColorF4(0, 1, 0);
	}

	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Bottom\nLeft";
		text.Bound() = bound;
		text.TextPosition() = Point2D(0, window.Size.Buffer.Full.Y);
		text.AlignBottomLeft();
		text.Color() = ColorF4(1, 0, 1);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Bottom\nMiddle";
		text.Bound() = bound;
		text.TextPosition() = Point2D(window.Size.Buffer.Half.X, window.Size.Buffer.Full.Y);
		text.AlignBottomMiddle();
		text.Color() = ColorF4(0, 1, 0);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.String() = "Bottom\nRight";
		text.Bound() = bound;
		text.TextPosition() = Point2D(window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y);
		text.AlignBottomRight();
		text.Color() = ColorF4(0, 1, 0);
	}

	(void)frame_time;
	ControlManager.UpdateMouse(window.MouseManager.CursorPosition().Buffer.Corner);
	ControlManager.Window.UpdateEntrys();
	ControlManager.Draw();
	TextManager.Draw();
}



void ContextTestTextAlignment::MouseScroll(ScrollArgs args) { (void)args; }
void ContextTestTextAlignment::MouseClick(ClickArgs args) { ControlManager.RelayClick(args); }
void ContextTestTextAlignment::MouseDrag(DragArgs args) { ControlManager.RelayCursorDrag(args); }
void ContextTestTextAlignment::KeyBoardKey(KeyArgs args) { (void)args; }
