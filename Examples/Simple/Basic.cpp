
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "PolyHedra/Simple3D/PolyHedra_3D_Instances.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"

#include "PolyHedra/Skin/SkinBase.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Graphics/Texture/Base.hpp"
#include "Graphics/Texture/2DArray.hpp"
#include "Graphics/Texture/Generate.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"



#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Base.hpp"
#include "Graphics/Buffer/Attribute.hpp"
#include "Graphics/Attribute/Trans3D.hpp"
#include "PolyHedra/MainData/PolyHedra_MainAttrib.hpp"



DirectoryContext ImageDir("../../media/Images");
DirectoryContext ShaderDir("../../media/Shaders");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

YMT::PolyHedra * PH;
PolyHedra_3D_Instances * PH_Instances;
Container::Dynamic<EntryContainer::Entry<Simple3D_InstData>> Instance_Entrys;

Buffer::ArrayBase BufferArray;
Buffer::Attribute BufferMain;
Buffer::Attribute BufferInst;
PolyHedra_MainAttrib AttributeMain(0, sizeof(PolyHedra_MainData), 0, 1, 2);
Attribute::Trans3D AttributeInst(1, sizeof(Simple3D_InstData), 3, 4);



Shader::Base * PH_Shader;

Uniform::WindowBufferSize2D * Uni_WindowSize;
Uniform::Trans3D * Uni_View;
Uniform::Depth * Uni_Depth;



void InitGraphics()
{
	PH_Shader = new Shader::Base(
		Container::Base<Shader::Code>(
			(Shader::Code [])
			{
				Shader::Code(ShaderDir.File("PH_S3D.vert")),
				Shader::Code(ShaderDir.File("PH_Full.frag"))
			}, 2
		)
	);
	PH_Shader -> Compile();

	Uni_WindowSize = new Uniform::WindowBufferSize2D(Uniform::NameShader("WindowSize", *PH_Shader));
	Uni_View = new Uniform::Trans3D(Uniform::NameShader("View", *PH_Shader));
	Uni_Depth = new Uniform::Depth(Uniform::NameShader("Depth", *PH_Shader));
}
void FreeGraphics()
{
	PH_Shader -> Dispose();
	delete PH_Shader;

	delete Uni_WindowSize;
	delete Uni_View;
	delete Uni_Depth;
}



void InitRun()
{
	InitGraphics();

	PH = YMT::PolyHedra::Generate::Cube();
	PH_Instances = new PolyHedra_3D_Instances(PH);

	Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(PH_Instances -> Instances, 1));
	Instance_Entrys[0][0].Trans.Pos = Point3D(0, 0, 10);

	BufferArray.Create();
	BufferArray.Bind();

	BufferMain.Create();
	BufferMain.Attributes.Allocate(1);
	BufferMain.Attributes[0] = &AttributeMain;

	BufferInst.Create();
	BufferInst.Attributes.Allocate(1);
	BufferInst.Attributes[0] = &AttributeInst;

	{
		int count;
		PolyHedra_MainData * data = PH -> ToMainData(count);
		BufferMain.Bind(GL_ARRAY_BUFFER, sizeof(PolyHedra_MainData) * count, data, GL_STATIC_DRAW);
		BufferMain.Count = count;
		delete[] data;
	}
}
void FreeRun()
{
	for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		Instance_Entrys[i].Dispose();
	}

	BufferInst.Delete();
	BufferMain.Delete();
	BufferArray.Delete();

	delete PH_Instances;
	delete PH;

	FreeGraphics();
}



void Frame(double timeDelta)
{
	if (win -> MouseManager.CursorModeIsLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();
	//std::cout << "View " << ViewTrans.Pos << ' ' << ViewTrans.Rot << '\n';

	Instance_Entrys[0][0].Trans.Rot.X += 1.0f * timeDelta;
	Instance_Entrys[0][0].Trans.Rot.CalcBack();

	//std::cout << "Limit " << PH_Instances->Instances.Limit() << "\n";
	//std::cout << "Count " << PH_Instances->Instances.Count() << "\n";
	//std::cout << "Trans " << (PH_Instances->Instances.Data()[0].Trans.Pos) << " " << (PH_Instances->Instances.Data()[0].Trans.Rot) << "\n";
	//std::cout << "Changed " << PH_Instances->Instances.Changed << "\n";

	PH_Shader -> Bind();
	Uni_View -> PutData(ViewTrans);
	//PH_Instances -> Update().Draw();

	if (PH_Instances -> Instances.Changed)
	{
		BufferArray.Bind();
		BufferInst.Bind(GL_ARRAY_BUFFER, sizeof(Simple3D_InstData) * PH_Instances -> Instances.Count(), PH_Instances -> Instances.Data(), GL_STREAM_DRAW);
		BufferInst.Count = PH_Instances -> Instances.Count();
	}
	BufferArray.Bind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, BufferMain.Count, BufferInst.Count);
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	PH_Shader -> Bind();
	Uni_WindowSize -> PutData(WindowSize);
}



int main()
{
	Debug::NewFileInDir(DirectoryContext("logs/"));

	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	win = new Window(640, 480);
	win -> InitFunc = InitRun;
	win -> FrameFunc = Frame;
	win -> FreeFunc = FreeRun;
	win -> ResizeFunc = Resize;

	win -> DefaultColor = Color(0.5f, 0.5f, 0.5f);

	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));
	ViewDepth.Factors = DepthFactors(0.1f, 1000.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;



	Debug::Log << "<<<< Run Window" << Debug::Done;
	win -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;


	delete win;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
