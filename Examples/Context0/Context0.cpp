#include "Context0.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Miscellaneous/Container/Array.hpp"



Context0::~Context0() { }
Context0::Context0()
	: ContextBase()
	, UIManager()
	, Menu()
{ }

void Context0::Make()
{
	UIManager.WindowControl.ChildInsert(Menu);
}

void Context0::Init()
{
	//window.DefaultColor = ColorF4(0, 0, 0);
	window.DefaultColor = ColorF4(0.5f, 0, 0);

	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	UIManager.GraphicsCreate();

	Make();
}
void Context0::Free()
{
	UIManager.GraphicsDelete();
}

void Context0::Resize(DisplaySize display_size)
{
	UIManager.Resize(display_size);
}



#include "Telemetry/ValueAccumulator.hpp"
#include "Graph/Object.hpp"
#include "Graph/ObjectData.hpp"

static ValueAccumulator<float> Values_FPS_Want(64);
static ValueAccumulator<float> Values_FPS_Have(64);

void Context0::Frame(FrameTime frame_time)
{
	Values_FPS_Want.NewValue(60);
	Values_FPS_Have.NewValue(frame_time.ActualFramesPerSecond);

	{
		UI::Graph::Object obj;
		obj.Create();
		if (obj.Is())
		{
			obj.Box().Min = VectorF2();
			obj.Box().Max = window.Size.Buffer.Full;
			obj.Data -> Values = &Values_FPS_Have;
			obj.Data -> Col = ColorF4(0, 0, 1);
		}
	}

	{
		UI::Graph::Object obj;
		obj.Create();
		if (obj.Is())
		{
			obj.Box().Min = VectorF2();
			obj.Box().Max = window.Size.Buffer.Full;
			obj.Data -> Values = &Values_FPS_Want;
			obj.Data -> Col = ColorF4(0, 0, 0);
		}
	}

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
	UIManager.Draw();
}

void Context0::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void Context0::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void Context0::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void Context0::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void Context0::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void Context0::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }



ContextBase * newContext0()
{
	return new Context0();
}
