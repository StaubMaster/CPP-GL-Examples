
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"

#include "DataShow.hpp"
#include "Miscellaneous/ContainerDynamic.hpp"

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
	Color Col;

	UI_Inst_Data() { }
	UI_Inst_Data(Point2D min, Point2D max, Color col) :
		Min(min),
		Max(max),
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
		Attribute::Color	Col;
	public:
		UI_Inst_Attribute(
			unsigned int divisor,
			unsigned int stride,
			unsigned int indexMin,
			unsigned int indexMax,
			unsigned int indexCol
		) :
			Min(divisor, stride, indexMin),
			Max(divisor, stride, indexMax),
			Col(divisor, stride, indexCol)
		{ }
	public:
		void Bind(const unsigned char * & offset) const override
		{
			Min.Bind(offset);
			Max.Bind(offset);
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
			Inst(1, (Attribute::Base * []) { new UI_Inst_Attribute(1, sizeof(UI_Inst_Data), 1, 2, 3) })
		{ }

	public:
		void Draw() override
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, Main.Count, Inst.Count);
		}
};
UI_BufferArray * UI_BufferArray_;

ContainerDynamic<UI_Main_Data> UI_Main_Data_C;
ContainerDynamic<UI_Inst_Data> UI_Inst_Data_C;



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

	UI_Inst_Data_C.Insert(UI_Inst_Data(Point2D(-0.75, -0.75), Point2D(-0.25, -0.25), Color(1, 0, 0)));
	UI_Inst_Data_C.Insert(UI_Inst_Data(Point2D(-0.25, -0.25), Point2D(+0.25, +0.25), Color(0, 1, 0)));
	UI_Inst_Data_C.Insert(UI_Inst_Data(Point2D(+0.25, +0.25), Point2D(+0.75, +0.75), Color(0, 0, 1)));
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

	UI_BufferArray_ -> Use();
	UI_BufferArray_ -> Main.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI_Main_Data) * UI_Main_Data_C.Count(), UI_Main_Data_C.ToPointer(), GL_STREAM_DRAW);
	UI_BufferArray_ -> Main.Count = UI_Main_Data_C.Count();
	UI_BufferArray_ -> Inst.BindData(GL_ARRAY_BUFFER, 0, sizeof(UI_Inst_Data) * UI_Inst_Data_C.Count(), UI_Inst_Data_C.ToPointer(), GL_STREAM_DRAW);
	UI_BufferArray_ -> Inst.Count = UI_Inst_Data_C.Count();
	UI_BufferArray_ -> Draw();
}

void Resize(int w, int h)
{
	Multi_ViewPortSizeRatio -> ChangeData(SizeRatio2D(w, h));
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
