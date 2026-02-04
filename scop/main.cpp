#include "OpenGL.hpp"

#include "Wavefront/OBJ.hpp"
#include "Wavefront/Main/Data.hpp"
#include "Wavefront/Simple3D/BufferArray.hpp"
#include "Wavefront/Simple3D/Shader.hpp"

#include "InstanceData/Simple3D/Data.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Texture/Array2D.hpp"
#include "Miscellaneous/Container/Pointer.hpp"

#include "ValueType/View.hpp"
#include "Window.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include "Function/Static.hpp"

#include "Debug.hpp"
#include <iostream>



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;

Window		window;
View		view;

MainContext() :
	ImageDir("./media/Images"),
	ShaderDir("./media/Shaders"),
	window(),
	view()
{ }
~MainContext()
{ }



Wavefront::Simple3D::Shader OBJ_Shader;
Texture::Array2D Tex0;
bool	Spinning;

int OBJ_Limit;
int OBJ_Count;
Wavefront::OBJ ** OBJs;
Point3D * OBJs_Center;
Trans3D * OBJs_Trans;

Wavefront::Simple3D::BufferArray ** OBJ_BufferArray;

LInter ColorToTex;
float ColorToTex_Speed = 0.01f;
bool ColorToTex_Direction = false;
bool ColorToTex_Direction_last = false;

LInter ShowLightFactor;
float ShowLightFactor_Speed = 0.01f;
bool ShowLightFactor_Direction = false;
bool ShowLightFactor_Direction_last = false;

void InitShaders()
{
	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("OBJ.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("OBJ.frag")));
		OBJ_Shader.Change(code);
	}
	OBJ_Shader.Create();
	OBJ_Shader.Depth.Put(view.Depth);

	ColorToTex = LInter::T0();
	ColorToTex_Direction = false;

	ShowLightFactor = LInter::T1();
	ShowLightFactor_Direction = true;
	ShowLightFactor_Direction_last = true;

	OBJ_Shader.Bind();
	OBJ_Shader.Depth.Put(view.Depth);
	OBJ_Shader.ColorToTex.Put(ColorToTex);
	OBJ_Shader.ShowLightFactor.Put(ShowLightFactor);
}
void FreeShaders()
{
	OBJ_Shader.Delete();
}



void Init()
{
	std::cout << "Init 0\n";

	InitShaders();

	Tex0.Assign(ImageDir.File("Orientation.png"));

	OBJ_BufferArray = new Wavefront::Simple3D::BufferArray * [OBJ_Count];
	for (int i = 0; i < OBJ_Count; i++)
	{
		OBJ_BufferArray[i] = new Wavefront::Simple3D::BufferArray();
		OBJ_BufferArray[i] -> Create();
		OBJ_BufferArray[i] -> Bind();

		{
			int main_count;
			Wavefront::Main::Data * main_data;
			main_data = OBJs[i] -> ToMainData(main_count, Tex0.SizeRatio);
			Container::Pointer<Wavefront::Main::Data> MainData(main_count, main_data);
			OBJ_BufferArray[i] -> Main.Change(MainData);
			delete [] main_data;
		}

		{
			Simple3D::Data inst_data []
			{
				(Simple3D::Data)Trans3D(Point3D(), Angle3D()),
			};
			Container::Pointer<Simple3D::Data> InstData(1, inst_data);
			OBJ_BufferArray[i] -> Inst.Change(InstData);
		}
	}
	std::cout << "Init 1\n";
}
void Free()
{
	std::cout << "Free 0\n";

	for (int i = 0; i < OBJ_Count; i++)
	{
		delete OBJ_BufferArray[i];
	}
	delete [] OBJ_BufferArray;

	FreeShaders();

	std::cout << "Free 1\n";
}

void Update_ColorToTex()
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_P].IsPress())
	{
		if (ColorToTex_Direction_last == false)
		{
			ColorToTex_Direction = !ColorToTex_Direction;
			ColorToTex_Direction_last = true;
		}
	} else { ColorToTex_Direction_last = false; }

	if (!ColorToTex_Direction)
	{
		if (ColorToTex.GetT1() > ColorToTex_Speed) { ColorToTex.SetT0(ColorToTex.GetT0() + ColorToTex_Speed); }
		else { ColorToTex.SetT0(1.0); }
	}
	else
	{
		if (ColorToTex.GetT0() > ColorToTex_Speed) { ColorToTex.SetT1(ColorToTex.GetT1() + ColorToTex_Speed); }
		else { ColorToTex.SetT1(1.0); }
	}
	OBJ_Shader.Bind();
	OBJ_Shader.ColorToTex.Put(ColorToTex);
}
void Update_ShowLightFactor()
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_L].IsPress())
	{
		if (ShowLightFactor_Direction_last == false)
		{
			ShowLightFactor_Direction = !ShowLightFactor_Direction;
			ShowLightFactor_Direction_last = true;
		}
	} else { ShowLightFactor_Direction_last = false; }

	if (!ShowLightFactor_Direction)
	{
		if (ShowLightFactor.GetT1() > ShowLightFactor_Speed) { ShowLightFactor.SetT0(ShowLightFactor.GetT0() + ShowLightFactor_Speed); }
		else { ShowLightFactor.SetT0(1.0); }
	}
	else
	{
		if (ShowLightFactor.GetT0() > ShowLightFactor_Speed) { ShowLightFactor.SetT1(ShowLightFactor.GetT1() + ShowLightFactor_Speed); }
		else { ShowLightFactor.SetT1(1.0); }
	}

	OBJ_Shader.Bind();
	OBJ_Shader.ShowLightFactor.Put(ShowLightFactor);
}
void Update_ObjTrans(double timeDelta)
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_O].IsPress())
	{
		Spinning = !Spinning;
	}

	for (int i = 0; i < OBJ_Count; i++)
	{
		if (Spinning)
		{
			OBJs_Trans[i].Rot.CalcMatrix();
			OBJs_Trans[i].Pos = OBJs_Trans[i].Pos + (OBJs_Trans[i].Rot.rotateBack(OBJs_Center[i]));
			OBJs_Trans[i].Rot.X += Angle::Radians(0.01f);
			OBJs_Trans[i].Rot.CalcMatrix();
			OBJs_Trans[i].Pos = OBJs_Trans[i].Pos - (OBJs_Trans[i].Rot.rotateBack(OBJs_Center[i]));
		}

		if (!window.MouseManager.CursorModeIsLocked())
		{
			OBJs_Trans[i].Pos = OBJs_Trans[i].Pos + view.Trans.Rot.rotateBack(window.MoveFromKeys() * (2.0f * timeDelta));
		}
		OBJs_Trans[i].Rot.CalcMatrix();

		{
			Trans3D trans;
			trans.Pos = Point3D(0, 0, 3);
			trans.Rot = Angle3D();
			Simple3D::Data inst_data []
			{
				(Simple3D::Data)OBJs_Trans[i],
			};
			Container::Pointer<Simple3D::Data> InstData(1, inst_data);
			OBJ_BufferArray[i] -> Inst.Change(InstData);
		}
	}
}

void Frame(double timeDelta)
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_TAB].IsPress()) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 30; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV.ToDegrees() * 0.005f;
		trans.Rot.Y *= view.FOV.ToDegrees() * 0.005f;
		trans.Rot.Z *= view.FOV.ToDegrees() * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}
	OBJ_Shader.Bind();
	OBJ_Shader.View.Put(view.Trans);

	Update_ColorToTex();
	Update_ShowLightFactor();
	Update_ObjTrans(timeDelta);

	Tex0.Bind();
	OBJ_Shader.Bind();
	for (int i = 0; i < OBJ_Count; i++)
	{
		OBJ_BufferArray[i] -> Draw();
	}
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	OBJ_Shader.Bind();
	OBJ_Shader.WindowSize.Put(WindowSize);
}

void LoadObject(FileInfo file)
{
	if (!file.Exists()) { std::cout << file.Path << ": Not found.\n"; return; }
	if (file.Mode.IsDirectory()) { std::cout << file.Path << ": Is a Directory.\n"; return; }
	if (file.Extension() != ".obj") { std::cout << file.Path << ": Does not have .obj extension.\n"; return; }

	OBJs[OBJ_Count] = Wavefront::OBJ::Load(file);
	OBJs_Center[OBJ_Count] = OBJs[OBJ_Count] -> ToAxisBox().Center();
	OBJs_Trans[OBJ_Count] = Trans3D(Point3D(OBJ_Count * 5, 0, 3) - OBJs_Center[OBJ_Count], Angle3D());
	OBJ_Count++;
}

int main(int argc, char * argv[])
{
	int ret = 0;

	window.InitCallBack.Change<MainContext>(this, &MainContext::Init);
	window.FreeCallBack.Change<MainContext>(this, &MainContext::Free);
	window.FrameCallBack.Change<MainContext>(this, &MainContext::Frame);
	window.ResizeCallBack.Change<MainContext>(this, &MainContext::Resize);
	window.DefaultColor = ColorF4(0.25f, 0.25f, 0.25f, 1.0f);

	Spinning = true;

	{
		OBJ_Limit = 0;
		if (argc != 0) { OBJ_Limit = argc - 1; }
		
		OBJs = new Wavefront::OBJ * [OBJ_Limit];
		OBJs_Center = new Point3D[OBJ_Limit];
		OBJs_Trans = new Trans3D[OBJ_Limit];

		OBJ_Count = 0;
		for (int i = 0; i < OBJ_Limit; i++)
		{
			LoadObject(FileInfo(argv[i + 1]));
		}
	}

	if (OBJ_Count != 0)
	{
		window.Create();
		Debug::Log << "<<<< Run Window" << Debug::Done;
		window.Run();
		Debug::Log << ">>>> Run Window" << Debug::Done;
		window.Delete();
	}
	else
	{
		std::cout << "No Objects loaded.\n";
		ret = -1;
	}

	{
		for (int i = 0; i < OBJ_Count; i++) { delete OBJs[i]; }
		delete [] OBJs;
		delete [] OBJs_Center;
		delete [] OBJs_Trans;
	}
	return ret;
}
};



int main(int argc, char * argv [])
{
	std::cout << "int main() ...\n";

	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }

	std::cout << "[P] Colored Triangled <-> Texture\n";
	std::cout << "[L] FullBright <-> Light\n";

	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			MainContext context;
			ret = context.main(argc, argv);
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	glfwTerminate();
	Debug::Log << "main() return; " << ret << Debug::Done;
	return ret;
}
