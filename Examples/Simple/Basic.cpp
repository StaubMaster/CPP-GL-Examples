
#include <iostream>
#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Simple3D/ManagerMulti.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

#include "Window.hpp"
#include "ValueType/View.hpp"
#include "Function/Object.hpp"
#include "UserParameter/Mouse/Scroll.hpp"

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"
#include "Image.hpp"

#include <exception>



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo YMTDir;

Window	window;
View	view;

MainContext() :
	ImageDir("../../media/Images"),
	ShaderDir("../../media/Shaders"),
	YMTDir("../../media/YMT"),
	window(),
	view()
{ }
~MainContext()
{ }



PolyHedra_Simple3D::ManagerMulti PolyHedra_3D_Manager;
Container::Binary<EntryContainer::Entry<Simple3D::Data>> Instance_Entrys;

void InitGraphics()
{
	{
		Container::Fixed<Shader::Code> code(2);
		code.Insert(Shader::Code(ShaderDir.File("PH/Simple3D.vert")));
		code.Insert(Shader::Code(ShaderDir.File("PH/Full.frag")));
		PolyHedra_3D_Manager.DefaultShader.Change(code);
		code.Dispose();
	}
	PolyHedra_3D_Manager.DefaultShader.Create();
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.Depth.Put(view.Depth);
}
void FreeGraphics()
{ }



void InitRun()
{
	InitGraphics();

	Image img;
	PolyHedra * PH;

	EntryContainer::Entry<Simple3D::Data> entry;

	img = ImageDir.File("Test.png").LoadImage();
	PH = PolyHedra::Generate::FramedImage(img);
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(0, 0, 1);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);

	img = ImageDir.File("Text_16x8_32x32.png").LoadImage();
	PH = PolyHedra::Generate::FramedImage(img);
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(2, 3.2, 1);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);

	img = ImageDir.File("Sender-Weinsberg-Steinbruchweg_small.png").LoadImage(true);
	/*{
		FileInfo file = ImageDir.File("Sender-Weinsberg-Steinbruchweg.png");
		std::cout << "PNG ...\n";
		double Time0 = glfwGetTime();
		img = file.LoadImage(false);
		double Time1 = glfwGetTime();
		std::cout << "Time " << (Time1 - Time0) << '\n';
		std::cout << "PNG done\n";
	}*/
	PH = PolyHedra::Generate::FramedImage(img);
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(-5.2, 0, 1);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);

	img = YMTDir.File("Light/ChairCloth.png").LoadImage();
	PH = PolyHedra::Generate::FramedImage(img, 8);
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(0, -2.5f, 1);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);

	img = YMTDir.File("Light/ChairMetal.png").LoadImage(true);
	PH = PolyHedra::Generate::FramedImage(img, 8);
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(2.5f, -2.5f, 1);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);

	PH = PolyHedra::Load(YMTDir.File("Light/Chair.polyhedra.ymt"));
	entry = PolyHedra_3D_Manager.Place(PH, 1);
	entry[0].Trans.Pos = Point3D(0, -10, -10);
	entry[0].Trans.Rot = Angle3D(0, 0, 0);
	entry[0].Trans.Rot.CalcBack();
	Instance_Entrys.Insert(entry);
}
void FreeRun()
{
	for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		Instance_Entrys[i].Dispose();
	}
	PolyHedra_3D_Manager.Dispose();

	FreeGraphics();
}

void Frame(double timeDelta)
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_TAB].IsPress()) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 10; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV * 0.005f;
		trans.Rot.Y *= view.FOV * 0.005f;
		trans.Rot.Z *= view.FOV * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}

	/*for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		for (unsigned int j = 0; j < Instance_Entrys[i].Length(); j++)
		{
			Instance_Entrys[i][j].Trans.Pos = Point3D(i * 2, j * 2, 10);
			//Instance_Entrys[i][j].Trans.Rot.X += 1.0f * timeDelta;
			Instance_Entrys[i][j].Trans.Rot.CalcBack();
		}
	}*/

	float fov_rad = Angle3D::DegreeToRadian(view.FOV);
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.View.Put(view.Trans);
	PolyHedra_3D_Manager.DefaultShader.FOV.PutData(&fov_rad);

	PolyHedra_3D_Manager.Draw();
}
void Resize(const WindowBufferSize2D & WindowSize)
{
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.WindowSize.Put(WindowSize);
}

void CursorScroll(UserParameter::Mouse::Scroll params)
{
	if (window.MouseManager.CursorModeIsLocked())
	{
		view.FOV -= params.Y;
		//std::cout << "FOV " << ViewFOV << '\n';
	}
}

int Main()
{
	window.Create();
	window.InitCallBack.Change(this, &MainContext::InitRun);
	window.FreeCallBack.Change(this, &MainContext::FreeRun);
	window.FrameCallBack.Change(this, &MainContext::Frame);
	window.ResizeCallBack.Change(this, &MainContext::Resize);
	window.MouseManager.CallbackScroll.Change(this, &MainContext::CursorScroll);

	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	window.Delete();

	return 0;
}
};



int main(int argc, char * argv[])
{
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			MainContext context;
			ret = context.Main();
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	glfwTerminate();
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
