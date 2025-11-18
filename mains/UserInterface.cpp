
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



#include "UI/DisplayScale.cpp"
#include "UI/AxisBox.cpp"
#include "UI/Anchor.cpp"
#include "UI/Control.cpp"



Window * window;
SizeRatio2D ViewPortSizeRatio;

Shader::Base * UI_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;

class UI_Main_Attribute : public Attribute::Base
{
	private:
		Attribute::Point2D	Pos;
	public:
		UI_Main_Attribute(
			unsigned int divisor,
			unsigned int stride,
			unsigned int indexPos
		) :
			Pos(divisor, stride, indexPos)
		{ }
	public:
		void Bind(const unsigned char * & offset) const override
		{
			Pos.Bind(offset);
		}
};
class UI_Inst_Attribute : public Attribute::Base
{
	private:
		Attribute::Point2D	Min;
		Attribute::Point2D	Max;
		Attribute::FloatN	Layer;
		Attribute::Color	Col;
	public:
		UI_Inst_Attribute(
			unsigned int divisor,
			unsigned int stride,
			unsigned int indexMin,
			unsigned int indexMax,
			unsigned int indexLayer,
			unsigned int indexCol
		) :
			Min(divisor, stride, indexMin),
			Max(divisor, stride, indexMax),
			Layer(divisor, stride, indexLayer),
			Col(divisor, stride, indexCol)
		{ }
	public:
		void Bind(const unsigned char * & offset) const override
		{
			Min.Bind(offset);
			Max.Bind(offset);
			Layer.Bind(offset);
			Col.Bind(offset);
		}
};

class UI_BufferArray : public BaseBufferArray
{
	public:
		BaseBuffer Main;
		BaseBuffer Inst;

	public:
		UI_BufferArray() :
			Main(1, (Attribute::Base * []) { new UI_Main_Attribute(0, sizeof(UI_Main_Data), 0) }),
			Inst(1, (Attribute::Base * []) { new UI_Inst_Attribute(1, sizeof(UI_Inst_Data), 1, 2, 3, 4) })
		{ }

	public:
		void Draw() override
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, Main.Count, Inst.Count);
		}
};
UI_BufferArray * UI_BufferArray_;

ContainerDynamic<UI_Main_Data> UI_Main_Data_C;
EntryContainerDynamic<UI_Inst_Data> UI_Inst_Data_C;

Control * WindowControl;

DirectoryContext ShaderDir("./media/Shaders");

/*	Controls
Window
Form

Button
Toggle
Text (with no Text for now ?)

Object Slow ?
*/

void InitRun()
{
	UI_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("UI.vert")),
		Shader::Code::FromFile(ShaderDir.File("UI.frag"))
	}, 2);

	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *UI_Shader);

	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");

	Multi_ViewPortSizeRatio -> FindUniforms(&UI_Shader, 1);

	UI_BufferArray_ = new UI_BufferArray();

	UI_Main_Data_C.Insert(UI_Main_Data(Point2D(-1, -1)));
	UI_Main_Data_C.Insert(UI_Main_Data(Point2D(-1, +1)));
	UI_Main_Data_C.Insert(UI_Main_Data(Point2D(+1, -1)));
	UI_Main_Data_C.Insert(UI_Main_Data(Point2D(+1, -1)));
	UI_Main_Data_C.Insert(UI_Main_Data(Point2D(-1, +1)));
	UI_Main_Data_C.Insert(UI_Main_Data(Point2D(+1, +1)));



	WindowControl = new Control(NULL);
	WindowControl -> Layer = 0.3f;
	WindowControl -> Anchor.X.Anchor = ANCHOR_BOTH;
	WindowControl -> Anchor.Y.Anchor = ANCHOR_BOTH;
	WindowControl -> PixelMinDist = Point2D(0, 0);
	WindowControl -> PixelSize = Point2D(0, 0);
	WindowControl -> PixelMaxDist = Point2D(0, 0);
	WindowControl -> NormalCenter = Point2D(0, 0);
	WindowControl -> ColorDefault = Color(0.25f, 0.25f, 0.25f);
	WindowControl -> ColorHover = Color(0.25f, 0.25f, 0.25f);

	Control * control;

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> Layer = 0.2f;
	control -> Anchor.X.Anchor = ANCHOR_NONE;
	control -> Anchor.Y.Anchor = ANCHOR_NONE;
	control -> PixelMinDist = Point2D(12, 12);
	control -> PixelSize = Point2D(480, 360);
	control -> PixelMaxDist = Point2D(12, 12);
	control -> NormalCenter = Point2D(0.5, 0.5);
	control -> ColorDefault = Color(0.75f, 0.75f, 0.75f);
	control -> ColorHover = Color(0.75f, 0.75f, 0.75f);
	WindowControl -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> Layer = 0.1f;
	control -> Anchor.X.Anchor = ANCHOR_MIN;
	control -> Anchor.Y.Anchor = ANCHOR_MIN;
	control -> PixelMinDist = Point2D(12, 12);
	control -> PixelSize = Point2D(120, 60);
	control -> PixelMaxDist = Point2D(12, 12);
	control -> NormalCenter = Point2D(0, 0);
	control -> ColorDefault = Color(0.625f, 0.625f, 0.625f);
	control -> ColorHover = Color(0.5f, 0.5f, 0.5f);
	WindowControl -> Children[0] -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> Layer = 0.1f;
	control -> Anchor.X.Anchor = ANCHOR_MAX;
	control -> Anchor.Y.Anchor = ANCHOR_MAX;
	control -> PixelMinDist = Point2D(12, 12);
	control -> PixelSize = Point2D(120, 60);
	control -> PixelMaxDist = Point2D(12, 12);
	control -> NormalCenter = Point2D(0, 0);
	control -> ColorDefault = Color(0.625f, 0.625f, 0.625f);
	control -> ColorHover = Color(0.5f, 0.5f, 0.5f);
	WindowControl -> Children[0] -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> Layer = 0.1f;
	control -> Anchor.X.Anchor = ANCHOR_BOTH;
	control -> Anchor.Y.Anchor = ANCHOR_NONE;
	control -> PixelMinDist = Point2D(12, 12);
	control -> PixelSize = Point2D(60, 60);
	control -> PixelMaxDist = Point2D(12, 12);
	control -> NormalCenter = Point2D(0.5, 0.5);
	control -> ColorDefault = Color(0.625f, 0.625f, 0.625f);
	control -> ColorHover = Color(0.5f, 0.5f, 0.5f);
	WindowControl -> Children[0] -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> Layer = 0.2f;
	control -> Anchor.X.Anchor = ANCHOR_MIN;
	control -> Anchor.Y.Anchor = ANCHOR_NONE;
	control -> PixelMinDist = Point2D(12, 12);
	control -> PixelSize = Point2D(60, 360);
	control -> PixelMaxDist = Point2D(12, 12);
	control -> NormalCenter = Point2D(0, 0.5);
	control -> ColorDefault = Color(0.75f, 0.75f, 0.75f);
	control -> ColorHover = Color(0.75f, 0.75f, 0.75f);
	WindowControl -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> Layer = 0.2f;
	control -> Anchor.X.Anchor = ANCHOR_MAX;
	control -> Anchor.Y.Anchor = ANCHOR_BOTH;
	control -> PixelMinDist = Point2D(12, 12);
	control -> PixelSize = Point2D(60, 360);
	control -> PixelMaxDist = Point2D(12, 12);
	control -> NormalCenter = Point2D(0, 0);
	control -> ColorDefault = Color(0.75f, 0.75f, 0.75f);
	control -> ColorHover = Color(0.75f, 0.75f, 0.75f);
	WindowControl -> Children.Insert(control);

	WindowControl -> UpdateEntryDefault();
}
void FreeRun()
{
	delete UI_Shader;

	delete Uni_ViewPortSizeRatio;

	delete Multi_ViewPortSizeRatio;

	delete UI_BufferArray_;

	delete WindowControl;
}

void Frame(double timeDelta)
{
	(void)timeDelta;
	UI_Shader -> Use();

	WindowControl -> UpdateBox(AxisBox2D(Point2D(0, 0), Point2D(ViewPortSizeRatio.W, ViewPortSizeRatio.H)));
	WindowControl -> UpdateEntryBox(Point2D(ViewPortSizeRatio.W, ViewPortSizeRatio.H));
	Point2D mouse = window -> CursorPixel();
	mouse.Y = ViewPortSizeRatio.H - mouse.Y;
	WindowControl -> UpdateHover(mouse);

	UI_BufferArray_ -> Use();
	UI_BufferArray_ -> Main.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI_Main_Data) * UI_Main_Data_C.Count(), UI_Main_Data_C.ToPointer(), GL_STREAM_DRAW);
	UI_BufferArray_ -> Main.Count = UI_Main_Data_C.Count();
	UI_BufferArray_ -> Inst.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI_Inst_Data) * UI_Inst_Data_C.Length, UI_Inst_Data_C.Data, GL_STREAM_DRAW);
	UI_BufferArray_ -> Inst.Count = UI_Inst_Data_C.Length;
	UI_BufferArray_ -> Draw();
}

void Resize(int w, int h)
{
	ViewPortSizeRatio = SizeRatio2D(w, h);
	Multi_ViewPortSizeRatio -> ChangeData(ViewPortSizeRatio);
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
