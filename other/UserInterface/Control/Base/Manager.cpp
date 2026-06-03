#include "Manager.hpp"
#include "ObjectData.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"
#include "../Window.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"

#include "ValueType/_Show.hpp"
#include <iostream>





UI::Control::Manager * UI::Control::Manager::CurrentPointer = nullptr;
UI::Control::Manager & UI::Control::Manager::Current() { return *CurrentPointer; }
bool UI::Control::Manager::CheckCurrent() { return (UI::Control::Manager::CurrentPointer != nullptr); }
void UI::Control::Manager::ClearCurrent() { UI::Control::Manager::CurrentPointer = nullptr; }
bool UI::Control::Manager::IsCurrent() const { return (UI::Control::Manager::CurrentPointer == this); }
void UI::Control::Manager::MakeCurrent() { UI::Control::Manager::CurrentPointer = this; }





#include "Image.hpp"
__attribute__((unused)) static Image CursorImgCross(ColorU4 col_fill, ColorU4 col_edge)
{
	Image img(31, 31);

	unsigned char middle = 15;
	unsigned char neck = 10;
	unsigned char thick = 2;

	LoopU2 loop = img.Loop();
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorI2 rel = VectorI2(u) - ((int)middle);
		VectorI2 abs = rel;
		if (abs.X < 0) { abs.X = -abs.X; }
		if (abs.Y < 0) { abs.Y = -abs.Y; }

		if (abs.X > neck || abs.Y > neck)
		{
			if (abs.X + abs.Y == middle) { img.Pixel(u) = col_edge; }
			if (abs.X + abs.Y < middle) { img.Pixel(u) = col_fill; }
		}
		if (abs.X == neck || abs.Y == neck)
		{
			if (abs.X + abs.Y <= middle) { img.Pixel(u) = col_edge; }
			//if (abs.X < thick || abs.Y < thick) { img.Pixel(u) = col_fill; }
		}
		if (abs.X < neck && abs.Y < neck)
		{
			if (abs.X == thick || abs.Y == thick) { img.Pixel(u) = col_edge; }
			if (abs.X < thick || abs.Y < thick) { img.Pixel(u) = col_fill; }
		}
	}

	return img;
}
__attribute__((unused)) static Image CursorImgResizeH(ColorU4 col_fill, ColorU4 col_edge)
{
	Image img(31, 31);

	unsigned char middle = 15;
	unsigned char neck = 8;
	unsigned char thick = 2;

	LoopU2 loop = img.Loop();
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorI2 rel = VectorI2(u) - ((int)middle);
		VectorI2 abs = rel;
		if (abs.X < 0) { abs.X = -abs.X; }
		if (abs.Y < 0) { abs.Y = -abs.Y; }

		if (abs.X > neck)
		{
			if (abs.X + abs.Y == middle) { img.Pixel(u) = col_edge; }
			if (abs.X + abs.Y < middle) { img.Pixel(u) = col_fill; }
		}
		if (abs.X == neck)
		{
			if (abs.X + abs.Y <= middle) { img.Pixel(u) = col_edge; }
			//if (abs.Y < thick) { img.Pixel(u) = col_fill; }
		}
		if (abs.X < neck)
		{
			if (abs.Y == thick) { img.Pixel(u) = col_edge; }
			if (abs.Y < thick) { img.Pixel(u) = col_fill; }
		}
	}

	return img;
}
__attribute__((unused)) static Image CursorImgResizeV(ColorU4 col_fill, ColorU4 col_edge)
{
	Image img(31, 31);

	unsigned char middle = 15;
	unsigned char neck = 8;
	unsigned char thick = 2;

	LoopU2 loop = img.Loop();
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorI2 rel = VectorI2(u) - ((int)middle);
		VectorI2 abs = rel;
		if (abs.X < 0) { abs.X = -abs.X; }
		if (abs.Y < 0) { abs.Y = -abs.Y; }

		if (abs.Y > neck)
		{
			if (abs.X + abs.Y == middle) { img.Pixel(u) = col_edge; }
			if (abs.X + abs.Y < middle) { img.Pixel(u) = col_fill; }
		}
		if (abs.Y == neck)
		{
			if (abs.X + abs.Y <= middle) { img.Pixel(u) = col_edge; }
			//if (abs.Y < thick) { img.Pixel(u) = col_fill; }
		}
		if (abs.Y < neck)
		{
			if (abs.X == thick) { img.Pixel(u) = col_edge; }
			if (abs.X < thick) { img.Pixel(u) = col_fill; }
		}
	}

	return img;
}
__attribute__((unused)) static Image CursorImgResizeD(ColorU4 col_fill, ColorU4 col_edge)
{
	Image img(31, 31);

	unsigned char middle = 15;
	unsigned char neck = 20;
	unsigned char thick = 2;

	(void)col_fill;
	(void)col_edge;
	(void)neck;
	(void)thick;

	LoopU2 loop = img.Loop();
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorI2 rel = VectorI2(u) - ((int)middle);
		VectorI2 abs = rel;
		if (abs.X < 0) { abs.X = -abs.X; }
		if (abs.Y < 0) { abs.Y = -abs.Y; }

		if (abs.X + abs.Y > neck)
		{
			if (abs.X < middle || abs.Y < middle) { img.Pixel(u) = col_fill; }
			if (abs.X == middle || abs.Y == middle) { img.Pixel(u) = col_edge; }
		}
		if (abs.X + abs.Y == neck)
		{
			if (abs.X < middle || abs.Y < middle) { img.Pixel(u) = col_edge; }
		}
		if (abs.X + abs.Y < neck)
		{
			int diff = 0;
			if (abs.X > abs.Y) { diff = abs.X - abs.Y; }
			if (abs.Y > abs.X) { diff = abs.Y - abs.X; }
			if (diff == thick) { img.Pixel(u) = col_edge; }
			if (diff < thick) { img.Pixel(u) = col_fill; }
		}
	}

	return img;
}
__attribute__((unused)) static Image CursorImgResizeD0(ColorU4 col_fill, ColorU4 col_edge)
{
	Image img(31, 31);

	unsigned char middle = 15;
	unsigned char neck = 20;
	unsigned char thick = 2;

	LoopU2 loop = img.Loop();
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorI2 rel = VectorI2(u) - ((int)middle);
		VectorI2 abs = rel;
		abs.Y = -abs.Y;
		if (abs.X < 0) { abs.X = -abs.X; abs.Y = -abs.Y; }

		if (abs.X + abs.Y > neck)
		{
			if (abs.X < middle || abs.Y < middle) { img.Pixel(u) = col_fill; }
			if (abs.X == middle || abs.Y == middle) { img.Pixel(u) = col_edge; }
		}
		if (abs.X + abs.Y == neck)
		{
			if (abs.X < middle || abs.Y < middle) { img.Pixel(u) = col_edge; }
		}
		if (abs.X + abs.Y < neck)
		{
			int diff = 0;
			if (abs.X > abs.Y) { diff = abs.X - abs.Y; }
			if (abs.Y > abs.X) { diff = abs.Y - abs.X; }
			if (diff == thick) { img.Pixel(u) = col_edge; }
			if (diff < thick) { img.Pixel(u) = col_fill; }
		}
	}

	return img;
}
__attribute__((unused)) static Image CursorImgResizeD1(ColorU4 col_fill, ColorU4 col_edge)
{
	Image img(31, 31);

	unsigned char middle = 15;
	unsigned char neck = 20;
	unsigned char thick = 2;

	LoopU2 loop = img.Loop();
	for (VectorU2 u = loop.Min(); loop.Check(u).All(true); loop.Next(u))
	{
		VectorI2 rel = VectorI2(u) - ((int)middle);
		VectorI2 abs = rel;
		if (abs.X < 0 || abs.Y < 0) { abs.X = -abs.X; abs.Y = -abs.Y; }

		if (abs.X + abs.Y > neck)
		{
			if (abs.X < middle || abs.Y < middle) { img.Pixel(u) = col_fill; }
			if (abs.X == middle || abs.Y == middle) { img.Pixel(u) = col_edge; }
		}
		if (abs.X + abs.Y == neck)
		{
			if (abs.X < middle || abs.Y < middle) { img.Pixel(u) = col_edge; }
		}
		if (abs.X + abs.Y < neck)
		{
			int diff = 0;
			if (abs.X > abs.Y) { diff = abs.X - abs.Y; }
			if (abs.Y > abs.X) { diff = abs.Y - abs.X; }
			if (diff == thick) { img.Pixel(u) = col_edge; }
			if (diff < thick) { img.Pixel(u) = col_fill; }
		}
	}

	return img;
}
GLFWcursor * ImageToCursor(Image img)
{
	GLFWimage glfw_img;
	glfw_img.width = img.W();
	glfw_img.height = img.H();
	glfw_img.pixels = (unsigned char *)img.Data();
	return glfwCreateCursor(&glfw_img, 15, 15);
}
void UI::Control::Manager::CursorsCreate()
{
	ColorU4 col0(0x00, 0x00, 0x00, 0xFF);
	ColorU4 col1(0xFF, 0xFF, 0xFF, 0xFF);

	glfw_cursorResizeH = ImageToCursor(CursorImgResizeH(col1, col0));
	glfw_cursorResizeV = ImageToCursor(CursorImgResizeV(col1, col0));
	glfw_cursorResizeD0 = ImageToCursor(CursorImgResizeD0(col1, col0));
	glfw_cursorResizeD1 = ImageToCursor(CursorImgResizeD1(col1, col0));
	glfw_cursorCross = ImageToCursor(CursorImgCross(col1, col0));
}
void UI::Control::Manager::CursorsDelete()
{
	glfwDestroyCursor(glfw_cursorResizeH);
	glfwDestroyCursor(glfw_cursorResizeV);
	glfwDestroyCursor(glfw_cursorResizeD0);
	glfwDestroyCursor(glfw_cursorResizeD1);
	glfwDestroyCursor(glfw_cursorCross);
}
void UI::Control::Manager::CursorsUseDefault() { glfwSetCursor(glfw_window, nullptr); }
void UI::Control::Manager::CursorsUseResizeH() { glfwSetCursor(glfw_window, glfw_cursorResizeH); }
void UI::Control::Manager::CursorsUseResizeV() { glfwSetCursor(glfw_window, glfw_cursorResizeV); }
void UI::Control::Manager::CursorsUseResizeD0() { glfwSetCursor(glfw_window, glfw_cursorResizeD0); }
void UI::Control::Manager::CursorsUseResizeD1() { glfwSetCursor(glfw_window, glfw_cursorResizeD1); }
void UI::Control::Manager::CursorsUseCross() { glfwSetCursor(glfw_window, glfw_cursorCross); }





UI::Control::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Control::Manager::~Manager()" << "\n";
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}
}
UI::Control::Manager::Manager()
	: Shader()
	, ShaderLayout()
	, Buffer()
	, WindowSize()
	, WindowControl()
	, Hovering(nullptr)
	, Selected(nullptr)
	, glfw_window(nullptr)
	, glfw_cursorResizeH(nullptr)
	, glfw_cursorResizeV(nullptr)
	, glfw_cursorResizeD0(nullptr)
	, glfw_cursorResizeD1(nullptr)
	, glfw_cursorCross(nullptr)
	, GraphicsExist(false)
	, GraphicsNeedInit(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	WindowControl.Show();
}
UI::Control::Manager::Manager(GLFWwindow * glfw_window)
	: Shader()
	, ShaderLayout()
	, Buffer()
	, WindowSize()
	, WindowControl()
	, Hovering(nullptr)
	, Selected(nullptr)
	, glfw_window(glfw_window)
	, glfw_cursorResizeH(nullptr)
	, glfw_cursorResizeV(nullptr)
	, glfw_cursorResizeD0(nullptr)
	, glfw_cursorResizeD1(nullptr)
	, glfw_cursorCross(nullptr)
	, GraphicsExist(false)
	, GraphicsNeedInit(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	WindowControl.Show();
}



UI::Control::ObjectData * UI::Control::Manager::PlaceObject()
{
	ObjectData * obj = new ObjectData();
	ObjectDatas.Insert(obj);
	return obj;
}
UI::Control::ObjectData * UI::Control::Manager::CopyObject(const ObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	ObjectData * ret = PlaceObject();
	*ret = *obj;
	return ret;
}



void UI::Control::Manager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();
	Shader.Create();
	CursorsCreate();

	GraphicsExist = true;

	GraphicsNeedInit = true;
	GraphicsNeedMain = true;
}
void UI::Control::Manager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();
	Shader.Delete();
	CursorsDelete();

	GraphicsExist = false;
}

void UI::Control::Manager::GraphicsInit()
{
	if (!(GraphicsNeedInit && GraphicsExist)) { return; }

	Buffer.MainBuffer.Update();
	Buffer.InstBuffer.Update();

	GraphicsNeedInit = false;
}
void UI::Control::Manager::GraphicsMain()
{
	if (!(GraphicsNeedMain && GraphicsExist)) { return; }

	Container::Binary<Control::Main_Data> data;

	data.Insert(UI::Control::Main_Data(VectorF2(-1, -1)));
	data.Insert(UI::Control::Main_Data(VectorF2(-1, +1)));
	data.Insert(UI::Control::Main_Data(VectorF2(+1, -1)));
	data.Insert(UI::Control::Main_Data(VectorF2(+1, -1)));
	data.Insert(UI::Control::Main_Data(VectorF2(-1, +1)));
	data.Insert(UI::Control::Main_Data(VectorF2(+1, +1)));

	Buffer.MainBuffer.DataFull(data.ToVoid());

	GraphicsNeedMain = false;
}
void UI::Control::Manager::GraphicsInst()
{
	Instances.Clear();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			if (obj.Display)
			{
				PlaceInstance(obj);
			}
			if (obj.Remove)
			{
				ObjectDatas.RemoveAt(i);
				delete &obj;
				i--;
			}
		}
	}
	Buffer.InstBuffer.DataFull(Instances.ToVoid());
}

void UI::Control::Manager::PlaceInstance(const ObjectData & obj)
{
	Inst_Data data;
	data.Min = obj.Box.Min;
	data.Max = obj.Box.Max;
	data.Layer = obj.Layer;
	data.Col = obj.Color;
	Instances.Insert(data);
}



void UI::Control::Manager::Draw()
{
	WindowControl.Update();

	GraphicsInit();
	GraphicsMain();
	GraphicsInst();

	Shader.Bind();
	Buffer.Bind();
	Buffer.Draw();
}



void UI::Control::Manager::UpdateSize(const DisplaySize & window_size)
{
	WindowSize = window_size;
	WindowControl.UpdateWindowSize(WindowSize.Buffer.Full);
}
void UI::Control::Manager::UpdateMouse(VectorF2 mouse)
{
	CursorPosition = mouse;
	UI::Control::Base * control = WindowControl.CheckHover(mouse);

	if (control != Hovering)
	{
		// this is done in this order so that when the Hover Leave function is called
		// the Manager Hovering is no longer that control
		// Control should not access Manager Hovering
		// change/store hovering state internally ?
		// store hovering this and hovering child ?
		// and hovering parent ?
		// or just dont update color until later ?
		UI::Control::Base * temp = Hovering;
		Hovering = control;
		if (temp != nullptr) { temp -> ChangeHover(UI::Control::Base::HoverArgs::Leave); }
		if (Hovering != nullptr) { Hovering -> ChangeHover(UI::Control::Base::HoverArgs::Enter); }
	}
	if (Hovering != nullptr)
	{
		Hovering -> ChangeHover(UI::Control::Base::HoverArgs::Move);
	}
}





void UI::Control::Manager::RelayClick(ClickArgs args)
{
	if (Hovering != nullptr)
	{
		Hovering -> RelayClick(args);
	}
	Selected = Hovering;
}
void UI::Control::Manager::RelayScroll(ScrollArgs args)
{
	// scroll hovering
	// if hovering does not have a scroll
	// scroll selected
	if (Selected != nullptr)
	{
		Selected -> RelayScroll(args);
	}
}
void UI::Control::Manager::RelayCursorDrag(DragArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayCursorDrag(args);
	}
}
void UI::Control::Manager::RelayKey(KeyArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayKey(args);
	}
}
void UI::Control::Manager::RelayText(TextArgs args)
{
	if (Selected != nullptr)
	{
		Selected -> RelayText(args);
	}
}
