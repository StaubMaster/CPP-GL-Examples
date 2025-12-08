
#include <iostream>
#include <exception>
#include "OpenGL/openGL.h"

#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "DataStruct/Full/PolyHedra_3D/PolyHedra_3D_Instances.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"

#include "PolyHedra/Skin/SkinBase.hpp"
#include "PolyHedra/Skin/Skin2DA.hpp"

#include "Graphics/Texture/Base.hpp"
#include "Graphics/Texture/2DArray.hpp"
#include "Graphics/Texture/Generate.hpp"

#include "Window.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"



/*	ToDo
Calculate Spline Length for SplineSegment and SplineCurve

add Skins so they are better visible
maybe just do Solar Light for now

make Wheels Spin based on Wheel Radius ?
assamble other things correctly
*/
#include "Spline/Factors.hpp"
#include "Spline/SplineNode3D.hpp"
#include "Spline/SplineSegment3D.hpp"
#include "Spline/SplineCurve3D.hpp"
#include "Spline/SplineObject.hpp"



DirectoryContext ImageDir("../../media/Images");
DirectoryContext ShaderDir("../../media/Shaders");
DirectoryContext MediaDir("../../media/YMT/Spline");



Window * win;

Trans3D	ViewTrans;
Depth	ViewDepth;

Shader::Base * PH_Shader;

Uniform::SizeRatio2D * Uni_ViewPortSizeRatio;
Uniform::Trans3D * Uni_View;
Uniform::Depth * Uni_Depth;

void InitGraphics()
{
	PH_Shader = new Shader::Base((const Shader::Code []) {
		Shader::Code::FromFile(ShaderDir.File("PH_S3D.vert")),
		//Shader::Code::FromFile(ShaderDir.File("PH_LightFixed.frag"))
		Shader::Code::FromFile(ShaderDir.File("PH_Full.frag"))
	}, 2);

	Uni_ViewPortSizeRatio = new Uniform::SizeRatio2D("ViewPortSizeRatio", *PH_Shader);
	Uni_View = new Uniform::Trans3D("View", *PH_Shader);
	Uni_Depth = new Uniform::Depth("Depth", *PH_Shader);

	PH_Shader -> Use();
	Uni_Depth -> PutData(ViewDepth);
}
void FreeGraphics()
{
	delete PH_Shader;

	delete Uni_ViewPortSizeRatio;
	delete Uni_View;
	delete Uni_Depth;
}





YMT::PolyHedra * Test_Path_PH;
YMT::PolyHedra * Test_Node_PH;
PolyHedra_3D_Instances * Test_Path_Instances;
PolyHedra_3D_Instances * Test_Node_Instances;
EntryContainer::Entry<Simple3D_InstData> Test_Path_Instance_Entrys;
EntryContainer::Entry<Simple3D_InstData> Test_Node_Instance_Entrys;

SplineCurve3D * Test_Spline;
Container::Dynamic<SplineObject> Test_Spline_Entrys;

void TestSpline_Init()
{
	/*Test_Spline = new SplineCurve3D((SplineNode3D []) {
		SplineNode3D(Point3D(+40, +10, -20), Point3D(+1, 0, +1)),
		SplineNode3D(Point3D(+40, -10, +20), Point3D(-1, 0, +1)),
		SplineNode3D(Point3D(  0,   0, +40), Point3D(-1, 0,  0)),
		SplineNode3D(Point3D(-40,   0, +20), Point3D(-1, 0, -1)),
		SplineNode3D(Point3D(-40,   0, -20), Point3D(+1, 0, -1)),
		SplineNode3D(Point3D(  0,   0, -40), Point3D(+1, 0,  0)),
	}, 6, true, 0, 0, 0);*/
	Test_Spline = new SplineCurve3D((SplineNode3D []) {
		SplineNode3D(Point3D(+40, +10, -20), Point3D(+1, 0, +1)),
		SplineNode3D(Point3D(+40, -10, +20), Point3D(-1, 0, +1)),
		SplineNode3D(Point3D(  0,   0, +40), Point3D(-1, 0,  0)),
		SplineNode3D(Point3D(-40,   0, +20), Point3D(-1, 0, -1)),
		SplineNode3D(Point3D(-40,   0, -20), Point3D(+1, 0, -1)),
		SplineNode3D(Point3D(  0,   0, -40), Point3D(+1, 0,  0)),
	}, 6, true, 0, 0, 0);

	Test_Node_PH = YMT::PolyHedra::Generate::Cube(1.0f);
	Test_Node_Instances = new PolyHedra_3D_Instances(Test_Node_PH);
	Test_Node_Instance_Entrys.Allocate(Test_Node_Instances -> Instances, (Test_Spline -> SegmentCount) * 2);
	for (unsigned int i = 0; i < Test_Spline -> SegmentCount; i++)
	{
		Test_Node_Instance_Entrys[i * 2 + 0].Trans.Pos = Test_Spline -> Segments[i].Node0.Pos;
		Test_Node_Instance_Entrys[i * 2 + 1].Trans.Pos = Test_Spline -> Segments[i].Node1.Pos;
	}

	Test_Path_PH = YMT::PolyHedra::Generate::ConeC(8, 0.5f, 2.0f);
	//Test_Path_PH = YMT::PolyHedra::Generate::Cube(0.5f);
	Test_Path_Instances = new PolyHedra_3D_Instances(Test_Path_PH);
	Test_Path_Instance_Entrys.Allocate(Test_Path_Instances -> Instances, 96);
	for (unsigned int i = 0; i < Test_Path_Instance_Entrys.Length(); i++)
	{
		Test_Spline_Entrys.Insert(SplineObject(i, (((float)i) / Test_Path_Instance_Entrys.Length()) * Test_Spline -> SegmentCount));
	}
}
void TestSpline_Free()
{
	Test_Path_Instance_Entrys.Dispose();
	Test_Node_Instance_Entrys.Dispose();
	delete Test_Node_Instances;
	delete Test_Node_PH;
	delete Test_Path_Instances;
	delete Test_Path_PH;
}
void TestSpline_Update(float timeDelta)
{
	for (unsigned int i = 0; i < Test_Path_Instance_Entrys.Length(); i++)
	{
		SplineNode3D node = Test_Spline -> Calculate(Test_Spline_Entrys[i].SplineValue);

		Test_Path_Instance_Entrys[i].Trans.Pos = node.Pos;
		Test_Path_Instance_Entrys[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		Test_Path_Instance_Entrys[i].Trans.Rot.CalcBack();

		Test_Spline_Entrys[i].SplineValue += 0.1f * timeDelta;
	}
}



SplineCurve3D * Train_Spline;
Container::Dynamic<SplineObject> Train_Rail_Spline_Entrys;
float Train_Spline_Value;
float Train_WheelSpin;

Container::Dynamic<YMT::PolyHedra *> Train_PHs;
Container::Dynamic<PolyHedra_3D_Instances *> Train_Instances;
EntryContainer::Entry<Simple3D_InstData> Train_Rail_Instance_Entrys;
EntryContainer::Entry<Simple3D_InstData> Train_Wheel_Instance_Entrys;

void TrainSpline_Init()
{
	Train_Spline_Value = 0;
	Train_WheelSpin = 0;

	Train_Spline = new SplineCurve3D((SplineNode3D []) {
		SplineNode3D(Point3D(+100, 0, +100), Point3D()),
		SplineNode3D(Point3D(+100, 0, -100), Point3D()),
		SplineNode3D(Point3D(-100, 0, -100), Point3D()),
		SplineNode3D(Point3D(-100, 0, +100), Point3D()),
	}, 4, true, -0.5f, 0, 0);

	unsigned int idx_axis =	Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Drehgestell_Achse.polyhedra.ymt")));
							Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Drehgestell_Halter.polyhedra.ymt")));	//	Faces wrong way
							Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Drehgestell_Rahmen.polyhedra.ymt")));	//	Faces Wrong way
	unsigned int idx_rail =	Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Gleis_Seg.polyhedra.ymt")));			//	Faces Wrong way
							Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Schienen_Seg.polyhedra.ymt")));			//	Faces Wrong way
							Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Wagen_Flach.polyhedra.ymt")));			//	Faces Wrong way, some Geometry Wrong
							Train_PHs.Count(); Train_PHs.Insert(YMT::PolyHedra::Load(MediaDir.File("Wagen_Tief.polyhedra.ymt")));			//	Faces Wrong way, some Geometry Wrong

	for (unsigned int i = 0; i < Train_PHs.Count(); i++)
	{
		Train_Instances.Insert(new PolyHedra_3D_Instances(Train_PHs[i]));
	}

	Train_Rail_Instance_Entrys.Allocate(Train_Instances[idx_rail] -> Instances, 128);
	for (unsigned int i = 0; i < Train_Rail_Instance_Entrys.Length(); i++)
	{
		float t = i;
		t = t / (Train_Rail_Instance_Entrys.Length());
		t = t * (Train_Spline -> SegmentCount);
		SplineNode3D node = Train_Spline -> Calculate(t);
		Train_Rail_Instance_Entrys[i].Trans.Pos = node.Pos;
		Train_Rail_Instance_Entrys[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		Train_Rail_Instance_Entrys[i].Trans.Rot.CalcBack();
	}

	Train_Wheel_Instance_Entrys.Allocate(Train_Instances[idx_axis] -> Instances, 2);
}
void TrainSpline_Free()
{
	Train_Rail_Instance_Entrys.Dispose();
	Train_Wheel_Instance_Entrys.Dispose();
	for (unsigned int i = 0; i < Train_PHs.Count(); i++)
	{
		delete Train_PHs[i];
	}
	for (unsigned int i = 0; i < Train_Instances.Count(); i++)
	{
		delete Train_Instances[i];
	}
}
void TrainSpline_Update(float timeDelta)
{
	{
		SplineNode3D node = Train_Spline -> Calculate(Train_Spline_Value);
		Angle3D a = Angle3D::FromPoint3D(node.Dir);
		a.CalcBack();

		(*Train_Wheel_Instance_Entrys).Trans.Pos = node.Pos + a.rotate(Point3D(0, 6, 0));
		(*Train_Wheel_Instance_Entrys).Trans.Rot = a;
		(*Train_Wheel_Instance_Entrys).Trans.Rot.Y -= Train_WheelSpin;
		(*Train_Wheel_Instance_Entrys).Trans.Rot.CalcBack();
	}

	Train_Spline_Value += 0.01f * timeDelta;
	Train_WheelSpin = Train_Spline_Value * 24;
}



void InitRun()
{
	InitGraphics();
	TestSpline_Init();
	TrainSpline_Init();
}
void FreeRun()
{
	TrainSpline_Free();
	TestSpline_Free();
	FreeGraphics();
}



void Frame(double timeDelta)
{
	if (win -> IsCursorLocked())
	{
		ViewTrans.TransformFlatX(win -> MoveFromKeys(20.0f * timeDelta), win -> SpinFromCursor(0.2f * timeDelta));
	}
	ViewTrans.Rot.CalcBack();

	TestSpline_Update(timeDelta);
	TrainSpline_Update(timeDelta);

	PH_Shader -> Use();
	Uni_View -> PutData(ViewTrans);
	Test_Path_Instances -> Update().Draw();
	Test_Node_Instances -> Update().Draw();
	for (unsigned int i = 0; i < Train_Instances.Count(); i++)
	{
		Train_Instances[i] -> Update().Draw();
	}
}

void Resize(const SizeRatio2D & ViewPortSizeRatio)
{
	PH_Shader -> Use();
	Uni_ViewPortSizeRatio -> PutData(ViewPortSizeRatio);
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



	try
	{
		Debug::Log << "<<<< Run Window" << Debug::Done;
		win -> Run();
		Debug::Log << ">>>> Run Window" << Debug::Done;
	}
	catch (std::exception & e)
	{
		Debug::Log << "Run Exception: " << e.what() << '\n';
	}



	delete win;

	glfwTerminate();
	std::cout << "main() return";
	return 0;
}


