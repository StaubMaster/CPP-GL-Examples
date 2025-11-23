
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

#include "Graphics/Texture/2DArray.hpp"



#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "UI/Control/Base/Manager.hpp"
#include "UI/Controls.hpp"

#include "UI/Text/Data.hpp"
#include "UI/Text/Buffer.hpp"



Window * window;
SizeRatio2D ViewPortSizeRatio;

DirectoryContext ShaderDir("./media/Shaders");

Shader::Base * UI_Shader;
Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;



Control::Manager * ControlManager;
Control::Window * WindowControl;



DirectoryContext ImageDir("./media/Images");

UI::Text::BufferArray * Text_BufferArray;
ContainerDynamic<UI::Text::Main_Data> Text_Main_Data_Container;
ContainerDynamic<UI::Text::Inst_Data> Text_Inst_Data_Container;
Shader::Base * Text_Shader;
Texture::T2DArray * Text_Pallet_Texture;

void TextInit()
{
	Text_BufferArray = new UI::Text::BufferArray();
	Text_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("Text.vert")),
		Shader::Code::FromFile(ShaderDir.File("Text.frag"))
	}, 2);

	Image * img = ImageDir.File("Text_16_8.png").LoadImagePNG();
	Text_Pallet_Texture = new Texture::T2DArray(img);
	delete img;

	Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, -1)));
	Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	Text_Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, +1)));

	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(-0.625, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(-0.500, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(-0.375, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(-0.250, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(-0.125, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D( 0.000, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(+0.125, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(+0.250, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(+0.375, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(+0.500, 0.0), Point2D(0, 0)));
	Text_Inst_Data_Container.Insert(UI::Text::Inst_Data(Point2D(+0.625, 0.0), Point2D(0, 0)));
}
void TextFree()
{
	delete Text_BufferArray;
	delete Text_Shader;
	delete Text_Pallet_Texture;
}
void TextFrame()
{
	Text_BufferArray -> Use();

	Text_BufferArray -> Main.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI::Text::Main_Data) * Text_Main_Data_Container.Count(), Text_Main_Data_Container.ToPointer(), GL_STREAM_DRAW);
	Text_BufferArray -> Main.Count = Text_Main_Data_Container.Count();

	Text_BufferArray -> Inst.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI::Text::Inst_Data) * Text_Inst_Data_Container.Count(), Text_Inst_Data_Container.ToPointer(), GL_STREAM_DRAW);
	Text_BufferArray -> Inst.Count = Text_Inst_Data_Container.Count();

	Text_Shader -> Use();
	Text_Pallet_Texture -> Bind();
	Text_BufferArray -> Draw();
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

	TextInit();
}
void FreeRun()
{
	delete UI_Shader;

	delete Uni_ViewPortSizeRatio;

	delete Multi_ViewPortSizeRatio;

	delete ControlManager;

	delete WindowControl;

	TextFree();
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

	TextFrame();
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
