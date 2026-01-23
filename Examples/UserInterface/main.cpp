
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "Window.hpp"
#include "UserParameter/MouseInclude.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include "DataShow.hpp"

#include "Miscellaneous/Container/Fixed.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Base.hpp"

#include "Graphics/Attribute/Base/AttributeBase.hpp"
#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/ColorF4.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "Graphics/Texture/Array2D.hpp"



#include "UI/Anchor.hpp"

#include "UI/Control/Base/Manager.hpp"
#include "UI/ControlsInclude.hpp"

#include "UI/Text/Manager.hpp"



DirectoryInfo ShaderDir("../../media/Shaders");
DirectoryInfo ImageDir("../../media/Images");
DirectoryInfo TextDir("../../media/Text");

Window * window;

Multiform::WindowBufferSize2D * Multi_WindowSize;





void click0(UserParameter::Mouse::Click params);
void click1(UserParameter::Mouse::Click params);
void click_toggle_Example(UserParameter::Mouse::Click params);
void click_toggle_Settings(UserParameter::Mouse::Click params);
void slider_changed(float val);

void settings_slider_color_r(float val);
void settings_slider_color_g(float val);
void settings_slider_color_b(float val);



UI::Control::Manager * UI_Control_Manager;
UI::Text::Manager * UI_Text_Manager;

UI::Control::CheckBox * Toggle_CheckBox_Example;
UI::Control::CheckBox * Toggle_CheckBox_Settings;
void UI_Make_Toggles()
{
	UI::Control::Form * form;
	UI::Control::CheckBox * check_box;

	form = new UI::Control::Form();
	form -> Anchor.X.Anchor = ANCHOR_MIN;
	form -> Anchor.Y.Anchor = ANCHOR_NONE;
	form -> Anchor.X.SetPaddedMinDist(0);
	form -> Anchor.X.SetSize(60);
	form -> Anchor.Y.SetSize(360);
	UI_Control_Manager -> Window -> ChildInsert(form);

	float h = 0;

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	check_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	check_box -> Anchor.X.SetPaddedMinDist(0);
	check_box -> Anchor.X.SetPaddedMaxDist(0);
	check_box -> Anchor.Y.SetPaddedMaxDist(h);
	check_box -> ClickFunc = click_toggle_Example;
	form -> ChildInsert(check_box);
	Toggle_CheckBox_Example = check_box;

	h = check_box -> Anchor.Y.GetPaddedMaxSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	check_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	check_box -> Anchor.X.SetPaddedMinDist(0);
	check_box -> Anchor.X.SetPaddedMaxDist(0);
	check_box -> Anchor.Y.SetPaddedMaxDist(h);
	check_box -> ClickFunc = click_toggle_Settings;
	form -> ChildInsert(check_box);
	Toggle_CheckBox_Settings = check_box;

	UI::Control::TextBox * text_box;

	text_box = new UI::Control::TextBox(*UI_Text_Manager);
	text_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	text_box -> Anchor.Y.Anchor = ANCHOR_MIN;
	text_box -> Anchor.X.SetPaddedMinDist(0);
	text_box -> Anchor.X.SetPaddedMaxDist(0);
	text_box -> Anchor.Y.SetPaddedMinDist(0);
	UI_Control_Manager -> Window -> ChildInsert(text_box);
}

UI::Control::Form * Settings_Form;
UI::Control::TextBox * Settings_TextBox_ColorR;
UI::Control::TextBox * Settings_TextBox_ColorG;
UI::Control::TextBox * Settings_TextBox_ColorB;
void UI_Make_Settings()
{
	UI::Control::Form * form;
	UI::Control::TextBox * text_box;
	UI::Control::Slider * slider;

	form = new UI::Control::Form();
	form -> Anchor.X.Anchor = ANCHOR_MAX;
	form -> Anchor.Y.Anchor = ANCHOR_BOTH;
	form -> Anchor.X.SetSize(240);
	form -> Anchor.Y.SetSize(360);
	UI_Control_Manager -> Window -> ChildInsert(form);
	form -> Hide();
	Settings_Form = form;

	float h = 0;

	text_box = new UI::Control::TextBox(*UI_Text_Manager);
	text_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	text_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	text_box -> Anchor.X.SetPaddedMinDist(0);
	text_box -> Anchor.X.SetPaddedMaxDist(0);
	text_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorR = text_box;

	h = text_box -> Anchor.Y.GetPaddedMaxSize();

	text_box = new UI::Control::TextBox(*UI_Text_Manager);
	text_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	text_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	text_box -> Anchor.X.SetPaddedMinDist(0);
	text_box -> Anchor.X.SetPaddedMaxDist(0);
	text_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorG = text_box;

	h = text_box -> Anchor.Y.GetPaddedMaxSize();

	text_box = new UI::Control::TextBox(*UI_Text_Manager);
	text_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	text_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	text_box -> Anchor.X.SetPaddedMinDist(0);
	text_box -> Anchor.X.SetPaddedMaxDist(0);
	text_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorB = text_box;

	h = text_box -> Anchor.Y.GetPaddedMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.Anchor = ANCHOR_BOTH;
	slider -> Anchor.Y.Anchor = ANCHOR_MAX;
	slider -> Anchor.X.SetPaddedMinDist(0);
	slider -> Anchor.X.SetPaddedMaxDist(0);
	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc = settings_slider_color_r;
	slider -> SliderMin = 0;
	slider -> SliderMax = 255;
	form -> ChildInsert(slider);

	h = slider -> Anchor.Y.GetPaddedMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.Anchor = ANCHOR_BOTH;
	slider -> Anchor.Y.Anchor = ANCHOR_MAX;
	slider -> Anchor.X.SetPaddedMinDist(0);
	slider -> Anchor.X.SetPaddedMaxDist(0);
	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc = settings_slider_color_g;
	slider -> SliderMin = 0;
	slider -> SliderMax = 255;
	form -> ChildInsert(slider);

	h = slider -> Anchor.Y.GetPaddedMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.Anchor = ANCHOR_BOTH;
	slider -> Anchor.Y.Anchor = ANCHOR_MAX;
	slider -> Anchor.X.SetPaddedMinDist(0);
	slider -> Anchor.X.SetPaddedMaxDist(0);
	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc = settings_slider_color_b;
	slider -> SliderMin = 0;
	slider -> SliderMax = 255;
	form -> ChildInsert(slider);
}

UI::Control::Form * Example_Form;
UI::Control::TextBox * Example_TextBox_0;
UI::Control::TextBox * Example_TextBox_1;
UI::Control::TextBox * Example_TextBox_2;
void UI_Make_Example()
{
	UI::Control::Form * form;
	UI::Control::GroupBox * group_box;
	UI::Control::Button * button;
	UI::Control::TextBox * text;
	UI::Control::Slider * slider;
	UI::Control::CheckBox * check_box;

	form = new UI::Control::Form();
	UI_Control_Manager -> Window -> ChildInsert(form);
	form -> Hide();
	Example_Form = form;

	float w = 0;
	float h = 0;

	group_box = new UI::Control::GroupBox();
	group_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	group_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	group_box -> Anchor.X.SetPaddedMinDist(0);
	group_box -> Anchor.X.SetPaddedMaxDist(0);
	group_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(group_box);

	button = new UI::Control::Button();
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> Anchor.X.SetPaddedMinDist(w);
	button -> Anchor.Y.SetPaddedMaxDist(h);
	button -> ClickFunc = click0;
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetPaddedMinSize();

	button = new UI::Control::Button();
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> Anchor.X.SetPaddedMinDist(w);
	button -> Anchor.Y.SetPaddedMaxDist(h);
	button -> ClickFunc = click1;
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetPaddedMinSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.Anchor = ANCHOR_MIN;
	check_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	check_box -> Anchor.X.SetPaddedMinDist(w);
	check_box -> Anchor.Y.SetPaddedMaxDist(h);
	group_box -> ChildInsert(check_box);

	w = 0;
	h = check_box -> Anchor.Y.GetPaddedMaxSize();

	text = new UI::Control::TextBox(*UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_MAX;
	text -> Anchor.X.SetPaddedMinDist(0);
	text -> Anchor.X.SetPaddedMaxDist(0);
	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("Text0");
	group_box -> ChildInsert(text);
	Example_TextBox_0 = text;

	w = 0;
	h = text -> Anchor.Y.GetPaddedMaxSize();

	text = new UI::Control::TextBox(*UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_MAX;
	text -> Anchor.X.SetPaddedMinDist(0);
	text -> Anchor.X.SetPaddedMaxDist(0);
	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("Text1");
	group_box -> ChildInsert(text);
	Example_TextBox_1 = text;

	w = 0;
	h = group_box -> Anchor.Y.GetPaddedMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.Anchor = ANCHOR_MIN;
	slider -> Anchor.Y.Anchor = ANCHOR_MAX;
	slider -> Anchor.X.SetPaddedMinDist(w);
	slider -> Anchor.X.SetSize(200);
	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc = slider_changed;
	form -> ChildInsert(slider);

	w = slider -> Anchor.X.GetPaddedMinSize();

	text = new UI::Control::TextBox(*UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_MAX;
	text -> Anchor.X.SetPaddedMinDist(w);
	text -> Anchor.X.SetPaddedMaxDist(0);
	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("0");
	text -> ReadOnly = true;
	form -> ChildInsert(text);
	Example_TextBox_2 = text;
}

void UI_Make()
{
	std::cout << "UI Make ...\n";

	UI_Make_Toggles();
	UI_Make_Settings();
	UI_Make_Example();

	std::cout << "UI Make done\n";

	UI_Control_Manager -> Window -> Show();
}

void UI_Init()
{
	std::cout << "Control Init ...\n";

	UI_Control_Manager = new UI::Control::Manager(ShaderDir);
	UI_Text_Manager = new UI::Text::Manager(ShaderDir, TextDir);

	UI_Control_Manager -> UpdateSize(window -> Size);

	std::cout << "Control Init done\n";
}
void UI_Free()
{
	std::cout << "Control Free ...\n";

	delete UI_Control_Manager;
	delete UI_Text_Manager;

	std::cout << "Control Free done\n";
}
void UI_Frame()
{
	Point2D mouse = window -> MouseManager.CursorPixelPosition().Absolute;

	UI_Control_Manager -> UpdateMouse(mouse);
	UI_Control_Manager -> Window -> UpdateEntrys();
	UI_Control_Manager -> Draw();

	//UI_Text_Manager -> Draw();
}



void click0(UserParameter::Mouse::Click params)
{
	if (params.Action.IsPress())
	{
		std::cout << "click0\n";
	}
}
void click1(UserParameter::Mouse::Click params)
{
	if (params.Action.IsPress())
	{
		std::cout << "click1\n";
	}
}
void click_toggle_Example(UserParameter::Mouse::Click params)
{
	if (Toggle_CheckBox_Example -> IsChecked())
	{ Example_Form -> Show(); }
	else
	{ Example_Form -> Hide(); }
	(void)params;
}
void click_toggle_Settings(UserParameter::Mouse::Click params)
{
	if (Toggle_CheckBox_Settings -> IsChecked())
	{ Settings_Form -> Show(); }
	else
	{ Settings_Form -> Hide(); }
	(void)params;
}
void slider_changed(float val)
{
	Example_TextBox_2 -> SetText(std::to_string(val));
}

void settings_slider_color_r(float val)
{
	Settings_TextBox_ColorR -> SetText(std::to_string((int)val));
}
void settings_slider_color_g(float val)
{
	Settings_TextBox_ColorG -> SetText(std::to_string((int)val));
}
void settings_slider_color_b(float val)
{
	Settings_TextBox_ColorB -> SetText(std::to_string((int)val));
}



void InitRun()
{
	std::cout << "Init ...\n";

	UI_Init();

	Container::Fixed<Shader::Base *> shaders(2);
	shaders.Insert(&(UI_Control_Manager -> Shader));
	shaders.Insert(&(UI_Text_Manager -> Shader));

	Multi_WindowSize = new Multiform::WindowBufferSize2D("WindowSize");
	Multi_WindowSize -> FindUniforms(shaders);

	UI_Make();

	std::cout << "Init done\n";
}
void FreeRun()
{
	std::cout << "Free ...\n";

	delete Multi_WindowSize;

	UI_Free();

	std::cout << "Free done\n";
}
void Frame(double timeDelta)
{
	(void)timeDelta;

	UI_Frame();
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	Multi_WindowSize -> ChangeData(WindowSize);
	UI_Control_Manager -> UpdateSize(WindowSize);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(window->DefaultColor.R, window->DefaultColor.G, window->DefaultColor.B, 1.0f);
	//Frame(0);
	//glfwSwapBuffers(window->win);
}

void ClickFunc(UserParameter::Mouse::Click params)
{
	UI_Control_Manager -> RelayClick(params);
}
void ScrollFunc(UserParameter::Mouse::Scroll params)
{
	std::cout << "Scroll " << params.X << ' ' << params.Y << '\n';
	(void)params;
}
void MoveFunc(UserParameter::Mouse::Position params)
{
	//std::cout << "Move " << params.Absolute << '\n';
	(void)params;
}
void DragFunc(UserParameter::Mouse::Drag params)
{
	UI_Control_Manager -> RelayCursorDrag(params);
}

void KeyFunc(UserParameter::KeyBoard::Key params)
{
	UI_Control_Manager -> RelayKey(params);
}
void TextFunc(UserParameter::KeyBoard::Text params)
{
	UI_Control_Manager -> RelayText(params);
}



int main()
{
	Debug::NewFileInDir(DirectoryInfo("logs/"));

	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	window = new Window();
	window -> InitFunc = InitRun;
	window -> FrameFunc = Frame;
	window -> FreeFunc = FreeRun;

	window -> ResizeFunc = Resize;

	window -> ChangeCallback_CursorClick(ClickFunc);
	window -> ChangeCallback_CursorScroll(ScrollFunc);
	window -> ChangeCallback_CursorMove(MoveFunc);
	window -> ChangeCallback_CursorDrag(DragFunc);

	window -> KeyFunc = KeyFunc;
	window -> TextFunc = TextFunc;

	//window -> DefaultColor = ColorF4(0.875f, 0.875f, 0.875f);
	window -> DefaultColor = ColorF4(0.5f, 0.5f, 0.5f);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete window;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
