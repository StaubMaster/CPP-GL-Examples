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



Wavefront::Simple3D::Shader	OBJ_Shader;
Texture::Array2D Tex0;
bool	Spinning;

int OBJ_Limit;
int OBJ_Count;

struct DisplayObject3D
{
	Wavefront::OBJ *	OBJ;
	Point3D				Center;
	Trans3D				Trans;
	Wavefront::Simple3D::BufferArray * BufferArray;
};
DisplayObject3D * Obj3Ds;



struct DynamicLinearInterpolator
{
	::LInter LInter;
	bool Direction;
	float Speed;

	DynamicLinearInterpolator() :
		LInter(),
		Direction(false),
		Speed(0.01f)
	{ }

	void Toggle()
	{
		Direction = !Direction;
	}
	void Update()
	{
		if (!Direction)
		{
			if (LInter.GetT1() > Speed) 
			{
				LInter.SetT0(LInter.GetT0() + Speed);
			}
			else { LInter.SetT0(1.0); }
		}
		else
		{
			if (LInter.GetT0() > Speed)
			{
				LInter.SetT1(LInter.GetT1() + Speed);
			}
			else { LInter.SetT1(1.0); }
		}
	}
};
DynamicLinearInterpolator ColorToTex;
DynamicLinearInterpolator ShowLightFactor;



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

	ColorToTex.LInter = LInter::T0();
	ColorToTex.Direction = false;

	ShowLightFactor.LInter = LInter::T1();
	ShowLightFactor.Direction = true;

	OBJ_Shader.Bind();
	OBJ_Shader.Depth.Put(view.Depth);
	OBJ_Shader.ColorToTex.Put(ColorToTex.LInter);
	OBJ_Shader.ShowLightFactor.Put(ShowLightFactor.LInter);
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

	for (int i = 0; i < OBJ_Count; i++)
	{
		Obj3Ds[i].BufferArray = new Wavefront::Simple3D::BufferArray();
		Obj3Ds[i].BufferArray -> Create();
		Obj3Ds[i].BufferArray -> Bind();

		{
			int main_count;
			Wavefront::Main::Data * main_data;
			main_data = Obj3Ds[i].OBJ -> ToMainData(main_count, Tex0.SizeRatio);
			Container::Pointer<Wavefront::Main::Data> MainData(main_count, main_data);
			Obj3Ds[i].BufferArray -> Main.Change(MainData);
			delete [] main_data;
		}

		{
			Simple3D::Data inst_data []
			{
				(Simple3D::Data)Trans3D(Point3D(), Angle3D()),
			};
			Container::Pointer<Simple3D::Data> InstData(1, inst_data);
			Obj3Ds[i].BufferArray -> Inst.Change(InstData);
		}
	}
	std::cout << "Init 1\n";
}
void Free()
{
	std::cout << "Free 0\n";

	FreeShaders();

	std::cout << "Free 1\n";
}

void Update_ColorToTex()
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_P].IsPress())
	{
		ColorToTex.Toggle();
	}
	ColorToTex.Update();

	OBJ_Shader.Bind();
	OBJ_Shader.ColorToTex.Put(ColorToTex.LInter);
}
void Update_ShowLightFactor()
{
	if (window.KeyBoardManager.Keys[GLFW_KEY_L].IsPress())
	{
		ShowLightFactor.Toggle();
	}
	ShowLightFactor.Update();

	OBJ_Shader.Bind();
	OBJ_Shader.ShowLightFactor.Put(ShowLightFactor.LInter);
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
			Obj3Ds[i].Trans.Rot.CalcMatrix();
			Obj3Ds[i].Trans.Pos = Obj3Ds[i].Trans.Pos + (Obj3Ds[i].Trans.Rot.rotateBack(Obj3Ds[i].Center));
			Obj3Ds[i].Trans.Rot.X += Angle::Radians(0.01f);
			Obj3Ds[i].Trans.Rot.CalcMatrix();
			Obj3Ds[i].Trans.Pos = Obj3Ds[i].Trans.Pos - (Obj3Ds[i].Trans.Rot.rotateBack(Obj3Ds[i].Center));
		}

		if (!window.MouseManager.CursorModeIsLocked())
		{
			Obj3Ds[i].Trans.Pos = Obj3Ds[i].Trans.Pos + view.Trans.Rot.rotateBack(window.MoveFromKeys() * (2.0f * timeDelta));
		}
		Obj3Ds[i].Trans.Rot.CalcMatrix();

		{
			Trans3D trans;
			trans.Pos = Point3D(0, 0, 3);
			trans.Rot = Angle3D();
			Simple3D::Data inst_data []
			{
				(Simple3D::Data)Obj3Ds[i].Trans,
			};
			Container::Pointer<Simple3D::Data> InstData(1, inst_data);
			Obj3Ds[i].BufferArray -> Inst.Change(InstData);
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
		Obj3Ds[i].BufferArray -> Draw();
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

	Obj3Ds[OBJ_Count].OBJ = Wavefront::OBJ::Load(file);
	Obj3Ds[OBJ_Count].Center = Obj3Ds[OBJ_Count].OBJ -> ToAxisBox().Center();
	Obj3Ds[OBJ_Count].Trans = Trans3D(Point3D(OBJ_Count * 5, 0, 3) - Obj3Ds[OBJ_Count].Center, Angle3D());
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
		Obj3Ds = new DisplayObject3D[OBJ_Limit];
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
		for (int i = 0; i < OBJ_Count; i++)
		{
			delete Obj3Ds[i].OBJ;
			delete Obj3Ds[i].BufferArray;
		}
		delete [] Obj3Ds;
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
