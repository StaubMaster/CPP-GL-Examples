
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"

#include "DataShow.hpp"
#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/Buffer/BaseBufferArray.hpp"
#include "Graphics/Buffer/BaseBuffer.hpp"

#include "Graphics/Attribute/Base/AttributeBase.hpp"
#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/Color.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "Graphics/Texture/2DArray.hpp"



#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "UI/Control/Base/Manager.hpp"
#include "UI/Controls.hpp"

#include "UI/Text/Manager.hpp"



DirectoryContext ShaderDir("./media/Shaders");
DirectoryContext ImageDir("./media/Images");

Window * window;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;





void click0(UI::Parameter::Click params);
void click1(UI::Parameter::Click params);
void click_toggle_MainForm(UI::Parameter::Click params);
void slider_changed(float val);



UI::Control::Manager * UI_Control_Manager;
UI::Text::Manager * UI_Text_Manager;

UI::Control::Form * MainForm;
UI::Control::TextBox * TextControl0;
UI::Control::TextBox * TextControl1;

void UI_Init()
{
	std::cout << "Control Init ...\n";

	UI_Control_Manager = new UI::Control::Manager(ShaderDir);
	UI_Text_Manager = new UI::Text::Manager(ShaderDir, ImageDir);

	std::cout << "Control Init done\n";
}
void UI_Free()
{
	std::cout << "Control Free ...\n";

	delete UI_Control_Manager;
	delete UI_Text_Manager;

	std::cout << "Control Free done\n";
}
void UI_Make()
{
	std::cout << "UI Make ...\n";

	UI::Control::Form * form;
	UI::Control::Button * button;
	UI::Control::TextBox * text;
	UI::Control::Slider * slider;
	UI::Control::CheckBox * check_box;

	form = new UI::Control::Form(*UI_Control_Manager);
	UI_Control_Manager -> Window -> Children.Insert(form);
	MainForm = form;

	check_box = new UI::Control::CheckBox(*UI_Control_Manager);
	check_box -> Anchor.X.Anchor = ANCHOR_MIN;
	check_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	form -> Children.Insert(check_box);

	button = new UI::Control::Button(*UI_Control_Manager);
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MIN;
	button -> ClickFunc = click0;
	form -> Children.Insert(button);

	button = new UI::Control::Button(*UI_Control_Manager);
	button -> Anchor.X.Anchor = ANCHOR_MAX;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> ClickFunc = click1;
	form -> Children.Insert(button);

	text = new UI::Control::TextBox(*UI_Control_Manager, *UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_NONE;
	text -> PixelSize = Point2D(60, 30);
	text -> NormalCenter = Point2D(0.5, 0.5 - 0.05);
	form -> Children.Insert(text);
	TextControl0 = text;
	TextControl0 -> SetText("Text0");

	text = new UI::Control::TextBox(*UI_Control_Manager, *UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_NONE;
	text -> PixelSize = Point2D(60, 30);
	text -> NormalCenter = Point2D(0.5, 0.5 + 0.05);
	form -> Children.Insert(text);
	TextControl1 = text;
	TextControl1 -> SetText("Text1");

	slider = new UI::Control::Slider(*UI_Control_Manager);
	slider -> Anchor.X.Anchor = ANCHOR_BOTH;
	slider -> Anchor.Y.Anchor = ANCHOR_NONE;
	slider -> PixelSize = Point2D(60, 30);
	slider -> NormalCenter = Point2D(0.5, 0.5 + 0.15);
	slider -> ValueChangedFunc = slider_changed;
	form -> Children.Insert(slider);

	form = new UI::Control::Form(*UI_Control_Manager);
	form -> Anchor.X.Anchor = ANCHOR_MIN;
	form -> Anchor.Y.Anchor = ANCHOR_NONE;
	form -> PixelSize = Point2D(60, 360);
	form -> NormalCenter = Point2D(0, 0.5);
	UI_Control_Manager -> Window -> Children.Insert(form);

	button = new UI::Control::Button(*UI_Control_Manager);
	button -> Anchor.X.Anchor = ANCHOR_BOTH;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> ClickFunc = click_toggle_MainForm;
	form -> Children.Insert(button);

	form = new UI::Control::Form(*UI_Control_Manager);
	form -> Anchor.X.Anchor = ANCHOR_MAX;
	form -> Anchor.Y.Anchor = ANCHOR_BOTH;
	form -> PixelSize = Point2D(60, 360);
	form -> NormalCenter = Point2D(0, 0);
	UI_Control_Manager -> Window -> Children.Insert(form);

	std::cout << "UI Make done\n";

	UI_Control_Manager -> Window -> Show();
}
void UI_Frame()
{
	UI_Control_Manager -> UpdateSize(window -> ViewPortSizeRatio.Size);

	Point2D mouse = window -> CursorPixel();
	mouse.Y = window -> ViewPortSizeRatio.Size.Y - mouse.Y;
	UI_Control_Manager -> UpdateMouse(mouse);

	if (window -> MouseButtons[GLFW_MOUSE_BUTTON_LEFT].State.GetPressed())
	{
		UI::Parameter::Click params;
		params.code = CLICK_BUTTON_L;
		params.action = CLICK_PRESS;
		params.Absolute = mouse;
		UI_Control_Manager -> RelayClick(params);
	}

	UI_Control_Manager -> Window -> UpdateEntrys();

	UI_Control_Manager -> Draw();
	UI_Text_Manager -> Draw();
}



void click0(UI::Parameter::Click params)
{
	std::cout << "click0\n";
	(void)params;
}
void click1(UI::Parameter::Click params)
{
	std::cout << "click1\n";
	(void)params;
}
void click_toggle_MainForm(UI::Parameter::Click params)
{
	(void)params;
	if (MainForm -> Visible)
	{
		MainForm -> Hide();
	}
	else
	{
		MainForm -> Show();
	}
}
void slider_changed(float val)
{
	TextControl0 -> SetText(std::to_string(val));
}



void InitRun()
{
	std::cout << "Init ...\n";

	UI_Init();

	Shader::Base * shaders[2] =
	{
		&(UI_Control_Manager -> Shader),
		&(UI_Text_Manager -> Shader),
	};
	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_ViewPortSizeRatio -> FindUniforms(shaders, 2);

	UI_Make();

	std::cout << "Init done\n";
}
void FreeRun()
{
	std::cout << "Free ...\n";

	delete Multi_ViewPortSizeRatio;

	UI_Free();

	std::cout << "Free done\n";
}
void Frame(double timeDelta)
{
	(void)timeDelta;

	UI_Frame();
}

void Resize(const SizeRatio2D & ViewPortSizeRatio)
{
	Multi_ViewPortSizeRatio -> ChangeData(ViewPortSizeRatio);
	UI_Control_Manager -> ViewPortSize = ViewPortSizeRatio.Size;

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(window->DefaultColor.R, window->DefaultColor.G, window->DefaultColor.B, 1.0f);
	//Frame(0);
	//glfwSwapBuffers(window->win);
}

void KeyFunc(int key, int scancode, int action, int mods)
{
	UI::Parameter::Key params;
	params.key = key;
	params.scancode = scancode;
	params.action = action;
	params.mods = mods;
	UI_Control_Manager -> RelayKey(params);
}
void TextFunc(unsigned int codepoint)
{
	UI::Parameter::Text params;
	params.codepoint = codepoint;
	UI_Control_Manager -> RelayText(params);
}



int main()
{
	Debug::NewFileInDir(DirectoryContext("logs/"));

	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	window = new Window(640, 480);
	window -> InitFunc = InitRun;
	window -> FrameFunc = Frame;
	window -> FreeFunc = FreeRun;

	window -> ResizeFunc = Resize;
	window -> TextFunc = TextFunc;
	window -> KeyFunc = KeyFunc;

	window -> DefaultColor = Color(0.875f, 0.875f, 0.875f);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete window;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
