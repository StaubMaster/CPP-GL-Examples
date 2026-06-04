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
#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"

static GLFWcursor * ImageToCursor(Image img)
{
	for (unsigned int i = 0; i < img.Size().Product(); i++)
	{
		ColorU4 & col = img.Pixel(i);
		if (col.R == 0x7F && col.G == 0x7F && col.B == 0x7F)
		{
			col.A = 0x00;
		}
	}

	GLFWimage glfw_img;
	glfw_img.width = img.W();
	glfw_img.height = img.H();
	glfw_img.pixels = (unsigned char *)img.Data();
	return glfwCreateCursor(&glfw_img, 15, 15);
}

void UI::Control::Manager::CursorsCreate(const DirectoryInfo & dir)
{
	glfw_cursorArrowC = ImageToCursor(dir.File("Images/Cursors/ArrowCross.png").LoadImage());

	glfw_cursorArrowH = ImageToCursor(dir.File("Images/Cursors/ArrowHori.png").LoadImage());
	glfw_cursorArrowV = ImageToCursor(dir.File("Images/Cursors/ArrowVert.png").LoadImage());
	glfw_cursorArrowD0 = ImageToCursor(dir.File("Images/Cursors/ArrowDiag0.png").LoadImage());
	glfw_cursorArrowD1 = ImageToCursor(dir.File("Images/Cursors/ArrowDiag1.png").LoadImage());

	glfw_cursorBoxEdge[0] = ImageToCursor(dir.File("Images/Cursors/BoxEdge0.png").LoadImage());
	glfw_cursorBoxEdge[1] = ImageToCursor(dir.File("Images/Cursors/BoxEdge1.png").LoadImage());
	glfw_cursorBoxEdge[2] = ImageToCursor(dir.File("Images/Cursors/BoxEdge2.png").LoadImage());
	glfw_cursorBoxEdge[3] = ImageToCursor(dir.File("Images/Cursors/BoxEdge3.png").LoadImage());

	glfw_cursorBoxCorn[0] = ImageToCursor(dir.File("Images/Cursors/BoxCorn0.png").LoadImage());
	glfw_cursorBoxCorn[1] = ImageToCursor(dir.File("Images/Cursors/BoxCorn1.png").LoadImage());
	glfw_cursorBoxCorn[2] = ImageToCursor(dir.File("Images/Cursors/BoxCorn2.png").LoadImage());
	glfw_cursorBoxCorn[3] = ImageToCursor(dir.File("Images/Cursors/BoxCorn3.png").LoadImage());
}
void UI::Control::Manager::CursorsDelete()
{
	glfwDestroyCursor(glfw_cursorArrowC);

	glfwDestroyCursor(glfw_cursorArrowH);
	glfwDestroyCursor(glfw_cursorArrowV);
	glfwDestroyCursor(glfw_cursorArrowD0);
	glfwDestroyCursor(glfw_cursorArrowD1);

	glfwDestroyCursor(glfw_cursorBoxEdge[0]);
	glfwDestroyCursor(glfw_cursorBoxEdge[1]);
	glfwDestroyCursor(glfw_cursorBoxEdge[2]);
	glfwDestroyCursor(glfw_cursorBoxEdge[3]);

	glfwDestroyCursor(glfw_cursorBoxCorn[0]);
	glfwDestroyCursor(glfw_cursorBoxCorn[1]);
	glfwDestroyCursor(glfw_cursorBoxCorn[2]);
	glfwDestroyCursor(glfw_cursorBoxCorn[3]);
}

void UI::Control::Manager::CursorsUseDefault() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, nullptr); } }
void UI::Control::Manager::CursorsUseArrowC()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowC); } }
void UI::Control::Manager::CursorsUseArrowH()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowH); } }
void UI::Control::Manager::CursorsUseArrowV()  { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowV); } }
void UI::Control::Manager::CursorsUseArrowD0() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowD0); } }
void UI::Control::Manager::CursorsUseArrowD1() { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorArrowD1); } }
void UI::Control::Manager::CursorsUseBoxEdge(unsigned char i) { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorBoxEdge[i]); } }
void UI::Control::Manager::CursorsUseBoxCorn(unsigned char i) { if (glfw_window != nullptr) { glfwSetCursor(glfw_window, glfw_cursorBoxCorn[i]); } }





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
	, glfw_cursorArrowC(nullptr)
	, glfw_cursorArrowH(nullptr)
	, glfw_cursorArrowV(nullptr)
	, glfw_cursorArrowD0(nullptr)
	, glfw_cursorArrowD1(nullptr)
	, glfw_cursorBoxEdge{ nullptr, nullptr, nullptr, nullptr }
	, glfw_cursorBoxCorn{ nullptr, nullptr, nullptr, nullptr }
	, GraphicsExist(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	Buffer.MainBuffer.AttributeLayout = &BufferLayoutMain;
	Buffer.InstBuffer.AttributeLayout = &BufferLayoutInst;

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
	, glfw_cursorArrowC(nullptr)
	, glfw_cursorArrowH(nullptr)
	, glfw_cursorArrowV(nullptr)
	, glfw_cursorArrowD0(nullptr)
	, glfw_cursorArrowD1(nullptr)
	, glfw_cursorBoxEdge{ nullptr, nullptr, nullptr, nullptr }
	, glfw_cursorBoxCorn{ nullptr, nullptr, nullptr, nullptr }
	, GraphicsExist(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Control::Manager::Manager()" << "\n";

	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	Buffer.MainBuffer.AttributeLayout = &BufferLayoutMain;
	Buffer.InstBuffer.AttributeLayout = &BufferLayoutInst;

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



void UI::Control::Manager::ChangeMedia(const DirectoryInfo & dir)
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(dir.File("Shaders/UI/Control.vert")),
			Shader::Code(dir.File("Shaders/UI/Control.frag")),
		});
		Shader.Change(code);
	}
	{
		BufferLayoutMain.Pos.Change(0);
		BufferLayoutInst.Min.Change(1);
		BufferLayoutInst.Max.Change(2);
		BufferLayoutInst.Layer.Change(3);
		BufferLayoutInst.Col.Change(4);
	}
}

void UI::Control::Manager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();
	Shader.Create();

	GraphicsExist = true;

	GraphicsNeedMain = true;
}
void UI::Control::Manager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();
	Shader.Delete();

	GraphicsExist = false;
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
	MakeInstances();
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
void UI::Control::Manager::MakeInstances()
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
}



void UI::Control::Manager::Draw()
{
	WindowControl.Update();

	GraphicsMain();
	GraphicsInst();

	Shader.Bind();

	Buffer.Bind();
	Buffer.MainBuffer.Update();
	Buffer.InstBuffer.Update();
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
