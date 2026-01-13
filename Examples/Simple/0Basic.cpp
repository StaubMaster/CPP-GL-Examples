
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

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"

#include "PolyHedra/Skin/SkinBase.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Graphics/Texture/Base.hpp"
#include "Graphics/Texture/Array2D.hpp"
#include "Graphics/Texture/Generate.hpp"

#include "Window.hpp"
#include "UserParameter/Mouse/Scroll.hpp"

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"
#include "Image.hpp"



#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Base.hpp"
#include "Graphics/Buffer/Attribute.hpp"
#include "Graphics/Attribute/Trans3D.hpp"

//#include "InstanceData/Simple3D/Simple3D_InstBuffer.hpp"
//#include "PolyHedra/MainData/PolyHedra_MainBuffer.hpp"
#include "PolyHedra/Simple3D/ManagerSingle.hpp"
#include "PolyHedra/Simple3D/ManagerMulti.hpp"
#include "PolyHedra/Simple3D/PolyHedra_3D_Instances.hpp"

#include "Miscellaneous/Container/BehaviourShow.hpp"

#include <math.h>



void CursorScroll(UserParameter::Mouse::Scroll params);

struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo YMTDir;

Window * win;

MainContext() :
	ImageDir("../../media/Images"),
	ShaderDir("../../media/Shaders"),
	YMTDir("../../media/YMT"),
	win(NULL)
{ }

Trans3D	ViewTrans;
Depth	ViewDepth;
float	ViewFOV = 90;

//PolyHedra_3D_Instances * PH_Instances;

//Shader::Base * PH_Shader;
//Uniform::WindowBufferSize2D * Uni_WindowSize;
//Uniform::Trans3D * Uni_View;
//Uniform::Depth * Uni_Depth;

PolyHedra_Simple3D::ManagerMulti PolyHedra_3D_Manager;

Container::Binary<EntryContainer::Entry<Simple3D::Data>> Instance_Entrys;



void InitGraphics()
{
	//PH_Shader = new Shader::Base(
	//	Container::Pointer<Shader::Code>(2, (Shader::Code [])
	//	{
	//		Shader::Code(ShaderDir.File("PH_S3D.vert")),
	//		Shader::Code(ShaderDir.File("PH_Full.frag"))
	//	})
	//);
	//Uni_WindowSize = new Uniform::WindowBufferSize2D(Uniform::NameShader("WindowSize", *PH_Shader));
	//Uni_View = new Uniform::Trans3D(Uniform::NameShader("View", *PH_Shader));
	//Uni_Depth = new Uniform::Depth(Uniform::NameShader("Depth", *PH_Shader));

	PolyHedra_3D_Manager.DefaultShader.Change(
		Container::Pointer<Shader::Code>(2, (Shader::Code [])
		{
			Shader::Code(ShaderDir.File("PH_S3D.vert")),
			Shader::Code(ShaderDir.File("PH_Full.frag"))
		})
	);
	PolyHedra_3D_Manager.DefaultShader.Create();
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.Depth.Put(ViewDepth);
}
void FreeGraphics()
{
	//PH_Shader -> Delete();
	//delete PH_Shader;
	//delete Uni_WindowSize;
	//delete Uni_View;
	//delete Uni_Depth;
}



void InitRun()
{
	InitGraphics();

	Image img;
	PolyHedra * PH;

	//PH_Instances = new PolyHedra_3D_Instances();
	//PH_Instances -> Create();
	//PH_Instances -> SetPolyHedra(PH);
	//Instance_Entrys.Insert(EntryContainer::Entry<Simple3D::Data>(*(PH_Instances -> Instances), 1));

	EntryContainer::Entry<Simple3D::Data> entry;

	img = ImageDir.File("Test.png").LoadImage();
	{
		//FileInfo file(R"(F:\Code\GitRepositorys\C++\CPP-GL-Examples\other\Engine\media\Images\Wood.png)");
		//FileInfo file(R"(F:\Code\GitRepositorys\C++\CPP-GL-Examples\other\Engine\media\Images\Cloth.png)");
		//img = file.LoadImage();
		//img = Texture::Generate::Wood16x16();
		/*std::cout << "[ " << img.W() << " | " << img.H() << " ]\n";
		uint32 col;
		for (unsigned int y = 0; y < img.H(); y++)
		{
			for (unsigned int x = 0; x < img.W(); x++)
			{
				col = img.Pixel(x, y).ToUInt32_RGBA();
				std::cout << "0x" << ToBase16(col) << ", ";
			}
			std::cout << '\n';
		}*/
	}
	//PolyHedra * PH = PolyHedra::Generate::HexaHedron();
	//PH = PolyHedra::Generate::DuoHedra(img);
	PH = PolyHedra::Generate::FramedImage(img);
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(0, 0, 1);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);

	//PH = PolyHedra::Load(YMTDir.File("test/cube.polyhedra.ymt"));
	//entry = PolyHedra_3D_Manager.Place(PH, 1);
	//entry[0].Trans.Pos = Point3D(0, 0, 0);
	//entry[0].Trans.Rot = Angle3D(0, 0, 0);
	//entry[0].Trans.Rot.CalcBack();
	//Instance_Entrys.Insert(entry);

	PolyHedra_3D_Manager.DefaultShader.LogInfo();
}
void FreeRun()
{
	for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		Instance_Entrys[i].Dispose();
	}

	//PH_Instances -> Delete();
	//delete PH_Instances;
	
	PolyHedra_3D_Manager.Clear();

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



void CursorScroll(UserParameter::Mouse::Scroll params)
{
	if (win -> MouseManager.CursorModeIsLocked())
	{
		ViewFOV -= params.Y;
		//std::cout << "FOV " << ViewFOV << '\n';
	}
}

void Frame(double timeDelta)
{
	if (win -> Keys[GLFW_KEY_TAB].IsPress()) { win -> MouseManager.CursorModeToggle(); }
	if (win -> MouseManager.CursorModeIsLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(2.0f * timeDelta), win -> SpinFromCursor(ViewFOV * 0.005f * timeDelta));
		if (ViewTrans.Rot.Y > Angle3D::DegreeToRadian(+90)) { ViewTrans.Rot.Y = Angle3D::DegreeToRadian(+90); }
		if (ViewTrans.Rot.Y < Angle3D::DegreeToRadian(-90)) { ViewTrans.Rot.Y = Angle3D::DegreeToRadian(-90); }
	}
	ViewTrans.Rot.CalcBack();
	//std::cout << "View " << ViewTrans.Pos << ' ' << ViewTrans.Rot << '\n';

	/*for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		for (unsigned int j = 0; j < Instance_Entrys[i].Length(); j++)
		{
			Instance_Entrys[i][j].Trans.Pos = Point3D(i * 2, j * 2, 10);
			//Instance_Entrys[i][j].Trans.Rot.X += 1.0f * timeDelta;
			Instance_Entrys[i][j].Trans.Rot.CalcBack();
		}
	}*/

	//std::cout << "Limit " << PH_Instances->Instances.Limit() << "\n";
	//std::cout << "Count " << PH_Instances->Instances.Count() << "\n";
	//std::cout << "Trans " << (PH_Instances->Instances.Data()[0].Trans.Pos) << " " << (PH_Instances->Instances.Data()[0].Trans.Rot) << "\n";
	//std::cout << "Changed " << PH_Instances->Instances.Changed << "\n";

	//PH_Shader -> Bind();
	//Uni_View -> PutData(ViewTrans);
	float fov_rad = Angle3D::DegreeToRadian(ViewFOV);
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.View.Put(ViewTrans);
	PolyHedra_3D_Manager.DefaultShader.FOV.PutData(&fov_rad);

	//PH_Instances -> Draw();
	PolyHedra_3D_Manager.Draw();
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	//PH_Shader -> Bind();
	//Uni_WindowSize -> PutData(WindowSize);
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.WindowSize.Put(WindowSize);
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
	win -> ChangeCallback_CursorScroll(::CursorScroll);
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

MainContext * context;

void CursorScroll(UserParameter::Mouse::Scroll params) { context -> CursorScroll(params); }

int main()
{
	int ret = 1;
	Debug::NewFileInDir(DirectoryInfo("logs/"));
	Debug::Log << "0 Basic" << Debug::Done;
	{
		context = new MainContext();
		try { ret = context -> main(); }
		catch (...) { Debug::Log << "Error: " << " Unknown" << Debug::Done; }
		delete context;
	}
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
