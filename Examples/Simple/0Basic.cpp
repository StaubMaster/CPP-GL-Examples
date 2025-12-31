
#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

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

#include "InstanceData/Simple3D/Simple3D_InstBuffer.hpp"
#include "PolyHedra/MainData/PolyHedra_MainBuffer.hpp"

#include "Miscellaneous/Container/BehaviourShow.hpp"



#define NEW_BUFFERS
//#define OLD_BUFFERS



struct MainContext
{
DirectoryContext ImageDir;
DirectoryContext ShaderDir;

#ifdef NEW_BUFFERS
PolyHedra_MainBuffer BufferMain;
Simple3D_InstBuffer BufferInst;
Texture::Base * BufferTexture;
Buffer::ArrayBase BufferArray;
#endif

Window * win;

MainContext() :
	ImageDir("../../media/Images"),
	ShaderDir("../../media/Shaders"),
#ifdef NEW_BUFFERS
	BufferMain(0, 1, 2),
	BufferInst(3, 4),
	BufferArray(),
#endif
	win(NULL)
{ }

Trans3D	ViewTrans;
Depth	ViewDepth;

YMT::PolyHedra * PH;

#ifdef OLD_BUFFERS
PolyHedra_3D_Instances * PH_Instances;
#endif

#ifdef NEW_BUFFERS
EntryContainer::Binary<Simple3D_InstData> Instances;
#endif

Container::Binary<EntryContainer::Entry<Simple3D_InstData>> Instance_Entrys;

Shader::Base * PH_Shader;
Uniform::WindowBufferSize2D * Uni_WindowSize;
Uniform::Trans3D * Uni_View;
Uniform::Depth * Uni_Depth;



void InitGraphics()
{
	PH_Shader = new Shader::Base(
		Container::Pointer<Shader::Code>(2, (Shader::Code [])
		{
			Shader::Code(ShaderDir.File("PH_S3D.vert")),
			Shader::Code(ShaderDir.File("PH_Full.frag"))
		})
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

	#ifdef OLD_BUFFERS
	PH_Instances = new PolyHedra_3D_Instances(PH);
	Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(PH_Instances -> Instances, 1));
	Instance_Entrys[0][0].Trans.Pos = Point3D(0, 0, 10);
	#endif

	#ifdef NEW_BUFFERS
	Instance_Entrys.Insert(EntryContainer::Entry<Simple3D_InstData>(Instances, 1));
	Instance_Entrys[0][0].Trans.Pos = Point3D(0, 0, 10);
	#endif

	#ifdef NEW_BUFFERS
	BufferArray.Create();
	BufferArray.Bind();
	BufferMain.Create();
	{
		Container::Pointer<PolyHedra_MainData> data = PH -> ToMainData();
		BufferMain.Bind(data);
		data.Dispose();
		BufferTexture = PH -> Skin -> ToTexture();
	}
	BufferInst.Create();
	/*{
		Container::Pointer<Simple3D_InstData> data(PH_Instances -> Instances.Count(), PH_Instances -> Instances.Data());
		BufferInst.Bind(data);
	}*/
	#endif
}
void FreeRun()
{
	for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		Instance_Entrys[i].Dispose();
	}

	#ifdef OLD_BUFFERS
	delete PH_Instances;
	#endif

	#ifdef NEW_BUFFERS
	BufferInst.Delete();
	BufferMain.Delete();
	BufferArray.Delete();
	delete BufferTexture;
	#endif

	delete PH;

	FreeGraphics();
}

static void InitRun(void * data)
{
	MainContext * context = (MainContext *)data;
	context -> InitRun();
}
static void FreeRun(void * data)
{
	MainContext * context = (MainContext *)data;
	context -> FreeRun();
}



void Frame(double timeDelta)
{
	if (win -> Keys[GLFW_KEY_TAB].IsPress()) { win -> MouseManager.CursorModeToggle(); }
	if (win -> MouseManager.CursorModeIsLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
		if (ViewTrans.Rot.Y > Angle3D::DegreeToRadian(+90)) { ViewTrans.Rot.Y = Angle3D::DegreeToRadian(+90); }
		if (ViewTrans.Rot.Y < Angle3D::DegreeToRadian(-90)) { ViewTrans.Rot.Y = Angle3D::DegreeToRadian(-90); }
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

	#ifdef OLD_BUFFERS
	PH_Instances -> Update().Draw();
	#endif

	#ifdef NEW_BUFFERS
	if (Instances.Changed)
	{
		BufferArray.Bind();
		BufferTexture -> Bind();
		//BufferInst.Bind(GL_ARRAY_BUFFER, sizeof(Simple3D_InstData) * PH_Instances -> Instances.Count(), PH_Instances -> Instances.Data(), GL_STREAM_DRAW);
		//BufferInst.Count = PH_Instances -> Instances.Count();
		//BufferInst.Bind(PH_Instances -> Instances.Data(), PH_Instances -> Instances.Count());
		Container::Pointer<Simple3D_InstData> data(Instances.Count(), Instances.Data());
		BufferInst.Bind(data);
	}
	BufferArray.Bind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, BufferMain.DrawCount, BufferInst.DrawCount);
	#endif
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	PH_Shader -> Bind();
	Uni_WindowSize -> PutData(WindowSize);
}

static void Frame(void * data, double timeDelta)
{
	MainContext * context = (MainContext *)data;
	context -> Frame(timeDelta);
}
static void Resize(void * data, const WindowBufferSize2D & WindowSize)
{
	MainContext * context = (MainContext *)data;
	context -> Resize(WindowSize);
}



int main()
{
	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	win = new Window();
	win -> Data = this;
	win -> FrameFunc = Frame;
	win -> InitFunc = InitRun;
	win -> FreeFunc = FreeRun;
	win -> ResizeFunc = Resize;
	//win -> FrameNumberTerminate = 4;

	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));
	ViewDepth.Factors = DepthFactors(0.1f, 1000.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;



	Debug::Log << "<<<< Run Window" << Debug::Done;
	win -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete win;

	glfwTerminate();
	return 0;
}
};

int main()
{
	int ret = 1;
	Debug::NewFileInDir(DirectoryContext("logs/"));
	Debug::Log << "0 Basic" << Debug::Done;
	{
		MainContext * context = new MainContext();
		try { ret = context -> main(); }
		catch (...) { Debug::Log << "Error: " << " Unknown" << Debug::Done; }
		delete context;
	}
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
