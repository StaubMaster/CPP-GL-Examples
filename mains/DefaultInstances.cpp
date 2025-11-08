#include <iostream>
#include "OpenGL/openGL.h"

#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Instances.hpp"
#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Shader.hpp"

#include "Graphics/Multiform/Data/SizeRatio2D.hpp"
#include "Graphics/Multiform/Data/Trans3D.hpp"
#include "Graphics/Multiform/Data/Depth.hpp"

#include "Texture2DArray.hpp"
#include "PolyHedra.hpp"
#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"



DirectoryContext ImageDir("../media/Images");
DirectoryContext ShaderDir("../media/Shaders");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

YMT::PolyHedra * Poly0;
Texture2DArray * Tex0;

PolyHedra_3D_Instances * PH_Instances;
EntryContainerDynamic<Simple3D_InstData>::Entry ** Entrys;
PolyHedra_3D_Shader * PH_Shader;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;
Multiform::Trans3D * Multi_View;
Multiform::Depth * Multi_Depth;



void InitShaders()
{
	PH_Shader = new PolyHedra_3D_Shader(ShaderDir);

	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_View = new Multiform::Trans3D("View");
	Multi_Depth = new Multiform::Depth("Depth");

	BaseShader * shaders [] = {
		PH_Shader,
	};
	int shader_count = 1;

	Multi_ViewPortSizeRatio -> FindUniforms(shaders, shader_count);
	Multi_View -> FindUniforms(shaders, shader_count);
	Multi_Depth -> FindUniforms(shaders, shader_count);

	Multi_Depth -> ChangeData(ViewDepth);
}
void FreeShaders()
{
	delete PH_Shader;

	delete Multi_ViewPortSizeRatio;
	delete Multi_View;
	delete Multi_Depth;
}

void AddInstances()
{
	int j_len = 16;
	int i_len = 16;
	Entrys = new EntryContainerDynamic<Simple3D_InstData>::Entry*[j_len];
	for (int j = 0; j < j_len; j++)
	{
		Entrys[j] = PH_Instances -> Alloc(i_len);
		Point3D center(
			(std::rand() & 0x1F) - 0xF,
			(std::rand() & 0x1F) - 0xF,
			(std::rand() & 0x1F) - 0xF
		);
		Angle3D rot(
			(std::rand() & 0x1F) - 0xF,
			(std::rand() & 0x1F) - 0xF,
			(std::rand() & 0x1F) - 0xF
		);
		for (int i = 0; i < i_len; i++)
		{
			(*Entrys[j])[i].Trans.Pos = center + Point3D(
				(std::rand() & 0x1F) - 0xF,
				(std::rand() & 0x1F) - 0xF,
				(std::rand() & 0x1F) - 0xF
			);
			(*Entrys[j])[i].Trans.Rot = rot;
		}
	}

	{
		int MemSize = (PH_Instances -> Instances.Length) * sizeof(Simple3D_InstData);
		std::cout << "Count: " << (PH_Instances -> Instances.Length) << "\n";
		std::cout << (MemSize / (1)) << " Bytes\n";
		std::cout << (MemSize / (1 * 1000)) << "k Bytes\n";
		std::cout << (MemSize / (1 * 1000 * 1000)) << "M Bytes\n";
	}
}



void Init()
{
	std::cout << "Init 0\n";

	InitShaders();

	//Poly0 = YMT::PolyHedra::FullTexture();
	Poly0 = YMT::PolyHedra::Cube();
	//Poly0 = YMT::PolyHedra::ConeC(12, 0.5f);
	
	Poly0 -> UseCornerNormals = false;
	Tex0 = new Texture2DArray(128, 128, 1, (FileContext[])
	{
		ImageDir.File("Orientation.png"),
		//ImageDir.File("GrayDeant.png"),
	});
	PH_Instances = new PolyHedra_3D_Instances(Poly0);
	AddInstances();

	std::cout << "Init 1\n";
}
void Free()
{
	std::cout << "Free 0\n";

	delete PH_Instances;
	delete [] Entrys;
	delete Tex0;
	delete Poly0;

	FreeShaders();

	std::cout << "Free 1\n";
}

void Frame(double timeDelta)
{
	if (win -> IsMouseLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(2.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();
	Multi_View -> ChangeData(ViewTrans);

	PH_Shader -> Use();
	Tex0 -> Bind();
	PH_Instances -> Update();
	PH_Instances -> Draw();
}

void Resize(int w, int h)
{
	Multi_ViewPortSizeRatio -> ChangeData(SizeRatio2D(w, h));
}



int main()
{
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

	win -> DefaultColor = Color(0.25f, 0.0f, 0.0f);

	ViewTrans = Trans3D(Point3D(0, 0, 0), Angle3D(0, 0, 0));

	ViewDepth.Factors = DepthFactors(0.1f, 100.0f);
	ViewDepth.Range = Range(0.8f, 1.0f);
	ViewDepth.Color = win -> DefaultColor;


	std::cout << "++++ Run\n";
	win -> Run();
	std::cout << "---- Run\n";



	delete win;



	glfwTerminate();
	std::cout << "main() return";
	return 0;
}
