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
static void MakeText(const char * str
	, AxisBox2D bound, Point2D pos
	, UI::Text::Alignment textX, UI::Text::Alignment textY
	, UI::Text::Alignment charX, UI::Text::Alignment charY
)
{
	UI::Text::Object	text;
	text.Create();
	text.String() = str;
	text.Bound() = bound;
	text.TextPosition() = pos;
	text.TextAlignmentX() = textX;
	text.TextAlignmentY() = textY;
	text.CharacterAlignmentX() = charX;
	text.CharacterAlignmentY() = charY;
}
void ContextTestTextAlignment::Frame(FrameTime frame_time)
{
	AxisBox2D bound(Point2D(), window.Size.Buffer.Full);

	MakeText("Top\nLeft", bound
		, Point2D(0, 0)
		, UI::Text::Alignment::Min, UI::Text::Alignment::Min
		, UI::Text::Alignment::Max, UI::Text::Alignment::Max
	);
	MakeText("Top\nMiddle", bound
		, Point2D(window.Size.Buffer.Half.X, 0)
		, UI::Text::Alignment::Mid, UI::Text::Alignment::Min
		, UI::Text::Alignment::Mid, UI::Text::Alignment::Max
	);
	MakeText("Top\nRight", bound
		, Point2D(window.Size.Buffer.Full.X, 0)
		, UI::Text::Alignment::Max, UI::Text::Alignment::Min
		, UI::Text::Alignment::Min, UI::Text::Alignment::Max
	);

	MakeText("Middle\nLeft", bound
		, Point2D(0, window.Size.Buffer.Half.Y)
		, UI::Text::Alignment::Min, UI::Text::Alignment::Mid
		, UI::Text::Alignment::Max, UI::Text::Alignment::Mid
	);
	MakeText("Middle\nMiddle", bound
		, Point2D(window.Size.Buffer.Half.X, window.Size.Buffer.Half.Y)
		, UI::Text::Alignment::Mid, UI::Text::Alignment::Mid
		, UI::Text::Alignment::Mid, UI::Text::Alignment::Mid
	);
	MakeText("Middle\nRight", bound
		, Point2D(window.Size.Buffer.Full.X, window.Size.Buffer.Half.Y)
		, UI::Text::Alignment::Max, UI::Text::Alignment::Mid
		, UI::Text::Alignment::Min, UI::Text::Alignment::Mid
	);

	MakeText("Bottom\nLeft", bound
		, Point2D(0, window.Size.Buffer.Full.Y)
		, UI::Text::Alignment::Min, UI::Text::Alignment::Max
		, UI::Text::Alignment::Max, UI::Text::Alignment::Min
	);
	MakeText("Bottom\nMiddle", bound
		, Point2D(window.Size.Buffer.Half.X, window.Size.Buffer.Full.Y)
		, UI::Text::Alignment::Mid, UI::Text::Alignment::Max
		, UI::Text::Alignment::Mid, UI::Text::Alignment::Min
	);
	MakeText("Bottom\nRight", bound
		, Point2D(window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y)
		, UI::Text::Alignment::Max, UI::Text::Alignment::Max
		, UI::Text::Alignment::Min, UI::Text::Alignment::Min
	);

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
