
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



Window * window;

DirectoryContext ShaderDir("./media/Shaders");
DirectoryContext ImageDir("./media/Images");

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;





void click0(unsigned char clickType, unsigned char clickButton);
void click1(unsigned char clickType, unsigned char clickButton);
void click_toggle_MainForm(unsigned char clickType, unsigned char clickButton);

UI::Control::Manager * UI_Control_Manager;
UI::Text::Manager * UI_Text_Manager;

UI::Control::Form * MainForm;
UI::Control::Text * TextControl0;
UI::Control::Text * TextControl1;

//	Removing Entrys might still cause Data Reallocation in Containers in Control Manager
//	have a way to mark EntryContainer for deletion so its just ignores Entry stuff
//	Insert should return NULL Entrys
//	have a way to start it again ? so it's just temprarily static ?
//	"immutable" ?

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
	UI::Control::Text * text;

	form = new UI::Control::Form(*UI_Control_Manager);
	UI_Control_Manager -> Window -> Children.Insert(form);
	MainForm = form;

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

	text = new UI::Control::Text(*UI_Control_Manager, *UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_NONE;
	text -> PixelSize = Point2D(60, 60);
	text -> NormalCenter = Point2D(0.5, 0.5 - 0.1);
	form -> Children.Insert(text);
	TextControl0 = text;
	TextControl0 -> SetText("Text0");

	text = new UI::Control::Text(*UI_Control_Manager, *UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_NONE;
	text -> PixelSize = Point2D(60, 60);
	text -> NormalCenter = Point2D(0.5, 0.5 + 0.1);
	form -> Children.Insert(text);
	TextControl1 = text;
	TextControl1 -> SetText("Text1");

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
		UI_Control_Manager -> Click(CLICK_PRESS, CLICK_BUTTON_L);
	}

	UI_Control_Manager -> Window -> UpdateEntrys();

	UI_Control_Manager -> Draw();
	UI_Text_Manager -> Draw();
}

void click0(unsigned char code, unsigned char action)
{
	std::cout << "click0\n";
	(void)code;
	(void)action;
}
void click1(unsigned char code, unsigned char action)
{
	std::cout << "click1\n";
	(void)code;
	(void)action;
}
void click_toggle_MainForm(unsigned char code, unsigned char action)
{
	std::cout << "click toggle\n";
	(void)code;
	(void)action;
	if (MainForm -> Visible)
	{
		MainForm -> Hide();
	}
	else
	{
		MainForm -> Show();
	}
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

/*	how to send this to Controls ?
	send to manager
	it sends it to the Controls ?
	what if I want multiple Control Types to accept Text
	the easiest would be to have functions that accept this in the Base
	and then have an empty virtual function
	so the controls that dont need it can just ignore it
*/
void KeyFunc(int key, int scancode, int action, int mods)
{
	UI_Control_Manager -> Key(key, scancode, action, mods);
}
void TextFunc(unsigned int codepoint)
{
	UI_Control_Manager -> DoText(codepoint);
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
