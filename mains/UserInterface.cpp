
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




Window * window;
SizeRatio2D ViewPortSizeRatio;

Shader::Base * UI_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;



struct UI_Main_Data
{
	Point2D	Pos;

	UI_Main_Data() { }
	UI_Main_Data(Point2D pos) :
		Pos(pos)
	{ }
};
struct UI_Inst_Data
{
	Point2D	Min;
	Point2D	Max;
	float	Layer;
	Color Col;

	UI_Inst_Data() { }
	UI_Inst_Data(Point2D min, Point2D max, float layer, Color col) :
		Min(min),
		Max(max),
		Layer(layer),
		Col(col)
	{ }
};

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

/*
more in UI_Data
{
	Point2D NormalPos
	Point2D PixelPos
}

Control
{
	Entry to UIInstData
	NormalPos
	PixelPos
	Size ?

	MinDist		Distance from Parent.Min to Control.Min
	LenDist		Distance from Control.Min to Control.Max
	MaxDist		Distance from Control.Max to Parent.Max
}
*/

Point2D Normal0ToPixel(Point2D p)
{
	//	Normal [ 0 ; 1 ]
	//	Pixel [ 0 ; n ]
	p.X = p.X * ViewPortSizeRatio.W;
	p.Y = p.Y * ViewPortSizeRatio.H;
	return p;
}
Point2D PixelToNormal0(Point2D p)
{
	//	Pixel [ 0 ; n ]
	//	Normal [ 0 ; 1 ]
	p.X = p.X / ViewPortSizeRatio.W;
	p.Y = p.Y / ViewPortSizeRatio.H;
	return p;
}
Point2D Normal0ToNormal1(Point2D p)
{
	//	Normal0 [ 0 ; 1 ]
	//	Normal1 [ -1 ; +1 ]
	p.X = (p.X * 2) - 1;
	p.Y = (p.Y * 2) - 1;
	return p;
}
Point2D Normal1ToNormal0(Point2D p)
{
	//	Normal1 [ -1 ; +1 ]
	//	Normal0 [ 0 ; 1 ]
	p.X = (p.X + 1) / 2;
	p.Y = (p.Y + 1) / 2;
	return p;
}

#define ANCHOR_X_MASK 0b0011
#define ANCHOR_X_NONE 0b0000
#define ANCHOR_X_MIN  0b0001
#define ANCHOR_X_MAX  0b0010
#define ANCHOR_X_BOTH 0b0011

class Control
{
	public:
		EntryContainerDynamic<UI_Inst_Data>::Entry * Entry;
		unsigned int Anchor;
		Point2D	MinDist;
		Point2D	LenDist;
		Point2D	MaxDist;

	public:
		Control() { }
		Control(EntryContainerDynamic<UI_Inst_Data>::Entry * entry) :
			Entry(entry)
		{ }
};

ContainerDynamic<Control> Controls;

DirectoryContext ShaderDir("./media/Shaders");

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

	unsigned int idx;

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.2f, Color(1, 0, 0));
	
	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.1f, Color(0, 1, 0));

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.1f, Color(0, 0, 1));
}
void FreeRun()
{
	delete UI_Shader;

	delete Uni_ViewPortSizeRatio;

	delete Multi_ViewPortSizeRatio;

	delete UI_BufferArray_;
}

void Frame(double timeDelta)
{
	(void)timeDelta;
	UI_Shader -> Use();

	//	Control 0
	{
		//	Fixed PixelSize
		//	Stay in Center
		Point2D	Size(480, 360);
		Point2D NormalCenter(0, 0);
		(*Controls[0].Entry)[0].Min = NormalCenter - PixelToNormal0(Size);
		(*Controls[0].Entry)[0].Max = NormalCenter + PixelToNormal0(Size);
	}

	//	Control1
	{
		//	Fixed PixelSize
		//	Keep Distance from BottomLeft of Control0
		Point2D Dist(24, 24);
		Point2D Size(240, 120);
		(*Controls[1].Entry)[0].Min = (*Controls[0].Entry)[0].Min + PixelToNormal0(Dist);
		(*Controls[1].Entry)[0].Max = (*Controls[0].Entry)[0].Min + PixelToNormal0(Dist) + PixelToNormal0(Size);
	}

	//	Control2
	{
		//	Fixed PixelSize
		//	Keep Distance from TopRight of Control0
		Point2D Dist(24, 24);
		Point2D Size(240, 120);
		(*Controls[2].Entry)[0].Min = (*Controls[0].Entry)[0].Max - PixelToNormal0(Dist) - PixelToNormal0(Size);
		(*Controls[2].Entry)[0].Max = (*Controls[0].Entry)[0].Max - PixelToNormal0(Dist);
	}

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

	window -> DefaultColor = Color(0.5f, 0.5f, 0.5f);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete window;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
