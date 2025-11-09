#include <iostream>
#include "OpenGL/openGL.h"
#include "OpenGL/openGL.hpp"

#include "Debug.hpp"

#include "DataStruct/Main/Waveform/OBJ.hpp"
#include "DataStruct/Main/Waveform/OBJ_Main.hpp"
#include "DataStruct/Main/Waveform/OBJ_3D_BufferArray.hpp"
#include "DataStruct/Main/Waveform/OBJ_3D_Shader.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "DataStruct/LInter.hpp"
#include "DataStruct/AxisBox3D.hpp"
#include "DataO.hpp"

#include "Graphics/Texture/2DArray.hpp"
#include "PolyHedra/PolyHedra.hpp"
#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"



DirectoryContext ImageDir("./media/Images");
DirectoryContext ShaderDir("./media/Shaders");



Window * win;

Trans3D ViewTrans;
Depth	ViewDepth;

Texture::T2DArray * Tex0;
int OBJ_Count;
OBJ ** OBJs;
Point3D * OBJs_Center;
Trans3D * OBJs_Trans;

OBJ_3D_BufferArray ** OBJ_BufferArray;
OBJ_3D_Shader * OBJ_Shader;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;
Multiform::Trans3D * Multi_View;
Multiform::Depth * Multi_Depth;
Multiform::LInter * Multi_ColorToTex;

LInter ColorToTex;
float ColorToTex_Speed = 0.01f;
bool ColorToTex_Direction = false;
bool ColorToTex_Direction_last = false;

/*
	Uniform to turn off Lights
	would be easier to have Uniform Value Bases
*/

void InitShaders()
{
	OBJ_Shader = new OBJ_3D_Shader(ShaderDir);

	ColorToTex = LInter::T0();
	ColorToTex_Direction = false;

	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_View = new Multiform::Trans3D("View");
	Multi_Depth = new Multiform::Depth("Depth");
	Multi_ColorToTex = new Multiform::LInter("ColorToTex");

	Shader::Base * shaders [] = {
		OBJ_Shader,
	};
	int shader_count = 1;

	Multi_ViewPortSizeRatio -> FindUniforms(shaders, shader_count);
	Multi_View -> FindUniforms(shaders, shader_count);
	Multi_Depth -> FindUniforms(shaders, shader_count);
	Multi_ColorToTex -> FindUniforms(shaders, shader_count);

	Multi_Depth -> ChangeData(ViewDepth);
	Multi_ColorToTex -> ChangeData(ColorToTex);
}
void FreeShaders()
{
	delete OBJ_Shader;

	delete Multi_ViewPortSizeRatio;
	delete Multi_View;
	delete Multi_Depth;
	delete Multi_ColorToTex;
}



void Init()
{
	std::cout << "Init 0\n";

	InitShaders();

	Tex0 = new Texture::T2DArray(ImageDir.File("Orientation.png"));

	OBJ_BufferArray = new OBJ_3D_BufferArray * [OBJ_Count];
	for (int i = 0; i < OBJ_Count; i++)
	{
		OBJ_BufferArray[i] = new OBJ_3D_BufferArray();

		int main_count;
		OBJ_MainData * main_data;
		main_data = OBJs[i] -> ToMainData(main_count, Tex0 -> SizeRatio);
		OBJ_BufferArray[i] -> BindMain(main_data, main_count);
		delete [] main_data;

		Simple3D_InstData inst_data []
		{
			(Simple3D_InstData)Trans3D(Point3D(), Angle3D()),
		};
		int inst_count = 1;
		OBJ_BufferArray[i] -> BindInst(inst_data, inst_count);
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
	delete Tex0;

	FreeShaders();

	std::cout << "Free 1\n";
}

void Update_ColorToTex()
{
	if (glfwGetKey(win -> win, GLFW_KEY_P))
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
	Multi_ColorToTex -> ChangeData(ColorToTex);
}
void Update_ObjTrans(double timeDelta)
{
	ViewTrans.Rot.CalcBack();
	for (int i = 0; i < OBJ_Count; i++)
	{
		OBJs_Trans[i].Rot.CalcBack();
		OBJs_Trans[i].Pos = OBJs_Trans[i].Pos + (OBJs_Trans[i].Rot.rotate(OBJs_Center[i]));
		OBJs_Trans[i].Rot.X += 0.01f;

		OBJs_Trans[i].Rot.CalcBack();
		OBJs_Trans[i].Pos = OBJs_Trans[i].Pos - (OBJs_Trans[i].Rot.rotate(OBJs_Center[i]));

		if (!win -> IsCursorLocked())
		{
			OBJs_Trans[i].Pos = OBJs_Trans[i].Pos + ViewTrans.Rot.rotate(win -> MoveFromKeys(2.0f * timeDelta));
		}

		{
			Trans3D trans;
			trans.Pos = Point3D(0, 0, 3);
			trans.Rot = Angle3D(0, 0, 0);
			trans.Rot.CalcBack();
			Simple3D_InstData inst_data []
			{
				//(Simple3D_InstData)OBJs_Trans[i],
				(Simple3D_InstData)trans,
			};
			/*const float * ptr = (const float *)inst_data;
			std::cout << "#\n";
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					std::cout << "|" << ptr[i * 3 + j];
				}
				std::cout << "|\n";
			}*/
			int inst_count = 1;
			OBJ_BufferArray[i] -> BindInst(inst_data, inst_count);
		}
	}
}

void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(2.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	Multi_View -> ChangeData(ViewTrans);

	Update_ColorToTex();
	Update_ObjTrans(timeDelta);

	OBJ_Shader -> Use();
	Tex0 -> Bind();
	for (int i = 0; i < OBJ_Count; i++)
	{
		OBJ_BufferArray[i] -> Draw();
	}
}

void Resize(int w, int h)
{
	Multi_ViewPortSizeRatio -> ChangeData(SizeRatio2D(w, h));
}



int main(int argc, char * argv [])
{
	Debug::NewFileInDir(DirectoryContext("logs/"));

	if (argc <= 0)
	{
		std::cout << "Argc: " << argc << " <= 0\n";
		return 1;
	}

	if (glfwInit() == 0)
	{
		std::cout << "GLFW Init Failed\n";
		return -1;
	}

	try
	{
		win = new Window(640, 480);
		win -> InitFunc = Init;
		win -> FrameFunc = Frame;
		win -> FreeFunc = Free;
		win -> ResizeFunc = Resize;
	}
	catch (std::exception & ex)
	{
		std::cout << "exception: " << ex.what() << "\n";
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
	//win -> DefaultColor = Color(0.25f, 0.0f, 0.0f);
	//win -> DefaultColor = Color(0.0f, 0.0f, 0.0f);
	win -> DefaultColor = Color(0.5f, 0.5f, 0.5f);



	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));
	ViewDepth.Factors = DepthFactors(0.1f, 100.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;



	OBJ_Count = argc - 1;
	OBJs = new OBJ * [OBJ_Count];
	OBJs_Center = new Point3D[OBJ_Count];
	OBJs_Trans = new Trans3D[OBJ_Count];
	for (int i = 0; i < OBJ_Count; i++)
	{
		OBJs[i] = OBJ::Load(FileContext(std::string(argv[i + 1])));
		OBJs_Center[i] = OBJs[i] -> ToAxisBox().Center();
		OBJs_Trans[i] = Trans3D(Point3D(i * 5, 0, 3) - OBJs_Center[i], Angle3D(0, 0, 0));
	}



	Debug::Log << "++++ Run" << Debug::Done;
	win -> Run();
	Debug::Log << "---- Run" << Debug::Done;



	for (int i = 0; i < OBJ_Count; i++) { delete OBJs[i]; }
	delete [] OBJs;
	delete [] OBJs_Center;
	delete [] OBJs_Trans;
	delete win;



	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
