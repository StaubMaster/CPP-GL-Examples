// C++
#include <string>
#include <sstream>
#include <iostream>

// General
#include "Window.hpp"
#include "Debug.hpp"
#include "ValueType/_Show.hpp"

#include "Miscellaneous/Function/Object.hpp"
#include "Miscellaneous/Container/Array.hpp"

// FileManager
#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

// 
#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Base.hpp"

#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/ColorF4.hpp"

#include "Graphics/Uniform/_Include.hpp"
#include "Graphics/Multiform/_Include.hpp"

#include "Graphics/Texture/Array2D.hpp"



// UI
#include "Control/Base/Manager.hpp"
#include "Control/Base/Object.hpp"
#include "ControlsInclude.hpp"

#include "Text/Manager.hpp"
#include "Text/Object.hpp"



struct MainContext
{
DirectoryInfo MediaDirectory;

Window window;

UI::Text::Manager		TextManager;
UI::Control::Manager	ControlManager;

~MainContext()
{ }
MainContext()
	: MediaDirectory("../../media")
	, window()
	, TextManager()
	, ControlManager()
{
	TextManager.MakeCurrent();
	ControlManager.MakeCurrent();
}



void TextInit()
{
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Text.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Text.frag")),
		});
		TextManager.Shader.Change(code);
	}
	{
		TextManager.Buffer.Main.Pos.Change(0);
		TextManager.Buffer.Inst.Pos.Change(1);
		TextManager.Buffer.Inst.PalletMin.Change(2);
		TextManager.Buffer.Inst.PalletMax.Change(3);
		TextManager.Buffer.Inst.BoundMin.Change(4);
		TextManager.Buffer.Inst.BoundMax.Change(5);
	}
	{
		TextManager.TextFont = UI::Text::Font::Parse(
			MediaDirectory.File("Text/Font0.atlas")
		);
	}
}
void ControlsInit()
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
}



UI::Control::CheckBox * Toggle_CheckBox_Example;
UI::Control::CheckBox * Toggle_CheckBox_Settings;
void UI_Make_Toggles()
{
	UI::Control::Form * form;
	UI::Control::CheckBox * check_box;
	UI::Control::TextBox * text_box;

	float h = 0;

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMin(0);
	ControlManager.Window.ChildInsert(text_box);

	h = text_box -> Anchor.Y.GetMinSize();

	form = new UI::Control::Form();
	form -> Anchor.X.AnchorMin(0, 60);
	form -> Anchor.Y.AnchorMin(h, 360);
	ControlManager.Window.ChildInsert(form);

	h = 0.0f;

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.AnchorBoth(0, 0);
	check_box -> Anchor.Y.AnchorMax(h);
	check_box -> ClickFunc.Assign(this, &MainContext::click_toggle_Example);
	form -> ChildInsert(check_box);
	Toggle_CheckBox_Example = check_box;

	h = check_box -> Anchor.Y.GetMaxSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.AnchorBoth(0, 0);
	check_box -> Anchor.Y.AnchorMax(h);
	check_box -> ClickFunc.Assign(this, &MainContext::click_toggle_Settings);
	form -> ChildInsert(check_box);
	Toggle_CheckBox_Settings = check_box;
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
	form -> Anchor.X.AnchorMax(0, 240);
	form -> Anchor.Y.AnchorMax(0, 360);
	ControlManager.Window.ChildInsert(form);
	form -> Hide();
	Settings_Form = form;

	float h = 0;

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMax(h);
	text_box -> SetText("0");
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorR = text_box;

	h = text_box -> Anchor.Y.GetMaxSize();

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMax(h);
	text_box -> SetText("0");
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorG = text_box;

	h = text_box -> Anchor.Y.GetMaxSize();

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMax(h);
	text_box -> SetText("0");
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorB = text_box;

	h = text_box -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorBoth(0, 0);
	slider -> Anchor.Y.AnchorMax(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::settings_slider_color_r);
	slider -> ValueMin = 0;
	slider -> ValueMax = 255;
	form -> ChildInsert(slider);

	h = slider -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorBoth(0, 0);
	slider -> Anchor.Y.AnchorMax(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::settings_slider_color_g);
	slider -> ValueMin = 0;
	slider -> ValueMax = 255;
	form -> ChildInsert(slider);

	h = slider -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorBoth(0, 0);
	slider -> Anchor.Y.AnchorMax(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::settings_slider_color_b);
	slider -> ValueMin = 0;
	slider -> ValueMax = 255;
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
	ControlManager.Window.ChildInsert(form);
	form -> Hide();
	Example_Form = form;

	float w = 0; (void)w;
	float h = 0; (void)h;

	group_box = new UI::Control::GroupBox();
	group_box -> Anchor.X.AnchorBoth(0, 0);
	group_box -> Anchor.Y.AnchorMax(h);
	form -> ChildInsert(group_box);

	button = new UI::Control::Button();
	button -> Anchor.X.AnchorMin(w);
	button -> Anchor.Y.AnchorMax(h);
	button -> ClickFunc.Assign(this, &MainContext::click0);
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetMinSize();

	button = new UI::Control::Button();
	button -> Anchor.X.AnchorMin(w);
	button -> Anchor.Y.AnchorMax(h);
	button -> ClickFunc.Assign(this, &MainContext::click1);
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetMinSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.AnchorMin(w);
	check_box -> Anchor.Y.AnchorMax(h);
	group_box -> ChildInsert(check_box);

	w = 0;
	h = check_box -> Anchor.Y.GetMaxSize();

	text = new UI::Control::TextBox();
	text -> Anchor.X.AnchorBoth(0, 0);
	text -> Anchor.Y.AnchorMax(h);
	text -> SetText("Text0");
	group_box -> ChildInsert(text);
	Example_TextBox_0 = text;

	w = 0;
	h = text -> Anchor.Y.GetMaxSize();

	text = new UI::Control::TextBox();
	text -> Anchor.X.AnchorBoth(0, 0);
	text -> Anchor.Y.AnchorMax(h);
	text -> SetText("Text1");
	group_box -> ChildInsert(text);
	Example_TextBox_1 = text;

	w = 0;
	h = group_box -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorMin(w, 200);
	slider -> Anchor.Y.AnchorMax(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::slider_changed);
	form -> ChildInsert(slider);

	w = slider -> Anchor.X.GetMinSize();

	text = new UI::Control::TextBox();
	text -> Anchor.X.AnchorBoth(w, 0);
	text -> Anchor.Y.AnchorMax(h);
	text -> SetText("0");
	text -> ReadOnly = true;
	form -> ChildInsert(text);
	Example_TextBox_2 = text;
}



void click0(ClickArgs params)
{
	if (params.Action == Action::Press)
	{
		std::cout << "click0\n";
	}
}
void click1(ClickArgs params)
{
	if (params.Action == Action::Press)
	{
		std::cout << "click1\n";
	}
}
void slider_changed(float val)
{
	Example_TextBox_2 -> SetText(std::to_string(val));
}

void click_toggle_Example(ClickArgs args)
{
	if (Toggle_CheckBox_Example -> IsChecked())
	{ Example_Form -> Show(); }
	else
	{ Example_Form -> Hide(); }
	(void)args;
}
void click_toggle_Settings(ClickArgs args)
{
	if (Toggle_CheckBox_Settings -> IsChecked())
	{ Settings_Form -> Show(); }
	else
	{ Settings_Form -> Hide(); }
	(void)args;
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
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	std::cout << "Init ...\n";

	TextInit();
	ControlsInit();

	TextManager.GraphicsCreate();
	ControlManager.GraphicsCreate();

	std::cout << "Init done\n";

	UI_Make_Toggles();
	UI_Make_Settings();
	UI_Make_Example();
}
void FreeRun()
{
	std::cout << "Free ...\n";

	TextManager.GraphicsDelete();
	ControlManager.GraphicsDelete();

	std::cout << "Free done\n";
}

void ShowText(const char * text)
{
	UI::Text::Object obj;
	obj.String() = text;
	obj.Pos() = window.Size.Buffer.Half;
	obj.Bound() = AxisBox2D(Point2D(), window.Size.Buffer.Full);
}
void ShowAlphabet()
{
	UI::Text::Object obj;
	obj.Create();

	obj.Pos() = window.Size.Buffer.Half;
	obj.Bound() = AxisBox2D(Point2D(), window.Size.Buffer.Full);

	obj.AlignmentX() = UI::Text::Alignment::Min;
	obj.AlignmentY() = UI::Text::Alignment::Min;

	obj.String() = "0123456789\n";
	obj.String() += "abcdefghijklm\n";
	obj.String() += "nopqrstuvwxyz\n";
	obj.String() += "ABCDEFGHIJKLM\n";
	obj.String() += "NOPQRSTUVWXYZ\n";
	obj.String() += "<>";
}

void Frame(double timeDelta)
{
	{
		UI::Text::Object obj;
		obj.Create();

		obj.Pos().X = window.Size.Window.Full.X - 10;
		obj.Pos().Y = 0 + 10;
		obj.Bound() = AxisBox2D(Point2D(), window.Size.Buffer.Full);
		obj.AlignmentX() = UI::Text::Alignment::Max;
		obj.AlignmentY() = UI::Text::Alignment::Min;

		std::stringstream ss;
		ss << timeDelta;
		ss << '\n';
		ss << ((int)(1.0 / timeDelta));
		obj.String() = ss.str();
	}
	(void)timeDelta;

	{
		UI::Control::Object obj;
		obj.Create();
		obj.Box().Min = window.Size.Buffer.Half - Point2D(20, 20);
		obj.Box().Max = window.Size.Buffer.Half + Point2D(20, 20);
		obj.Color() = ColorF4(1, 0, 1);
	}

	//ShowText("test asd Text");
	//ShowAlphabet();
	//ShowAllCharacters();

	{
		Point2D mouse = window.MouseManager.CursorPosition().Buffer.Corner;
		ControlManager.UpdateMouse(mouse);
		ControlManager.Window.UpdateEntrys();
		ControlManager.Draw();
	}
	TextManager.Draw();
}



void Resize(const ::DisplaySize & DisplaySize)
{
	TextManager.Shader.DisplaySize.Put(DisplaySize);

	ControlManager.UpdateSize(DisplaySize);
	ControlManager.Shader.DisplaySize.Put(DisplaySize);
}

void ClickFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		ControlManager.RelayClick(args);
	}
}
void ScrollFunc(ScrollArgs args)
{
	//std::cout << "Scroll " << params.X << ' ' << params.Y << '\n';
	(void)args;
}
void MoveFunc(MoveArgs args)
{
	//std::cout << "Move " << params.Absolute << '\n';
	(void)args;
}
void DragFunc(DragArgs args)
{
	ControlManager.RelayCursorDrag(args);
}

void KeyFunc(KeyArgs args)
{
	ControlManager.RelayKey(args);
}
void TextFunc(TextArgs args)
{
	ControlManager.RelayText(args);
}



int Main()
{
	window.InitCallBack.Assign(this, &MainContext::InitRun);
	window.FreeCallBack.Assign(this, &MainContext::FreeRun);
	window.FrameCallBack.Assign(this, &MainContext::Frame);
	window.ResizeCallBack.Assign(this, &MainContext::Resize);

	window.KeyBoardManager.CallBack_KeyEvent.Assign(this, &MainContext::KeyFunc);
	window.KeyBoardManager.CallBack_TextEvent.Assign(this, &MainContext::TextFunc);

	window.MouseManager.Callback_ClickEvent.Assign(this, &MainContext::ClickFunc);
	window.MouseManager.Callback_ScrollEvent.Assign(this, &MainContext::ScrollFunc);
	window.MouseManager.Callback_MoveEvent.Assign(this, &MainContext::MoveFunc);
	window.MouseManager.Callback_DragEvent.Assign(this, &MainContext::DragFunc);

	window.DefaultColor = ColorF4(0.875f, 0.875f, 0.875f);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
};



int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			MainContext context;
			ret = context.Main();
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	glfwTerminate();
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
