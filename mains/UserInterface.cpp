
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

float Normal0ToPixel(float val, float size)
{
	//	Normal [ 0 ; 1 ]
	//	Pixel [ 0 ; n ]
	return val * size;
}
float PixelToNormal0(float val, float size)
{
	//	Pixel [ 0 ; n ]
	//	Normal [ 0 ; 1 ]
	return val / size;
}
float Normal0ToNormal1(float val)
{
	//	Normal0 [ 0 ; 1 ]
	//	Normal1 [ -1 ; +1 ]
	return (val * 2) - 1;
}
float Normal1ToNormal0(float val)
{
	//	Normal1 [ -1 ; +1 ]
	//	Normal0 [ 0 ; 1 ]
	return (val + 1) / 2;
}

Point2D Normal0ToPixel(Point2D p)
{
	p.X = Normal0ToPixel(p.X, ViewPortSizeRatio.W);
	p.Y = Normal0ToPixel(p.Y, ViewPortSizeRatio.H);
	return p;
}
Point2D PixelToNormal0(Point2D p)
{
	p.X = PixelToNormal0(p.X, ViewPortSizeRatio.W);
	p.Y = PixelToNormal0(p.Y, ViewPortSizeRatio.H);
	return p;
}
Point2D Normal0ToNormal1(Point2D p)
{
	p.X = Normal0ToNormal1(p.X);
	p.Y = Normal0ToNormal1(p.Y);
	return p;
}
Point2D Normal1ToNormal0(Point2D p)
{
	p.X = Normal1ToNormal0(p.X);
	p.Y = Normal1ToNormal0(p.Y);
	return p;
}

#define ANCHOR_NONE 0b00
#define ANCHOR_MIN  0b01
#define ANCHOR_MAX  0b10
#define ANCHOR_BOTH 0b11

struct AxisBox1D
{
	float Min;
	float Max;

	AxisBox1D() : Min(0), Max(0) { }
	AxisBox1D(float min, float max) : Min(min), Max(max) { }
};

struct AxisBox2D
{
	Point2D Min;
	Point2D Max;

	AxisBox2D() : Min(), Max() { }
	AxisBox2D(Point2D min, Point2D max) : Min(min), Max(max) { }

	bool Intersekt(Point2D p) const
	{
		return (Min.X <= p.X && Max.X >= p.X)
			&& (Min.Y <= p.Y && Max.Y >= p.Y);
	}
};

struct ControlAnchor
{
	unsigned char Anchor;

	AxisBox1D Update(AxisBox1D Dist, float Size, float NormalCenter, AxisBox1D Parent)
	{
		AxisBox1D child;
		if (Anchor == ANCHOR_NONE)
		{
			float t0 = (NormalCenter - 0);
			float t1 = (1 - NormalCenter);
			float center = (Parent.Min * t0) + (Parent.Max * t1);
			child.Min = center - Size;
			child.Max = center + Size;
		}
		else if (Anchor == ANCHOR_MIN)
		{
			child.Min = Parent.Min + Dist.Min;
			child.Max = Parent.Min + Dist.Min + Size;
		}
		else if (Anchor == ANCHOR_MAX)
		{
			child.Min = Parent.Max - Dist.Max - Size;
			child.Max = Parent.Max - Dist.Max;
		}
		else if (Anchor == ANCHOR_BOTH)
		{
			child.Min = Parent.Min + Dist.Min;
			child.Max = Parent.Max - Dist.Max;
		}
		return child;
	}
};

/*
how should Controls store its Boxes
need Pixel Size for storing
need NormalSize for recalculating
need NormalSize in Anchors
*/

/*	Anchoring
None:
	takes: Size, NormalCenter, (Parent.Min, Parent.Max)
	calcs: MinDist, MaxDist
Min:
	takes: MinDist, Size, (Parent.Min)
	calcs: MaxDist, NormalCenter
Max:
	takes: MaxDist, Size, (Parent.Max)
	calcs: MinDist, NormalCenter
Both:
	takes: MinDist, MaxDist, (Parent.Min, Parent.Max)
	calcs: Size, NormalCenter
*/

/*	Absolute
	MinDist and MaxDist are relative
	should I calculate the absolute Pixel Pos
	and then the Normal stuff
	dont really need that ?

	it would ne more consistent
	and I would only need to normalize at the end
	maybe even in the shader

	but to I want thing from 0 to 1 (0 to n) or -1 to +1 (-n/2 to +n/2)
*/

class Control
{
	public:
		EntryContainerDynamic<UI_Inst_Data>::Entry * Entry;
		ContainerDynamic<Control *> Children;

		ControlAnchor	AnchorX;
		ControlAnchor	AnchorY;

		Point2D			PixelMinDist;
		Point2D			PixelSize;
		Point2D			PixelMaxDist;

		//	AxisBox2D
		Point2D			PixelMin;
		Point2D			PixelMax;

		Point2D			NormalCenter;

		float			Layer;

		Color			ColorDefault;
		Color			ColorHover;

	public:
		Control(EntryContainerDynamic<UI_Inst_Data>::Entry * entry) :
			Entry(entry)
		{ }
		~Control()
		{
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				delete Children[i];
			}
		}

	public:
		void UpdateBoxChildren()
		{
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				Children[i] -> UpdateBox(PixelMin, PixelMax);
			}
		}
		void UpdateBox(const Point2D & Min, const Point2D & Max)
		{
			AxisBox1D posX = AnchorX.Update(
				AxisBox1D(PixelMinDist.X, PixelMaxDist.X),
				PixelSize.X,
				NormalCenter.X,
				AxisBox1D(Min.X, Max.X)
			);

			AxisBox1D posY = AnchorY.Update(
				AxisBox1D(PixelMinDist.Y, PixelMaxDist.Y),
				PixelSize.Y,
				NormalCenter.Y,
				AxisBox1D(Min.Y, Max.Y)
			);

			PixelMin.X = posX.Min;
			PixelMax.X = posX.Max;
			PixelMin.Y = posY.Min;
			PixelMax.Y = posY.Max;

			if (Entry != NULL)
			{
				(*Entry)[0].Min = PixelToNormal0(PixelMin);
				(*Entry)[0].Max = PixelToNormal0(PixelMax);
			}

			UpdateBoxChildren();
		}

	public:
		void UpdateDefault()
		{
			if (Entry != NULL)
			{
				(*Entry)[0].Layer = Layer;
				(*Entry)[0].Col = ColorDefault;
			}
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				Children[i] -> UpdateDefault();
			}
		}
		bool UpdateHover(Point2D mouse)
		{
			AxisBox2D box(PixelMin, PixelMax);
			if (box.Intersekt(mouse))
			{
				unsigned int hover_idx = 0xFFFFFFFF;
				for (unsigned int i = 0; i < Children.Count(); i++)
				{
					if (Children[i] -> UpdateHover(mouse))
					{
						hover_idx = i;
					}
				}

				if (hover_idx != 0xFFFFFFFF)
				{
					if (Entry != NULL)
					{
						(*Entry)[0].Col = ColorDefault;
					}
				}
				else
				{
					if (Entry != NULL)
					{
						(*Entry)[0].Col = ColorHover;
					}
				}
				return true;
			}

			if (Entry != NULL)
			{
				(*Entry)[0].Col = ColorDefault;
			}
			return false;
		}
};

Control * WindowControl;

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



	//WindowControl = new Control(UI_Inst_Data_C.Alloc(1));
	WindowControl = new Control(NULL);
	WindowControl -> AnchorX.Anchor = ANCHOR_BOTH;
	WindowControl -> AnchorY.Anchor = ANCHOR_BOTH;
	WindowControl -> PixelMinDist = Point2D(0, 0);
	WindowControl -> PixelSize = Point2D(480, 360);
	WindowControl -> PixelMaxDist = Point2D(0, 0);
	WindowControl -> NormalCenter = Point2D(0, 0);
	WindowControl -> Layer = 0.3f;
	WindowControl -> ColorDefault = Color(0.25f, 0.25f, 0.25f);
	WindowControl -> ColorHover = Color(0.25f, 0.25f, 0.25f);

	Control * control;

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> AnchorX.Anchor = ANCHOR_NONE;
	control -> AnchorY.Anchor = ANCHOR_NONE;
	control -> PixelMinDist = Point2D(24, 24);
	control -> PixelSize = Point2D(480, 360);
	control -> PixelMaxDist = Point2D(24, 24);
	control -> NormalCenter = Point2D(0.5, 0.5);
	control -> Layer = 0.2f;
	control -> ColorDefault = Color(0.75f, 0.75f, 0.75f);
	control -> ColorHover = Color(0.75f, 0.75f, 0.75f);
	WindowControl -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> AnchorX.Anchor = ANCHOR_MIN;
	control -> AnchorY.Anchor = ANCHOR_MIN;
	control -> PixelMinDist = Point2D(24, 24);
	control -> PixelSize = Point2D(240, 120);
	control -> PixelMaxDist = Point2D(24, 24);
	control -> NormalCenter = Point2D(0, 0);
	control -> Layer = 0.1f;
	control -> ColorDefault = Color(0.625f, 0.625f, 0.625f);
	control -> ColorHover = Color(0.5f, 0.5f, 0.5f);
	WindowControl -> Children[0] -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> AnchorX.Anchor = ANCHOR_MAX;
	control -> AnchorY.Anchor = ANCHOR_MAX;
	control -> PixelMinDist = Point2D(24, 24);
	control -> PixelSize = Point2D(240, 120);
	control -> PixelMaxDist = Point2D(24, 24);
	control -> NormalCenter = Point2D(0, 0);
	control -> Layer = 0.1f;
	control -> ColorDefault = Color(0.625f, 0.625f, 0.625f);
	control -> ColorHover = Color(0.5f, 0.5f, 0.5f);
	WindowControl -> Children[0] -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> AnchorX.Anchor = ANCHOR_BOTH;
	control -> AnchorY.Anchor = ANCHOR_NONE;
	control -> PixelMinDist = Point2D(24, 24);
	control -> PixelSize = Point2D(120, 120);
	control -> PixelMaxDist = Point2D(24, 24);
	control -> NormalCenter = Point2D(0.5, 0.5);
	control -> Layer = 0.1f;
	control -> ColorDefault = Color(0.625f, 0.625f, 0.625f);
	control -> ColorHover = Color(0.5f, 0.5f, 0.5f);
	WindowControl -> Children[0] -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> AnchorX.Anchor = ANCHOR_MIN;
	control -> AnchorY.Anchor = ANCHOR_NONE;
	control -> PixelMinDist = Point2D(24, 24);
	control -> PixelSize = Point2D(120, 360);
	control -> PixelMaxDist = Point2D(24, 24);
	control -> NormalCenter = Point2D(0, 0.5);
	control -> Layer = 0.2f;
	control -> ColorDefault = Color(0.75f, 0.75f, 0.75f);
	control -> ColorHover = Color(0.75f, 0.75f, 0.75f);
	WindowControl -> Children.Insert(control);

	control = new Control(UI_Inst_Data_C.Alloc(1));
	control -> AnchorX.Anchor = ANCHOR_MAX;
	control -> AnchorY.Anchor = ANCHOR_BOTH;
	control -> PixelMinDist = Point2D(24, 24);
	control -> PixelSize = Point2D(120, 360);
	control -> PixelMaxDist = Point2D(24, 24);
	control -> NormalCenter = Point2D(0, 0);
	control -> Layer = 0.2f;
	control -> ColorDefault = Color(0.75f, 0.75f, 0.75f);
	control -> ColorHover = Color(0.75f, 0.75f, 0.75f);
	WindowControl -> Children.Insert(control);

	WindowControl -> UpdateDefault();
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

	WindowControl -> UpdateBox(Point2D(-ViewPortSizeRatio.W, -ViewPortSizeRatio.H), Point2D(+ViewPortSizeRatio.W, +ViewPortSizeRatio.H));
	Point2D mouse = window -> CursorPixel();
	mouse.X = (mouse.X * 2) - ViewPortSizeRatio.W;
	mouse.Y = ViewPortSizeRatio.H - (mouse.Y * 2);
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
