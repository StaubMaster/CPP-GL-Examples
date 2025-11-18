
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

#define ANCHOR_Y_MASK 0b1100
#define ANCHOR_Y_NONE 0b0000
#define ANCHOR_Y_MIN  0b0100
#define ANCHOR_Y_MAX  0b1000
#define ANCHOR_Y_BOTH 0b1100

class Control
{
	public:
		EntryContainerDynamic<UI_Inst_Data>::Entry * Entry;

		unsigned int	Anchor;
		Point2D			MinDist;
		Point2D			LenDist;
		Point2D			MaxDist;
		Point2D			NormalCenter;

	public:
		Control() { }
		Control(EntryContainerDynamic<UI_Inst_Data>::Entry * entry) :
			Entry(entry)
		{ }
	public:
		void Update(const Control * Parent)
		{
			Point2D NormalMinDist = PixelToNormal0(MinDist);
			Point2D NormalLenDist = PixelToNormal0(LenDist);
			Point2D NormalMaxDist = PixelToNormal0(MaxDist);

			{
				unsigned int anchor_x = Anchor & ANCHOR_X_MASK;
				if (anchor_x == ANCHOR_X_NONE)
				{
					if (Parent != NULL)
					{
						float t0 = (NormalCenter.X - 0);
						float t1 = (1 - NormalCenter.X);
						float center_x = ((*(*Parent).Entry)[0].Min.X * t0) + ((*(*Parent).Entry)[0].Max.X * t1);
						(*Entry)[0].Min.X = center_x - (NormalLenDist.X / 2);
						(*Entry)[0].Max.X = center_x + (NormalLenDist.X / 2);
					}
					else
					{
						(*Entry)[0].Min.X = NormalCenter.X - (NormalLenDist.X);
						(*Entry)[0].Max.X = NormalCenter.X + (NormalLenDist.X);
					}
				}
				else if (anchor_x == ANCHOR_X_MIN)
				{
					if (Parent != NULL)
					{
						(*Entry)[0].Min.X = (*(*Parent).Entry)[0].Min.X + NormalMinDist.X;
						(*Entry)[0].Max.X = (*(*Parent).Entry)[0].Min.X + NormalMinDist.X + NormalLenDist.X;
					}
					else
					{
						(*Entry)[0].Min.X = -1 + NormalMinDist.X;
						(*Entry)[0].Max.X = -1 + NormalMinDist.X + NormalLenDist.X;
					}
				}
				else if (anchor_x == ANCHOR_X_MAX)
				{
					if (Parent != NULL)
					{
						(*Entry)[0].Min.X = (*(*Parent).Entry)[0].Max.X - NormalMaxDist.X - NormalLenDist.X;
						(*Entry)[0].Max.X = (*(*Parent).Entry)[0].Max.X - NormalMaxDist.X;
					}
					else
					{
						(*Entry)[0].Min.X = +1 - NormalMaxDist.X - NormalLenDist.X;
						(*Entry)[0].Max.X = +1 - NormalMaxDist.X;
					}
				}
				else if (anchor_x == ANCHOR_X_BOTH)
				{
					if (Parent != NULL)
					{
						(*Entry)[0].Min.X = (*(*Parent).Entry)[0].Min.X + NormalMinDist.X;
						(*Entry)[0].Max.X = (*(*Parent).Entry)[0].Max.X - NormalMaxDist.X;
					}
					else
					{
						(*Entry)[0].Min.X = -1 + NormalMinDist.X;
						(*Entry)[0].Max.X = +1 - NormalMaxDist.X;
					}
				}
			}

			{
				unsigned int anchor_y = Anchor & ANCHOR_Y_MASK;
				if (anchor_y == ANCHOR_Y_NONE)
				{
					if (Parent != NULL)
					{
						float t0 = (NormalCenter.Y - 0);
						float t1 = (1 - NormalCenter.Y);
						float center_y = ((*(*Parent).Entry)[0].Min.Y * t0) + ((*(*Parent).Entry)[0].Max.Y * t1);
						(*Entry)[0].Min.Y = center_y - (NormalLenDist.Y / 2);
						(*Entry)[0].Max.Y = center_y + (NormalLenDist.Y / 2);
					}
					else
					{
						(*Entry)[0].Min.Y = NormalCenter.Y - (NormalLenDist.Y);
						(*Entry)[0].Max.Y = NormalCenter.Y + (NormalLenDist.Y);
					}
				}
				else if (anchor_y == ANCHOR_Y_MIN)
				{
					if (Parent != NULL)
					{
						(*Entry)[0].Min.Y = (*(*Parent).Entry)[0].Min.Y + NormalMinDist.Y;
						(*Entry)[0].Max.Y = (*(*Parent).Entry)[0].Min.Y + NormalMinDist.Y + NormalLenDist.Y;
					}
					else
					{
						(*Entry)[0].Min.Y = -1 + NormalMinDist.Y;
						(*Entry)[0].Max.Y = -1 + NormalMinDist.Y + NormalLenDist.Y;
					}
				}
				else if (anchor_y == ANCHOR_Y_MAX)
				{
					if (Parent != NULL)
					{
						(*Entry)[0].Min.Y = (*(*Parent).Entry)[0].Max.Y - NormalMaxDist.Y - NormalLenDist.Y;
						(*Entry)[0].Max.Y = (*(*Parent).Entry)[0].Max.Y - NormalMaxDist.Y;
					}
					else
					{
						(*Entry)[0].Min.Y = +1 - NormalMaxDist.Y - NormalLenDist.Y;
						(*Entry)[0].Max.Y = +1 - NormalMaxDist.Y;
					}
				}
				else if (anchor_y == ANCHOR_Y_BOTH)
				{
					if (Parent != NULL)
					{
						(*Entry)[0].Min.Y = (*(*Parent).Entry)[0].Min.Y + NormalMinDist.Y;
						(*Entry)[0].Max.Y = (*(*Parent).Entry)[0].Max.Y - NormalMaxDist.Y;
					}
					else
					{
						(*Entry)[0].Min.Y = -1 + NormalMinDist.Y;
						(*Entry)[0].Max.Y = +1 - NormalMaxDist.Y;
					}
				}
			}
		}
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
	Controls[idx].Anchor = ANCHOR_X_NONE | ANCHOR_Y_NONE;
	Controls[idx].MinDist = Point2D(24, 24);
	Controls[idx].LenDist = Point2D(480, 360);
	Controls[idx].MaxDist = Point2D(24, 24);
	Controls[idx].NormalCenter = Point2D(0, 0);

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.1f, Color(0, 1, 0));
	Controls[idx].Anchor = ANCHOR_X_MIN | ANCHOR_Y_MIN;
	Controls[idx].MinDist = Point2D(24, 24);
	Controls[idx].LenDist = Point2D(240, 120);
	Controls[idx].MaxDist = Point2D(24, 24);
	Controls[idx].NormalCenter = Point2D(0, 0);

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.1f, Color(0, 1, 0));
	Controls[idx].Anchor = ANCHOR_X_MAX | ANCHOR_Y_MAX;
	Controls[idx].MinDist = Point2D(24, 24);
	Controls[idx].LenDist = Point2D(240, 120);
	Controls[idx].MaxDist = Point2D(24, 24);
	Controls[idx].NormalCenter = Point2D(0, 0);

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.1f, Color(0, 0, 1));
	Controls[idx].Anchor = ANCHOR_X_BOTH | ANCHOR_Y_NONE;
	Controls[idx].MinDist = Point2D(24, 24);
	Controls[idx].LenDist = Point2D(120, 120);
	Controls[idx].MaxDist = Point2D(24, 24);
	Controls[idx].NormalCenter = Point2D(0.5, 0.5);

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.2f, Color(0, 1, 0));
	Controls[idx].Anchor = ANCHOR_X_MIN | ANCHOR_Y_NONE;
	Controls[idx].MinDist = Point2D(24, 24);
	Controls[idx].LenDist = Point2D(120, 360);
	Controls[idx].MaxDist = Point2D(24, 24);
	Controls[idx].NormalCenter = Point2D(0, 0);

	idx = Controls.Insert(Control(UI_Inst_Data_C.Alloc(1)));
	(*Controls[idx].Entry)[0] = UI_Inst_Data(Point2D(), Point2D(), 0.2f, Color(0, 0, 1));
	Controls[idx].Anchor = ANCHOR_X_MAX | ANCHOR_Y_BOTH;
	Controls[idx].MinDist = Point2D(24, 24);
	Controls[idx].LenDist = Point2D(120, 360);
	Controls[idx].MaxDist = Point2D(24, 24);
	Controls[idx].NormalCenter = Point2D(0, 0);
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

	Controls[0].Update(NULL);
	Controls[1].Update(&(Controls[0]));
	Controls[2].Update(&(Controls[0]));
	Controls[3].Update(&(Controls[0]));
	Controls[4].Update(NULL);
	Controls[5].Update(NULL);

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

	window -> DefaultColor = Color(0.5f, 0.5f, 0.5f);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete window;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
