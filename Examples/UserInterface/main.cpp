// C++
#include <string>
#include <sstream>
#include <iostream>

// General
#include "Debug.hpp"
#include "Window.hpp"
#include "Miscellaneous/Function/Object.hpp"
#include "ValueType/_Show.hpp"

// FileManager
#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

// 
#include "Miscellaneous/Container/Fixed.hpp"

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
#include "ControlsInclude.hpp"

#include "Text/Manager.hpp"
#include "Text/Object.hpp"
#include "Text/ObjectData.hpp"



struct MainContext
{
DirectoryInfo ShaderDir;
DirectoryInfo ImageDir;
DirectoryInfo TextDir;

Window window;

UI::Text::Manager UI_Text_Manager;
UI::Control::Manager UI_Control_Manager;

MainContext()
	: ShaderDir("../../media/Shaders")
	, ImageDir("../../media/Images")
	, TextDir("../../media/Text")
	, window()
	, UI_Text_Manager()
	, UI_Control_Manager()
{
	UI_Text_Manager.MakeCurrent();
}
~MainContext()
{ }



void Text_Make()
{
	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("UI/Text.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("UI/Text.frag")));
		UI_Text_Manager.Shader.Change(code);
	}

	{
		UI_Text_Manager.TextFont = UI::Text::Font::Parse(TextDir.File("Font0.atlas"));
		UI_Text_Manager.Pallet_Texture.Create();
		UI_Text_Manager.Pallet_Texture.Bind();
		UI_Text_Manager.Pallet_Texture.Assign(UI_Text_Manager.TextFont -> AtlasTexture);
		UI_Text_Manager.Pallet_Texture.FilterMin(Texture::Base::FilterMinType::Linear);
	}
	UI_Text_Manager.GraphicsCreate();

	UI_Text_Manager.Buffer.Main.Init();
	UI_Text_Manager.Buffer.Inst.Init();
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
//	text_box -> Anchor.X.Anchor = AnchorType::Both;
//	text_box -> Anchor.Y.Anchor = AnchorType::Min;
//	text_box -> Anchor.X.SetPaddedMinDist(0);
//	text_box -> Anchor.X.SetPaddedMaxDist(0);
//	text_box -> Anchor.Y.SetPaddedMinDist(0);
	UI_Control_Manager.Window.ChildInsert(text_box);

	h = text_box -> Anchor.Y.GetMinSize();

	form = new UI::Control::Form();
	form -> Anchor.X.AnchorMin(0, 60);
	form -> Anchor.Y.AnchorMin(h, 360);
//	form -> Anchor.X.Anchor = AnchorType::Min;
//	form -> Anchor.Y.Anchor = AnchorType::None;
//	form -> Anchor.X.SetPaddedMinDist(0);
//	form -> Anchor.X.SetSize(60);
//	form -> Anchor.Y.SetSize(360);
	UI_Control_Manager.Window.ChildInsert(form);

	h = 0.0f;

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.AnchorBoth(0, 0);
	check_box -> Anchor.Y.AnchorMax(h);
//	check_box -> Anchor.X.Anchor = AnchorType::Both;
//	check_box -> Anchor.Y.Anchor = AnchorType::Max;
//	check_box -> Anchor.X.SetPaddedMinDist(0);
//	check_box -> Anchor.X.SetPaddedMaxDist(0);
//	check_box -> Anchor.Y.SetPaddedMaxDist(h);
	check_box -> ClickFunc.Assign(this, &MainContext::click_toggle_Example);
	form -> ChildInsert(check_box);
	Toggle_CheckBox_Example = check_box;

	h = check_box -> Anchor.Y.GetMaxSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.AnchorBoth(0, 0);
	check_box -> Anchor.Y.AnchorMax(h);
//	check_box -> Anchor.X.Anchor = AnchorType::Both;
//	check_box -> Anchor.Y.Anchor = AnchorType::Max;
//	check_box -> Anchor.X.SetPaddedMinDist(0);
//	check_box -> Anchor.X.SetPaddedMaxDist(0);
//	check_box -> Anchor.Y.SetPaddedMaxDist(h);
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
//	form -> Anchor.X.Anchor = AnchorType::Max;
//	form -> Anchor.Y.Anchor = AnchorType::Both;
//	form -> Anchor.X.SetSize(240);
//	form -> Anchor.Y.SetSize(360);
	UI_Control_Manager.Window.ChildInsert(form);
	form -> Hide();
	Settings_Form = form;

	float h = 0;

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMax(h);
//	text_box -> Anchor.X.Anchor = AnchorType::Both;
//	text_box -> Anchor.Y.Anchor = AnchorType::Max;
//	text_box -> Anchor.X.SetPaddedMinDist(0);
//	text_box -> Anchor.X.SetPaddedMaxDist(0);
//	text_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorR = text_box;

	h = text_box -> Anchor.Y.GetMaxSize();

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMax(h);
//	text_box -> Anchor.X.Anchor = AnchorType::Both;
//	text_box -> Anchor.Y.Anchor = AnchorType::Max;
//	text_box -> Anchor.X.SetPaddedMinDist(0);
//	text_box -> Anchor.X.SetPaddedMaxDist(0);
//	text_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorG = text_box;

	h = text_box -> Anchor.Y.GetMaxSize();

	text_box = new UI::Control::TextBox();
	text_box -> Anchor.X.AnchorBoth(0, 0);
	text_box -> Anchor.Y.AnchorMax(h);
//	text_box -> Anchor.X.Anchor = AnchorType::Both;
//	text_box -> Anchor.Y.Anchor = AnchorType::Max;
//	text_box -> Anchor.X.SetPaddedMinDist(0);
//	text_box -> Anchor.X.SetPaddedMaxDist(0);
//	text_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(text_box);
	Settings_TextBox_ColorB = text_box;

	h = text_box -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorBoth(0, 0);
	slider -> Anchor.Y.AnchorMax(h);
//	slider -> Anchor.X.Anchor = AnchorType::Both;
//	slider -> Anchor.Y.Anchor = AnchorType::Max;
//	slider -> Anchor.X.SetPaddedMinDist(0);
//	slider -> Anchor.X.SetPaddedMaxDist(0);
//	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::settings_slider_color_r);
	slider -> ValueMin = 0;
	slider -> ValueMax = 255;
	form -> ChildInsert(slider);

	h = slider -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorBoth(0, 0);
	slider -> Anchor.Y.AnchorMax(h);
//	slider -> Anchor.X.Anchor = AnchorType::Both;
//	slider -> Anchor.Y.Anchor = AnchorType::Max;
//	slider -> Anchor.X.SetPaddedMinDist(0);
//	slider -> Anchor.X.SetPaddedMaxDist(0);
//	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::settings_slider_color_g);
	slider -> ValueMin = 0;
	slider -> ValueMax = 255;
	form -> ChildInsert(slider);

	h = slider -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorBoth(0, 0);
	slider -> Anchor.Y.AnchorMax(h);
//	slider -> Anchor.X.Anchor = AnchorType::Both;
//	slider -> Anchor.Y.Anchor = AnchorType::Max;
//	slider -> Anchor.X.SetPaddedMinDist(0);
//	slider -> Anchor.X.SetPaddedMaxDist(0);
//	slider -> Anchor.Y.SetPaddedMaxDist(h);
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
	UI_Control_Manager.Window.ChildInsert(form);
	form -> Hide();
	Example_Form = form;

	float w = 0; (void)w;
	float h = 0; (void)h;

	group_box = new UI::Control::GroupBox();
	group_box -> Anchor.X.AnchorBoth(0, 0);
	group_box -> Anchor.Y.AnchorMax(h);
//	group_box -> Anchor.X.Anchor = AnchorType::Both;
//	group_box -> Anchor.Y.Anchor = AnchorType::Max;
//	group_box -> Anchor.X.SetPaddedMinDist(0);
//	group_box -> Anchor.X.SetPaddedMaxDist(0);
//	group_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(group_box);

	button = new UI::Control::Button();
	button -> Anchor.X.AnchorMin(w);
	button -> Anchor.Y.AnchorMax(h);
//	button -> Anchor.X.Anchor = AnchorType::Min;
//	button -> Anchor.Y.Anchor = AnchorType::Max;
//	button -> Anchor.X.SetPaddedMinDist(w);
//	button -> Anchor.Y.SetPaddedMaxDist(h);
	button -> ClickFunc.Assign(this, &MainContext::click0);
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetMinSize();

	button = new UI::Control::Button();
	button -> Anchor.X.AnchorMin(w);
	button -> Anchor.Y.AnchorMax(h);
//	button -> Anchor.X.Anchor = AnchorType::Min;
//	button -> Anchor.Y.Anchor = AnchorType::Max;
//	button -> Anchor.X.SetPaddedMinDist(w);
//	button -> Anchor.Y.SetPaddedMaxDist(h);
	button -> ClickFunc.Assign(this, &MainContext::click1);
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetMinSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.AnchorMin(w);
	check_box -> Anchor.Y.AnchorMax(h);
//	check_box -> Anchor.X.Anchor = AnchorType::Min;
//	check_box -> Anchor.Y.Anchor = AnchorType::Max;
//	check_box -> Anchor.X.SetPaddedMinDist(w);
//	check_box -> Anchor.Y.SetPaddedMaxDist(h);
	group_box -> ChildInsert(check_box);

	w = 0;
	h = check_box -> Anchor.Y.GetMaxSize();

	text = new UI::Control::TextBox();
	text -> Anchor.X.AnchorBoth(0, 0);
	text -> Anchor.Y.AnchorMax(h);
//	text -> Anchor.X.Anchor = AnchorType::Both;
//	text -> Anchor.Y.Anchor = AnchorType::Max;
//	text -> Anchor.X.SetPaddedMinDist(0);
//	text -> Anchor.X.SetPaddedMaxDist(0);
//	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("Text0");
	group_box -> ChildInsert(text);
	Example_TextBox_0 = text;

	w = 0;
	h = text -> Anchor.Y.GetMaxSize();

	text = new UI::Control::TextBox();
	text -> Anchor.X.AnchorBoth(0, 0);
	text -> Anchor.Y.AnchorMax(h);
//	text -> Anchor.X.Anchor = AnchorType::Both;
//	text -> Anchor.Y.Anchor = AnchorType::Max;
//	text -> Anchor.X.SetPaddedMinDist(0);
//	text -> Anchor.X.SetPaddedMaxDist(0);
//	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("Text1");
	group_box -> ChildInsert(text);
	Example_TextBox_1 = text;

	w = 0;
	h = group_box -> Anchor.Y.GetMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.AnchorMin(w, 200);
	slider -> Anchor.Y.AnchorMax(h);
//	slider -> Anchor.X.Anchor = AnchorType::Min;
//	slider -> Anchor.Y.Anchor = AnchorType::Max;
//	slider -> Anchor.X.SetPaddedMinDist(w);
//	slider -> Anchor.X.SetSize(200);
//	slider -> Anchor.Y.SetPaddedMaxDist(h);
	slider -> ValueChangedFunc.Assign(this, &MainContext::slider_changed);
	form -> ChildInsert(slider);

	w = slider -> Anchor.X.GetMinSize();

	text = new UI::Control::TextBox();
	text -> Anchor.X.AnchorBoth(w, 0);
	text -> Anchor.Y.AnchorMax(h);
//	text -> Anchor.X.Anchor = AnchorType::Both;
//	text -> Anchor.Y.Anchor = AnchorType::Max;
//	text -> Anchor.X.SetPaddedMinDist(w);
//	text -> Anchor.X.SetPaddedMaxDist(0);
//	text -> Anchor.Y.SetPaddedMaxDist(h);
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
}
void UI_Init()
{
	std::cout << "Control Init ...\n";

//	UI_Control_Manager = new UI::Control::Manager(ShaderDir);
//	UI_Text_Manager = new UI::Text::Manager(ShaderDir, TextDir);
//	UI_Control_Manager -> UpdateSize(window.Size);

	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("UI/Control.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("UI/Control.frag")));
		UI_Control_Manager.Shader.Change(code);
	}
	UI_Control_Manager.Shader.Create();
	UI_Control_Manager.BufferArray.Create();
	UI_Control_Manager.UpdateSize(window.Size);

	UI_Control_Manager.Window.ChangeManager(&UI_Control_Manager);
	UI_Control_Manager.Window.ChangeManager(&UI_Text_Manager);

	UI_Control_Manager.BufferArray.Main.Init();
	UI_Control_Manager.BufferArray.Inst.Init();

	std::cout << "Control Init done\n";
}
void UI_Free()
{
	std::cout << "Control Free ...\n";

	std::cout << "Control Free done\n";
}
void UI_Frame()
{
	Point2D mouse = window.MouseManager.CursorPosition().Buffer.Corner;

	UI_Control_Manager.UpdateMouse(mouse);
	UI_Control_Manager.Window.UpdateEntrys();
	UI_Control_Manager.UpdateSize(window.Size);

	UI_Control_Manager.Shader.DisplaySize.Put(window.Size);
	UI_Control_Manager.Draw();
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

	Text_Make();

	std::cout << "Init ...\n";

	UI_Init();

//	Container::Fixed<Shader::Base *> shaders(2);
//	shaders.Insert(&(UI_Control_Manager -> Shader));
//	shaders.Insert(&(UI_Text_Manager -> Shader));

//	Multi_WindowSize = new Multiform::WindowBufferSize2D("WindowSize");
//	Multi_WindowSize -> FindUniforms(shaders);

	UI_Make();
	{
		UI::Control::Form * form = new UI::Control::Form();
		form -> Anchor.X.AnchorBoth(320 - 20, 320 - 20);
		form -> Anchor.Y.AnchorBoth(240 - 20, 240 - 20);
		UI_Control_Manager.Window.ChildInsert(form);
	}

	std::cout << "Init done\n";
}
void FreeRun()
{
	std::cout << "Free ...\n";

//	delete Multi_WindowSize;

	UI_Free();

	std::cout << "Free done\n";
}

void ShowText(const char * text)
{
	UI::Text::ObjectData * obj = UI_Text_Manager.PlaceObject();
	obj -> Text = text;
	obj -> Pos = window.Size.Buffer.Half;
	obj -> Bound = AxisBox2D(Point2D(), window.Size.Buffer.Full);
	obj -> Remove = true;
}
void ShowAlphabet()
{
	UI::Text::Object obj;
	obj.Create();

	obj.Pos() = window.Size.Buffer.Half;
	obj.Bound() = AxisBox2D(Point2D(), window.Size.Buffer.Full);

	obj.Data -> AlignmentX = UI::Text::Alignment::Min;
	obj.Data -> AlignmentY = UI::Text::Alignment::Min;

	obj.String() = "0123456789\n";
	obj.String() += "abcdefghijklm\n";
	obj.String() += "nopqrstuvwxyz\n";
	obj.String() += "ABCDEFGHIJKLM\n";
	obj.String() += "NOPQRSTUVWXYZ\n";
	obj.String() += "<>";
}
/*void ShowAllCharacters()
{
	//Point2D CharacterSize = Point2D(32, 32);
	Point2D CharacterSize = Point2D(20, 20);
	Point2D center = window.Size.Buffer.Half;

	unsigned int i = 0;
	for (unsigned int y = 0; y < 8; y++)
	{
		for (unsigned int x = 0; x < 16; x++)
		{
			TextEntry[i].Pos = Point2D(center.X - (CharacterSize.X * (x - 8.0f)), center.Y - (CharacterSize.Y * (y - 4.0f)));
			TextEntry[i].Pallet.Min = Point2D(x / 16.0f, y / 8.0f);
			TextEntry[i].Pallet.Max = TextEntry[i].Pallet.Min + Point2D(1 / 16.0f, 1 / 8.0f);
			TextEntry[i].Bound = AxisBox2D(Point2D(), window.Size.Buffer.Full);
			i++;
		}
	}
}*/

void Frame(double timeDelta)
{
	(void)timeDelta;

	//ShowText("test asd Text");
	ShowAlphabet();
	//ShowAllCharacters();

	UI_Frame();

	UI_Text_Manager.Draw();
}



void Resize(const ::DisplaySize & DisplaySize)
{
	(void)DisplaySize;

	UI_Text_Manager.Shader.DisplaySize.Put(DisplaySize);
	
//	Multi_WindowSize -> ChangeData(WindowSize);
//	UI_Control_Manager -> UpdateSize(WindowSize);
}

void ClickFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		UI_Control_Manager.RelayClick(args);
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
	UI_Control_Manager.RelayCursorDrag(args);
}

void KeyFunc(KeyArgs args)
{
	UI_Control_Manager.RelayKey(args);
}
void TextFunc(TextArgs args)
{
	UI_Control_Manager.RelayText(args);
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
