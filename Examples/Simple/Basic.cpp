
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
#include "UserParameter/Mouse/Scroll.hpp"

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"
#include "Image.hpp"

#include <exception>



void SInitRun();
void SFreeRun();
void SFrame(double timeDelta);
void SResize(const WindowBufferSize2D & WindowSize);
void SCursorScroll(UserParameter::Mouse::Scroll params);

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
	win(NULL),
	ViewTrans(),
	ViewDepth(),
	ViewFOV(),
	_PolyHedra_3D_Manager(new PolyHedra_Simple3D::ManagerMulti()),
	PolyHedra_3D_Manager(*_PolyHedra_3D_Manager),
	_Instance_Entrys(new Container::Binary<EntryContainer::Entry<Simple3D::Data>>()),
	Instance_Entrys(*_Instance_Entrys)
{ }
~MainContext()
{
	std::cout << "deleting _PolyHedra_3D_Manager ...\n";
	delete _PolyHedra_3D_Manager;
	std::cout << "deleting _PolyHedra_3D_Manager done\n";

	std::cout << "deleting _Instance_Entrys ...\n";
	delete _Instance_Entrys;
	std::cout << "deleting _Instance_Entrys done\n";
}

Trans3D	ViewTrans;
Depth	ViewDepth;
float	ViewFOV;

PolyHedra_Simple3D::ManagerMulti * _PolyHedra_3D_Manager;
PolyHedra_Simple3D::ManagerMulti & PolyHedra_3D_Manager;

Container::Binary<EntryContainer::Entry<Simple3D::Data>> * _Instance_Entrys;
Container::Binary<EntryContainer::Entry<Simple3D::Data>> & Instance_Entrys;



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
	PolyHedra_3D_Manager.DefaultShader.Depth.Put(ViewDepth);
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
	if (win -> Keys[GLFW_KEY_TAB].IsPress()) { win -> MouseManager.CursorModeToggle(); }
	if (win -> MouseManager.CursorModeIsLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(2.0f * timeDelta), win -> SpinFromCursor(ViewFOV * 0.005f * timeDelta));
		if (ViewTrans.Rot.Y > Angle3D::DegreeToRadian(+90)) { ViewTrans.Rot.Y = Angle3D::DegreeToRadian(+90); }
		if (ViewTrans.Rot.Y < Angle3D::DegreeToRadian(-90)) { ViewTrans.Rot.Y = Angle3D::DegreeToRadian(-90); }
	}
	ViewTrans.Rot.CalcBack();

	/*for (unsigned int i = 0; i < Instance_Entrys.Count(); i++)
	{
		for (unsigned int j = 0; j < Instance_Entrys[i].Length(); j++)
		{
			Instance_Entrys[i][j].Trans.Pos = Point3D(i * 2, j * 2, 10);
			//Instance_Entrys[i][j].Trans.Rot.X += 1.0f * timeDelta;
			Instance_Entrys[i][j].Trans.Rot.CalcBack();
		}
	}*/

	float fov_rad = Angle3D::DegreeToRadian(ViewFOV);
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.View.Put(ViewTrans);
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
	if (win -> MouseManager.CursorModeIsLocked())
	{
		ViewFOV -= params.Y;
		//std::cout << "FOV " << ViewFOV << '\n';
	}
}

int Main()
{
	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	win = new Window();
	win -> FrameFunc = SFrame;
	win -> InitFunc = SInitRun;
	win -> FreeFunc = SFreeRun;
	win -> ResizeFunc = SResize;
	win -> ChangeCallback_CursorScroll(SCursorScroll);

	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));
	ViewDepth.Factors = DepthFactors(0.1f, 1000.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;
	ViewFOV = 90;

	Debug::Log << "<<<< Run Window" << Debug::Done;
	win -> Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;

	delete win;

	glfwTerminate();
	return 0;
}
};



MainContext * context;

void SInitRun() { context -> InitRun(); }
void SFreeRun() { context -> FreeRun(); }
void SFrame(double timeDelta) { context -> Frame(timeDelta); }
void SResize(const WindowBufferSize2D & WindowSize) { context -> Resize(WindowSize); }
void SCursorScroll(UserParameter::Mouse::Scroll params) { context -> CursorScroll(params); }

int main()
{
	int ret = 1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	Debug::Log << "Basic" << Debug::Done;
	{
		context = new MainContext();
		try { ret = context -> Main(); }
		catch (std::exception & ex) { Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...) { Debug::Log << "Error: " << "Unknown" << Debug::Done; }
		std::cout << "Deleting Context ...\n" << std::flush;
		delete context;
		std::cout << "Deleting Context done\n" << std::flush;
	}
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}
