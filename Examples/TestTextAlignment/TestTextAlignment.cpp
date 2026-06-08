#include "TestTextAlignment.hpp"

#include "Text/Object.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"

#include "General/Telemetry/ValueAccumulator.hpp"
#include "General/Telemetry/StopWatch.hpp"
#include "General/UnitToString.hpp"



ContextTestTextAlignment::~ContextTestTextAlignment() { }
ContextTestTextAlignment::ContextTestTextAlignment()
	: ContextBase()
	, UIManager()
{ }



void ContextTestTextAlignment::Init()
{
	window.FrameTime = FrameTime(4096, 1.0f / 0.0f);

	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	UIManager.GraphicsCreate();
}
void ContextTestTextAlignment::Free()
{
	UIManager.GraphicsDelete();
}



static void ShowTimeFreq(std::stringstream & ss, float time, int freq)
{
	ss << ToString(time) << 's' << ' ';
	ss << '(';
	ss << ToString(freq, 4) << "Hz";
	ss << ')';
}
static void ShowTime(std::stringstream & ss, float time)
{
	ss << ToString(time) << 's';
}
static void ShowNameTimeLine(std::stringstream & ss, const char * name, const ValueAccumulator<float> & time)
{
	ss << name << ':';
	ShowTime(ss, time.Min()); ss << ' ';
	ShowTime(ss, time.Average()); ss << ' ';
	ShowTime(ss, time.Max()); ss << '\n';
}

static ValueAccumulator<float>		TimeData_TextMake(64);
static ValueAccumulator<float>		TimeData_TextDraw(64);



void ContextTestTextAlignment::TextAlignment()
{
	BoxF2 bound(VectorF2(), window.Size.Buffer.Full);

	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Top\nLeft";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(0, 0);
		text.AlignTopLeft();
		text.Color() = ColorF4(1, 0, 1);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Top\nMiddle";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(window.Size.Buffer.Half.X, 0);
		text.AlignTopMiddle();
		text.Color() = ColorF4(0, 1, 0);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Top\nRight";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, 0);
		text.AlignTopRight();
		text.Color() = ColorF4(0, 1, 0);
	}

	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Middle\nLeft";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(0, window.Size.Buffer.Half.Y);
		text.AlignMiddleLeft();
		text.Color() = ColorF4(1, 0, 1);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Middle\nMiddle";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(window.Size.Buffer.Half.X, window.Size.Buffer.Half.Y);
		text.AlignMiddleMiddle();
		text.Color() = ColorF4(0, 1, 0);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Middle\nRight";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, window.Size.Buffer.Half.Y);
		text.AlignMiddleRight();
		text.Color() = ColorF4(0, 1, 0);
	}

	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Bottom\nLeft";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(0, window.Size.Buffer.Full.Y);
		text.AlignBottomLeft();
		text.Color() = ColorF4(1, 0, 1);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Bottom\nMiddle";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(window.Size.Buffer.Half.X, window.Size.Buffer.Full.Y);
		text.AlignBottomMiddle();
		text.Color() = ColorF4(0, 1, 0);
	}
	{
		UI::Text::Object	text;
		text.Create();
		text.Text() = "Bottom\nRight";
		text.Bound() = bound;
		text.TextPosition() = VectorF2(window.Size.Buffer.Full.X, window.Size.Buffer.Full.Y);
		text.AlignBottomRight();
		text.Color() = ColorF4(0, 1, 0);
	}
}

static ValueAccumulator<float>		DLTAverageTime(64);
static ValueAccumulator<int>		FPSAverageTime(64);

void ContextTestTextAlignment::Frame(FrameTime frame_time)
{
	if (window.KeyBoardManager[Keys::Escape].State == State::Press)
	{
		ChangeToContext0();
		return;
	}

	UIManager.TextManager.ShowInstancesTime();

	{
		BoxF2 bound(VectorF2(), window.Size.Buffer.Full);

		DLTAverageTime.NewValue(frame_time.ActualFrameTime);
		FPSAverageTime.NewValue(frame_time.ActualFramesPerSecond);

		std::stringstream ss;
		ss << "Frame (" << (int)frame_time.WantedFramesPerSecond << '|' << (int)frame_time.ActualFramesPerSecond << ")Hz\n";
		ss << "Frame (" << frame_time.WantedFrameTime << '|' << frame_time.ActualFrameTime << ")s\n";
		ss << '\n';
		ss << "Min: "; ShowTimeFreq(ss, DLTAverageTime.Min(), FPSAverageTime.Max()); ss << '\n';
		ss << "Avg: "; ShowTimeFreq(ss, DLTAverageTime.Average(), FPSAverageTime.Average()); ss << '\n';
		ss << "Max: "; ShowTimeFreq(ss, DLTAverageTime.Max(), FPSAverageTime.Min()); ss << '\n';
		ss << '\n';

		ss << "TextManager.TextArrayIdx     : " << UIManager.TextManager.TextArrayIdx << '\n';
		ss << "TextManager.Instances.Count(): " << UIManager.TextManager.InstancesArray.Length() << '\n';
		ss << "TextManager.ObjectDatas.Count(): " << UIManager.TextManager.ObjectDatas.Count() << '\n';
		ShowNameTimeLine(ss, "TextMake", TimeData_TextMake);
		ShowNameTimeLine(ss, "TextDraw", TimeData_TextDraw);
		ss << '\n';

		//ss << "MaxUniformLocations" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxUniformLocations) << '\n';
		//ss << "MaxUniformBlockSize" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxUniformBlockSize) << '\n';
		//ss << "MaxUniformBufferBindings" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxUniformBufferBindings) << '\n';

		UI::Text::Object	text;
		text.Create();
		text.Text() = ss.str();
		text.Bound() = bound;
		text.TextPosition() = VectorF2(0, 0);
		text.AlignTopLeft();
		text.Color() = ColorF4(0, 0, 0);
	}

	{
		BoxF2 bound(VectorF2(), window.Size.Buffer.Full);

		UI::Text::Object	text;
		text.Create();
		text.Text() =
"Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\nLorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor\ninvidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\nAt vero eos et accusam et justo duo dolores et ea rebum.\nStet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
		text.Bound() = bound;
		text.TextPosition() = window.Size.Buffer.Half;
		text.AlignMiddleMiddle();
		text.Color() = ColorF4(1, 1, 1);
	}

	StopWatch sw;
	TextAlignment();
	(void)frame_time;

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());

	UIManager.ControlManager.MakeInstances();
	UIManager.ControlManager.Draw();

	sw.Clear(); sw.Start();
	UIManager.TextManager.MakeInstances();
	sw.Stop(); TimeData_TextMake.NewValue(sw.ElapsedTime());

	sw.Clear(); sw.Start();
	UIManager.TextManager.Draw();
	sw.Stop(); TimeData_TextDraw.NewValue(sw.ElapsedTime());
}

void ContextTestTextAlignment::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}
/* DisplaySize Functions
	DisplayBound()
	TopLeft...
*/



void ContextTestTextAlignment::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void ContextTestTextAlignment::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void ContextTestTextAlignment::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void ContextTestTextAlignment::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void ContextTestTextAlignment::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void ContextTestTextAlignment::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
