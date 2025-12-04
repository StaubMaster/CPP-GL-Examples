
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

#include "UI/Text/Data.hpp"
#include "UI/Text/Buffer.hpp"



Window * window;

DirectoryContext ShaderDir("./media/Shaders");
DirectoryContext ImageDir("./media/Images");

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;





void click0(unsigned char clickType, unsigned char clickButton);
void click1(unsigned char clickType, unsigned char clickButton);
void click_toggle_MainForm(unsigned char clickType, unsigned char clickButton);

Control::Manager * UI_Control_Manager;

Control::Window * WindowControl;
Control::Form * MainForm;
Control::Text * TextControl;

void ControlInit()
{
	std::cout << "Control Init ...\n";



	UI_Control_Manager = new Control::Manager(ShaderDir);

	WindowControl = new Control::Window(*UI_Control_Manager);

	Control::Form * form;
	Control::Button * button;
	Control::Text * text;

	form = new Control::Form(*UI_Control_Manager);
	WindowControl -> Children.Insert(form);
	MainForm = form;

	button = new Control::Button(*UI_Control_Manager);
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MIN;
	button -> ClickFunc = click0;
	form -> Children.Insert(button);

	button = new Control::Button(*UI_Control_Manager);
	button -> Anchor.X.Anchor = ANCHOR_MAX;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> ClickFunc = click1;
	form -> Children.Insert(button);

	text = new Control::Text(*UI_Control_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_NONE;
	text -> PixelSize = Point2D(60, 60);
	text -> NormalCenter = Point2D(0.5, 0.5);
	form -> Children.Insert(text);
	TextControl = text;

	form = new Control::Form(*UI_Control_Manager);
	form -> Anchor.X.Anchor = ANCHOR_MIN;
	form -> Anchor.Y.Anchor = ANCHOR_NONE;
	form -> PixelSize = Point2D(60, 360);
	form -> NormalCenter = Point2D(0, 0.5);
	WindowControl -> Children.Insert(form);

	button = new Control::Button(*UI_Control_Manager);
	button -> Anchor.X.Anchor = ANCHOR_BOTH;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> ClickFunc = click_toggle_MainForm;
	form -> Children.Insert(button);

	form = new Control::Form(*UI_Control_Manager);
	form -> Anchor.X.Anchor = ANCHOR_MAX;
	form -> Anchor.Y.Anchor = ANCHOR_BOTH;
	form -> PixelSize = Point2D(60, 360);
	form -> NormalCenter = Point2D(0, 0);
	WindowControl -> Children.Insert(form);

	std::cout << "Control Init done\n";

	WindowControl -> Show();
}
void ControlFree()
{
	std::cout << "Control Free ....\n";

	delete WindowControl;
	//	Removing Entrys might still cause Data Reallocation in Containers in Control Manager
	//	have a way to mark EntryContainer for deletion so its just ignores Entry stuff
	//	Insert should return NULL Entrys
	//	have a way to start it again ? so it's just temprarily static ?
	//	"immutable" ?
	delete UI_Control_Manager;

	std::cout << "Control Free done\n";
}
void ControlFrame()
{
	UI_Control_Manager -> Shader.Use();

	WindowControl -> UpdateBox(AxisBox2D(Point2D(), UI_Control_Manager -> ViewPortSize));
	WindowControl -> UpdateEntryAll();

	UI_Control_Manager -> ChangeHover(NULL);
	Point2D mouse = window -> CursorPixel();
	mouse.Y = window -> ViewPortSizeRatio.Size.Y - mouse.Y;
	WindowControl -> UpdateHover(mouse);

	//std::cout << "mouse " << mouse << "\n";
	//std::cout << "button " << (MainForm -> Children[0] -> PixelBox.Min) << " " << (MainForm -> Children[0] -> PixelBox.Max) << "\n";

	if (window -> MouseButtons[GLFW_MOUSE_BUTTON_LEFT].State.GetPressed())
	{
		UI_Control_Manager -> Click(CLICK_PRESS, CLICK_BUTTON_L);
	}

	UI_Control_Manager -> BufferUpdate();
	UI_Control_Manager -> BufferDraw();
}

void click0(unsigned char clickType, unsigned char clickButton)
{
	std::cout << "click0\n";
	(void)clickType;
	(void)clickButton;
}
void click1(unsigned char clickType, unsigned char clickButton)
{
	std::cout << "click1\n";
	(void)clickType;
	(void)clickButton;
}
void click_toggle_MainForm(unsigned char clickType, unsigned char clickButton)
{
	std::cout << "click toggle\n";
	(void)clickType;
	(void)clickButton;
	if (MainForm -> Visible)
	{
		MainForm -> Hide();
	}
	else
	{
		MainForm -> Show();
	}
}



Shader::Base * UI_Text_Shader;
Uniform::SizeRatio2D * UI_Text_Uni_ViewPortSizeRatio;

std::string UI_Text_String = "0aAzZ+-";
bool UI_Text_String_Changed = true;

UI::Text::BufferArray * UI_Text_BufferArray;
Container::Dynamic<UI::Text::Main_Data> UI_Text_Main_Data_Container;
Container::Dynamic<UI::Text::Inst_Data> UI_Text_Inst_Data_Container;
Texture::T2DArray * UI_Text_Pallet_Texture;

Point2D CharToTextCoord(int c)
{
	if (c >= '0' && c <= '9') { return Point2D(c - '0' ,0); }
	if (c >= 'A' && c <= 'M') { return Point2D(c - 'A' ,1); }
	if (c >= 'N' && c <= 'Z') { return Point2D(c - 'N' ,2); }
	if (c >= 'a' && c <= 'm') { return Point2D(c - 'a' ,3); }
	if (c >= 'n' && c <= 'z') { return Point2D(c - 'n' ,4); }
	if (c == '+') { return Point2D(10 ,0); }
	if (c == '-') { return Point2D(11 ,0); }
	if (c == '*') { return Point2D(12 ,0); }
	if (c == '/') { return Point2D(13 ,0); }
	if (c == '=') { return Point2D(13 ,2); }
	if (c == '<') { return Point2D(14 ,2); }
	if (c == '>') { return Point2D(15 ,2); }
	return Point2D(15, 0);
}

void TextChangeFunc();

void TextInit()
{
	UI_Text_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("UI/Text.vert")),
		Shader::Code::FromFile(ShaderDir.File("UI/Text.frag"))
	}, 2);
	UI_Text_Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *UI_Text_Shader);

	UI_Text_BufferArray = new UI::Text::BufferArray();

	Image * img = ImageDir.File("Text_16_8.png").LoadImagePNG();
	UI_Text_Pallet_Texture = new Texture::T2DArray(img);
	delete img;

	UI_Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, -1)));
	UI_Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	UI_Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	UI_Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	UI_Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	UI_Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, +1)));
}
void TextFree()
{
	delete UI_Text_Shader;
	delete UI_Text_Uni_ViewPortSizeRatio;

	delete UI_Text_BufferArray;
	delete UI_Text_Pallet_Texture;
}
void TextFrame()
{
	if (UI_Text_String_Changed)
	{
		UI_Text_Inst_Data_Container.Dispose();
		for (unsigned int i = 0; i < UI_Text_String.length(); i++)
		{
			UI_Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(25.0 + (i * 50), 25.0),
				CharToTextCoord(UI_Text_String[i])));
		}
		UI_Text_String_Changed = false;
	}
	
	{
		Point2D min = TextControl -> PixelBox.Min;
		Point2D max = TextControl -> PixelBox.Max;
		Point2D center = (max + min) / 2;
		for (unsigned int i = 0; i < UI_Text_String.length(); i++)
		{
			UI_Text_Inst_Data_Container[i].Pos = Point2D((min.X + 25) + (i * 50), center.Y);
		}
	}

	UI_Text_BufferArray -> Use();

	UI_Text_BufferArray -> Main.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI::Text::Main_Data) * UI_Text_Main_Data_Container.Count(), UI_Text_Main_Data_Container.Data(), GL_STREAM_DRAW);
	UI_Text_BufferArray -> Main.Count = UI_Text_Main_Data_Container.Count();

	UI_Text_BufferArray -> Inst.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI::Text::Inst_Data) * UI_Text_Inst_Data_Container.Count(), UI_Text_Inst_Data_Container.Data(), GL_STREAM_DRAW);
	UI_Text_BufferArray -> Inst.Count = UI_Text_Inst_Data_Container.Count();

	UI_Text_Shader -> Use();
	UI_Text_Pallet_Texture -> Bind();
	UI_Text_BufferArray -> Draw();
}



void InitRun()
{
	std::cout << "Init ...\n";

	ControlInit();
	TextInit();

	Shader::Base * shaders[2] =
	{
		&(UI_Control_Manager -> Shader),
		UI_Text_Shader,
	};
	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_ViewPortSizeRatio -> FindUniforms(shaders, 2);

	std::cout << "Init done\n";
}
void FreeRun()
{
	std::cout << "Free ...\n";

	ControlFree();
	TextFree();

	delete Multi_ViewPortSizeRatio;

	std::cout << "Free done\n";
}
void Frame(double timeDelta)
{
	(void)timeDelta;

	ControlFrame();
	TextFrame();
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

/*	how to send this to Controls ?
	send to manager
	it sends it to the Controls ?
	what if I want multiple Control Types to accept Text
	the easiest would be to have functions that accept this in the Base
	and then have an empty virtual function
	so the controls that dont need it can just ignore it
*/
void TextFunc(unsigned int codepoint)
{
	(void)codepoint;
	//std::cout << "text [" << codepoint << "] '" << ((char)codepoint) << "'\n";
	if (
		(codepoint >= '0' && codepoint <= '9') ||
		(codepoint >= 'A' && codepoint <= 'Z') ||
		(codepoint >= 'a' && codepoint <= 'z') ||
		codepoint == '+' || codepoint == '-' || codepoint == '*' ||
		codepoint == '/' ||
		codepoint == '=' || codepoint == '<' || codepoint == '>' ||
		codepoint == ' '
		)
	{
		if (UI_Control_Manager -> Selected == TextControl)
		{
			UI_Text_String += (char)codepoint;
			UI_Text_String_Changed = true;
		}
	}
}
void KeyFunc(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//std::cout << "BackSpace\n";
		if (UI_Control_Manager -> Selected == TextControl)
		{
			if (UI_Text_String.length() > 0)
			{
				UI_Text_String.erase(UI_Text_String.length() - 1, 1);
				UI_Text_String_Changed = true;
			}
		}
	}
	if (key == GLFW_KEY_ENTER && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//std::cout << "Enter\n";
	}
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
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
