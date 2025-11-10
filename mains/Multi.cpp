

#include <iostream>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "DataO.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Instances.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Skin/SkinBase.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Graphics/Texture/Base.hpp"
#include "Graphics/Texture/2DArray.hpp"
#include "Graphics/Texture/Generate.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"



DirectoryContext ImageDir("./media/Images");
DirectoryContext ShaderDir("./media/Shaders");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

ContainerDynamic<YMT::PolyHedra *> PHs;
ContainerDynamic<PolyHedra_3D_Instances *> PH_Instances;
ContainerDynamic<EntryContainerDynamic<Simple3D_InstData>::Entry*> Instance_Entrys;

ContainerDynamic<Shader::Base *> PH_Shaders;
ContainerDynamic<Uniform::SizeRatio2D *> Uni_ViewPortSizeRatio;
ContainerDynamic<Uniform::Trans3D *> Uni_View;
ContainerDynamic<Uniform::Depth *> Uni_Depth;

Multiform::SizeRatio2D * Multi_ViewPortSizeRatio;
Multiform::Trans3D * Multi_View;
Multiform::Depth * Multi_Depth;



void InitRun()
{
	PH_Shaders.Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_Full.frag"))
	}, 2));

	PH_Shaders.Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_R.frag"))
	}, 2));

	PH_Shaders.Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_G.frag"))
	}, 2));

	PH_Shaders.Insert(new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_B.frag"))
	}, 2));

	for (unsigned int i = 0; i < PH_Shaders.Count(); i++)
	{
		Uni_ViewPortSizeRatio.Insert(new Uniform::SizeRatio2D("ViewPortSizeRatio", *PH_Shaders[i]));
		Uni_View.Insert(new Uniform::Trans3D("View", *PH_Shaders[i]));
		Uni_Depth.Insert(new Uniform::Depth("Depth", *PH_Shaders[i]));
	}

	Multi_ViewPortSizeRatio = new Multiform::SizeRatio2D("ViewPortSizeRatio");
	Multi_View = new Multiform::Trans3D("View");
	Multi_Depth = new Multiform::Depth("Depth");

	Multi_ViewPortSizeRatio -> FindUniforms(PH_Shaders.ToPointer(), PH_Shaders.Count());
	Multi_View -> FindUniforms(PH_Shaders.ToPointer(), PH_Shaders.Count());
	Multi_Depth -> FindUniforms(PH_Shaders.ToPointer(), PH_Shaders.Count());

	Multi_Depth -> ChangeData(ViewDepth);

	PHs.Insert(YMT::PolyHedra::Cube(2.0f));
	PHs.Insert(YMT::PolyHedra::Cube(0.5f));
	PHs.Insert(YMT::PolyHedra::Cube(1.0f));
	PHs.Insert(YMT::PolyHedra::Cube(1.5f));

	for (unsigned int i = 0; i < PHs.Count(); i++)
	{
		PH_Instances.Insert(new PolyHedra_3D_Instances(PHs[i]));
	}

	{
		unsigned int idx = Instance_Entrys.Insert(PH_Instances[0] -> Alloc(8));
		for (int i = 0; i < (*Instance_Entrys[idx]).Length; i++)
		{
			(*Instance_Entrys[idx])[i].Trans.Rot = Angle3D();
			(*Instance_Entrys[idx])[i].Trans.Rot.CalcBack();
		}
		(*Instance_Entrys[idx])[0].Trans.Pos = Point3D(-10, -10, -10);
		(*Instance_Entrys[idx])[1].Trans.Pos = Point3D(+10, -10, -10);
		(*Instance_Entrys[idx])[2].Trans.Pos = Point3D(-10, +10, -10);
		(*Instance_Entrys[idx])[3].Trans.Pos = Point3D(+10, +10, -10);
		(*Instance_Entrys[idx])[4].Trans.Pos = Point3D(-10, -10, +10);
		(*Instance_Entrys[idx])[5].Trans.Pos = Point3D(+10, -10, +10);
		(*Instance_Entrys[idx])[6].Trans.Pos = Point3D(-10, +10, +10);
		(*Instance_Entrys[idx])[7].Trans.Pos = Point3D(+10, +10, +10);
	}

	{
		unsigned int idx = Instance_Entrys.Insert(PH_Instances[1] -> Alloc(16));
		for (int i = 0; i < (*Instance_Entrys[idx]).Length; i++)
		{
			Angle3D a((TAU * i) / (*Instance_Entrys[idx]).Length, 0, 0);
			a.CalcBack();
			(*Instance_Entrys[idx])[i].Trans.Pos = a.rotate(Point3D(0, 0, 10));
			(*Instance_Entrys[idx])[i].Trans.Rot = a;
		}
	}

	{
		unsigned int idx = Instance_Entrys.Insert(PH_Instances[2] -> Alloc(16));
		for (int i = 0; i < (*Instance_Entrys[idx]).Length; i++)
		{
			Angle3D a(0, (TAU * i) / (*Instance_Entrys[idx]).Length, 0);
			a.CalcBack();
			(*Instance_Entrys[idx])[i].Trans.Pos = a.rotate(Point3D(0, 15, 0));
			(*Instance_Entrys[idx])[i].Trans.Rot = a;
		}
	}

	{
		unsigned int idx = Instance_Entrys.Insert(PH_Instances[3] -> Alloc(16));
		for (int i = 0; i < (*Instance_Entrys[idx]).Length; i++)
		{
			Angle3D a(0, 0, (TAU * i) / (*Instance_Entrys[idx]).Length);
			a.CalcBack();
			(*Instance_Entrys[idx])[i].Trans.Pos = a.rotate(Point3D(20, 0, 0));
			(*Instance_Entrys[idx])[i].Trans.Rot = a;
		}
	}
}
void FreeRun()
{
	for (unsigned int i = 0; i < PH_Instances.Count(); i++)
	{
		delete PH_Instances[i];
	}
	for (unsigned int i = 0; i < PHs.Count(); i++)
	{
		delete PHs[i];
	}

	for (unsigned int i = 0; i < PH_Shaders.Count(); i++)
	{
		delete PH_Shaders[i];
	}

	for (unsigned int i = 0; i < Uni_ViewPortSizeRatio.Count(); i++)
	{
		delete Uni_ViewPortSizeRatio[i];
	}
	for (unsigned int i = 0; i < Uni_View.Count(); i++)
	{
		delete Uni_View[i];
	}
	for (unsigned int i = 0; i < Uni_Depth.Count(); i++)
	{
		delete Uni_Depth[i];
	}
}



void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();
	Multi_View -> ChangeData(ViewTrans);
	for (unsigned int i = 0; i < PH_Shaders.Count(); i++)
	{
		PH_Shaders[i] -> Use();
		if (i < PH_Instances.Count())
		{
			PH_Instances[i] -> Update().Draw();
		}
	}
}

void Resize(int w, int h)
{
	Multi_ViewPortSizeRatio -> ChangeData(SizeRatio2D(w, h));
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
