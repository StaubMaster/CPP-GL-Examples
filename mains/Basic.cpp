

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

YMT::PolyHedra * PH;
PolyHedra_3D_Instances * PH_Instances;
ContainerDynamic<EntryContainerDynamic<Simple3D_InstData>::Entry*> Instance_Entrys;

Shader::Base * PH_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;
Uniform::Trans3D * Uni_View;
Uniform::Depth * Uni_Depth;



void InitGraphics()
{
	PH_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		Shader::Code::FromFile(ShaderDir.File("PH_Full.frag"))
	}, 2);

	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *PH_Shader);
	Uni_View = new Uniform::Trans3D("View", *PH_Shader);
	Uni_Depth = new Uniform::Depth("Depth", *PH_Shader);
}
void FreeGraphics()
{
	delete PH_Shader;

	delete Uni_ViewPortSizeRatio;
	delete Uni_View;
	delete Uni_Depth;
}



void InitRun()
{
	InitGraphics();

	PH = YMT::PolyHedra::Cube();
	PH_Instances = new PolyHedra_3D_Instances(PH);

	Instance_Entrys.Insert(PH_Instances -> Alloc(1));
	(*Instance_Entrys[0])[0].Trans.Pos = Point3D(0, 0, 10);
}
void FreeRun()
{
	delete PH_Instances;
	delete PH;

	FreeGraphics();
}



void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();

	(*Instance_Entrys[0])[0].Trans.Rot.X += 1.0f * timeDelta;
	(*Instance_Entrys[0])[0].Trans.Rot.CalcBack();

	PH_Shader -> Use();
	Uni_View -> PutData(ViewTrans);
	PH_Instances -> Update().Draw();
}

void Resize(int w, int h)
{
	PH_Shader -> Use();
	Uni_ViewPortSizeRatio -> PutData(SizeRatio2D(w, h));
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
