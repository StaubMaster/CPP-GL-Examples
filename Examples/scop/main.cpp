#include "OpenGL.hpp"

#include "Waveform/OBJ.hpp"
#include "Waveform/OBJ_Main.hpp"
#include "Waveform/OBJ_3D_BufferArray.hpp"
#include "Waveform/OBJ_3D_Shader.hpp"

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



DirectoryInfo ImageDir("./media/Images");
DirectoryInfo ShaderDir("./media/Shaders");



Window *	win;
View		view;

Texture::Array2D * Tex0;
int OBJ_Limit;
int OBJ_Count;
OBJ ** OBJs;
Point3D * OBJs_Center;
Trans3D * OBJs_Trans;

OBJ_3D_BufferArray ** OBJ_BufferArray;
OBJ_3D_Shader * OBJ_Shader;

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
	OBJ_Shader = new OBJ_3D_Shader();
	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("OBJ.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("OBJ.frag")));
		OBJ_Shader -> Change(code);
	}
	OBJ_Shader -> Create();
	OBJ_Shader -> Depth.Put(view.Depth);

	ColorToTex = LInter::T0();
	ColorToTex_Direction = false;

	ShowLightFactor = LInter::T1();
	ShowLightFactor_Direction = true;
	ShowLightFactor_Direction_last = true;

	OBJ_Shader -> Bind();
	OBJ_Shader -> Depth.Put(view.Depth);
	OBJ_Shader -> ColorToTex.Put(ColorToTex);
	OBJ_Shader -> ShowLightFactor.Put(ShowLightFactor);
}
void FreeShaders()
{
	OBJ_Shader -> Delete();
	delete OBJ_Shader;
}



void Init()
{
	std::cout << "Init 0\n";

	InitShaders();

	//Tex0 = new Texture::Array2D(ImageDir.File("Orientation.png"));
	Tex0 = new Texture::Array2D();
	Tex0 -> Assign(ImageDir.File("Orientation.png"));

std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
	OBJ_BufferArray = new OBJ_3D_BufferArray * [OBJ_Count];
	for (int i = 0; i < OBJ_Count; i++)
	{
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
		OBJ_BufferArray[i] = new OBJ_3D_BufferArray();
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
		OBJ_BufferArray[i] -> Create();
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';

		int main_count;
		OBJ_MainData * main_data;
		main_data = OBJs[i] -> ToMainData(main_count, Tex0 -> SizeRatio);
		Container::Pointer<OBJ_MainData> MainData(main_count, main_data);
		/*{
			std::cout << "Main: " << MainData.Count() << "\n";
			for (unsigned int i = 0; i < MainData.Count(); i++)
			{
				std::cout << MainData[i].Position << "\n";
			}
		}*/
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
		OBJ_BufferArray[i] -> Main.Change(MainData);
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
		delete [] main_data;

		Simple3D::Data inst_data []
		{
			(Simple3D::Data)Trans3D(Point3D(), Angle3D()),
		};
		Container::Pointer<Simple3D::Data> InstData(1, inst_data);
		/*{
			std::cout << "Inst: " << InstData.Count() << "\n";
			for (unsigned int i = 0; i < InstData.Count(); i++)
			{
				std::cout << InstData[i].Trans << "\n";
			}
		}*/
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
		OBJ_BufferArray[i] -> Inst.Change(InstData);
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
	}
std::cerr << __FILE__ << ' ' << __LINE__ << ' ' << GL::GetError() << '\n';
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
	delete Tex0;

	FreeShaders();

	std::cout << "Free 1\n";
}

void Update_ColorToTex()
{
	if (win -> KeyBoardManager.Keys[GLFW_KEY_P].IsPress())
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
	OBJ_Shader -> Bind();
	OBJ_Shader -> ColorToTex.Put(ColorToTex);
}
void Update_ShowLightFactor()
{
	if (win -> KeyBoardManager.Keys[GLFW_KEY_L].IsPress())
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

	OBJ_Shader -> Bind();
	OBJ_Shader -> ShowLightFactor.Put(ShowLightFactor);
}
void Update_ObjTrans(double timeDelta)
{
	view.Trans.Rot.CalcMatrix();
	for (int i = 0; i < OBJ_Count; i++)
	{
		//OBJs_Trans[i].Rot.CalcBack();
		OBJs_Trans[i].Rot.CalcMatrix();
		OBJs_Trans[i].Pos = OBJs_Trans[i].Pos + (OBJs_Trans[i].Rot.rotateBack(OBJs_Center[i]));
		OBJs_Trans[i].Rot.X += Angle::Radians(0.01f);
		OBJs_Trans[i].Rot.CalcMatrix();
		//OBJs_Trans[i].Rot.CalcBack();
		OBJs_Trans[i].Pos = OBJs_Trans[i].Pos - (OBJs_Trans[i].Rot.rotateBack(OBJs_Center[i]));

		if (!win -> MouseManager.CursorModeIsLocked())
		{
			OBJs_Trans[i].Pos = OBJs_Trans[i].Pos + view.Trans.Rot.rotateBack(win -> MoveFromKeys() * (2.0f * timeDelta));
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
	OBJ_Shader -> Bind();
	if (win -> KeyBoardManager.Keys[GLFW_KEY_TAB].IsPress()) { win -> MouseManager.CursorModeToggle(); }
	if (win -> MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = win -> MoveSpinFromKeysCursor();
		if (win -> KeyBoardManager.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 30; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV.ToDegrees() * 0.005f;
		trans.Rot.Y *= view.FOV.ToDegrees() * 0.005f;
		trans.Rot.Z *= view.FOV.ToDegrees() * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}
	OBJ_Shader -> View.Put(view.Trans);

	//Update_ColorToTex();
	//Update_ShowLightFactor();
	//Update_ObjTrans(timeDelta);

	GL::Disable(GL::Capability::CullFace);
	GL::Disable(GL::Capability::DepthTest);
	//Tex0 -> Bind();
	OBJ_Shader -> Bind();
	OBJ_BufferArray[0] -> Draw();
	/*for (int i = 0; i < OBJ_Count; i++)
	{
		OBJ_BufferArray[i] -> Draw();
	}*/
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	std::cout << "Resize: " << WindowSize.Ratio << "\n";
	OBJ_Shader -> Bind();
	OBJ_Shader -> WindowSize.Put(WindowSize);
}



int main(int argc, char * argv [])
{
	Debug::NewFileInDir(DirectoryInfo("logs/"));

	if (argc <= 1)
	{
		std::cout << "Argc: " << argc << " <= 1\n";
		return 1;
	}

	if (!glfwInit())
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	StaticFunction<void> init_func(&Init);
	StaticFunction<void> free_func(&Free);
	StaticFunction<void, double> frame_func(&Frame);
	StaticFunction<void, const WindowBufferSize2D &> resize_func(&Resize);

	try
	{
		win = new Window();
		win -> InitCallBack.Change(&init_func);
		win -> FreeCallBack.Change(&free_func);
		win -> FrameCallBack.Change(&frame_func);
		win -> ResizeCallBack.Change(&resize_func);
	}
	catch (std::exception & ex)
	{
		std::cout << "exception: " << ex.what() << "\n";
		return -1;
	}
	catch (const char * err)
	{
		std::cerr << "String Error: "<< err << "\n";
		glfwTerminate();
		return -1;
	}
	catch (...)
	{
		std::cerr << "Unknown Error" << "\n";
		glfwTerminate();
		return -1;
	}
	//win -> DefaultColor = ColorF4(0.25f, 0.0f, 0.0f);
	//win -> DefaultColor = ColorF4(0.0f, 0.0f, 0.0f);
	win -> DefaultColor = ColorF4(0.5f, 0.5f, 0.5f);



	OBJ_Limit = argc - 1;
	OBJs = new OBJ * [OBJ_Limit];
	OBJs_Center = new Point3D[OBJ_Limit];
	OBJs_Trans = new Trans3D[OBJ_Limit];
	OBJ_Count = 0;
	for (int i = 0; i < OBJ_Limit; i++)
	{
		std::string path(argv[i + 1]);
		FileInfo file(path);
		if (file.Exists())
		{
			OBJs[OBJ_Count] = OBJ::Load(file);
			OBJs_Center[OBJ_Count] = OBJs[OBJ_Count] -> ToAxisBox().Center();
			OBJs_Trans[OBJ_Count] = Trans3D(Point3D(OBJ_Count * 5, 0, 3) - OBJs_Center[OBJ_Count], Angle3D());
			OBJ_Count++;
		}
		else
		{
			std::cout << "File: '" << path << "' not found.";
		}
	}

	std::cout << "[P] Colored Triangled <-> Texture\n";
	std::cout << "[L] FullBright <-> Light\n";



	win -> Create();
	Debug::Log << "++++ Run" << Debug::Done;
	win -> Run();
	Debug::Log << "---- Run" << Debug::Done;
	win -> Delete();


	for (int i = 0; i < OBJ_Count; i++) { delete OBJs[i]; }
	delete [] OBJs;
	delete [] OBJs_Center;
	delete [] OBJs_Trans;
	delete win;



	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
