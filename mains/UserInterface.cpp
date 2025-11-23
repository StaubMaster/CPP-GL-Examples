
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"

#include "DataShow.hpp"
#include "Miscellaneous/ContainerDynamic.hpp"
#include "Miscellaneous/EntryContainer/EntryContainerDynamic.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/Buffer/BaseBufferArray.hpp"
#include "Graphics/Buffer/BaseBuffer.hpp"

#include "Graphics/Attribute/Base/AttributeBase.hpp"
#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/Color.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"



#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "UI/Control/Base/Manager.hpp"
#include "UI/Controls.hpp"



Window * window;
SizeRatio2D ViewPortSizeRatio;

DirectoryContext ShaderDir("./media/Shaders");

Shader::Base * UI_Shader;
Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;



Control::Manager * ControlManager;
Control::Window * WindowControl;



/*	Controls
Window
Form

Button
Toggle
Text (with no Text for now ?)

Object Slow ?
*/

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

void InitRun()
{
	UI_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("UI.vert")),
		Shader::Code::FromFile(ShaderDir.File("UI.frag"))
	}, 2);

	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *UI_Shader);

	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");

	Multi_ViewPortSizeRatio -> FindUniforms(&UI_Shader, 1);



	ControlManager = new Control::Manager();

	WindowControl = new Control::Window(*ControlManager);

	Control::Button * button;
	Control::Text * text;
	Control::Form * form;

	form = new Control::Form(*ControlManager);
	WindowControl -> Children.Insert(form);

	button = new Control::Button(*ControlManager);
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MIN;
	button -> ClickFunc = click0;
	form -> Children.Insert(button);

	button = new Control::Button(*ControlManager);
	button -> Anchor.X.Anchor = ANCHOR_MAX;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> ClickFunc = click1;
	form -> Children.Insert(button);

	text = new Control::Text(*ControlManager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_NONE;
	text -> PixelSize = Point2D(60, 60);
	text -> NormalCenter = Point2D(0.5, 0.5);
	form -> Children.Insert(text);

	form = new Control::Form(*ControlManager);
	form -> Anchor.X.Anchor = ANCHOR_MIN;
	form -> Anchor.Y.Anchor = ANCHOR_NONE;
	form -> PixelSize = Point2D(60, 360);
	form -> NormalCenter = Point2D(0, 0.5);
	WindowControl -> Children.Insert(form);

	form = new Control::Form(*ControlManager);
	form -> Anchor.X.Anchor = ANCHOR_MAX;
	form -> Anchor.Y.Anchor = ANCHOR_BOTH;
	form -> PixelSize = Point2D(60, 360);
	form -> NormalCenter = Point2D(0, 0);
	WindowControl -> Children.Insert(form);

	WindowControl -> Show();
}
void FreeRun()
{
	delete UI_Shader;

	delete Uni_ViewPortSizeRatio;

	delete Multi_ViewPortSizeRatio;

	delete ControlManager;

	delete WindowControl;
}

void Frame(double timeDelta)
{
	(void)timeDelta;
	UI_Shader -> Use();

	WindowControl -> UpdateBox(AxisBox2D(Point2D(), ControlManager -> ViewPortSize));
	WindowControl -> Show();

	ControlManager -> ChangeHover(NULL);
	Point2D mouse = window -> CursorPixel();
	mouse.Y = ViewPortSizeRatio.H - mouse.Y;
	WindowControl -> UpdateHover(mouse);

	if (window -> MouseButtons[GLFW_MOUSE_BUTTON_LEFT].State.GetPressed())
	{
		ControlManager -> Click(CLICK_PRESS, CLICK_BUTTON_L);
	}

	ControlManager -> BufferUpdate();
	ControlManager -> BufferDraw();
}

void Resize(int w, int h)
{
	ViewPortSizeRatio = SizeRatio2D(w, h);
	Multi_ViewPortSizeRatio -> ChangeData(ViewPortSizeRatio);
	ControlManager -> ViewPortSize = Point2D(ViewPortSizeRatio.W, ViewPortSizeRatio.H);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(window->DefaultColor.R, window->DefaultColor.G, window->DefaultColor.B, 1.0f);
	//Frame(0);
	//glfwSwapBuffers(window->win);
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

	window -> DefaultColor = Color(0.875f, 0.875f, 0.875f);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete window;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
