
#include <iostream>
#include <exception>
#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DataInclude.hpp"
#include "DataShow.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Simple3D/ManagerMulti.hpp"

#include "Window.hpp"
#include "ValueType/View.hpp"
#include "Function/Object.hpp"
#include "UserParameter/KeyBoardInclude.hpp"
#include "UserParameter/MouseInclude.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

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

#include "UI/Control/Base/Manager.hpp"
#include "UI/Text/Manager.hpp"
#include "UI/Text/Font/Font.hpp"
#include "SplineSegment3DControl.hpp"



struct MainContext
{
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
View	view;

MainContext() :
	ImageDir("../../media/Images"),
	ShaderDir("../../media/Shaders"),
	PolyHedraDir("../../media/YMT/Spline"),
	TextDir("../../media/Text"),
	window(),
	view()
{ }
~MainContext()
{ }



UI::Control::Manager UI_Control_Manager;
UI::Text::Manager UI_Text_Manager;

PolyHedra_Simple3D::ManagerMulti PolyHedra_3D_Manager;

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
	PolyHedra_3D_Manager.DefaultShader.FOV.Put(view.FOV);

	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("UI/Control.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("UI/Control.frag")));
		UI_Control_Manager.Shader.Change(code);
	}
	UI_Control_Manager.Shader.Create();
	UI_Control_Manager.BufferArray.Create();
	UI_Control_Manager.UpdateSize(window.Size);

	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("UI/Text.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("UI/Text.frag")));
		UI_Text_Manager.Shader.Change(code);
	}
	UI_Text_Manager.Shader.Create();
	UI_Text_Manager.BufferArray.Create();

	{
		UI_Text_Manager.TextFont = UI::Text::Font::Parse(TextDir.File("Font0.atlas"));
		UI_Text_Manager.Pallet_Texture.Create();
		UI_Text_Manager.Pallet_Texture.Bind();
		UI_Text_Manager.Pallet_Texture.Assign(UI_Text_Manager.TextFont -> AtlasTexture);
	}
	UI_Control_Manager.Window.ChangeManager(&UI_Control_Manager);
	UI_Control_Manager.Window.ChangeManager(&UI_Text_Manager);

	window.KeyBoardManager.KeyCallBack.Change(&UI_Control_Manager, &UI::Control::Manager::RelayKey);
	window.KeyBoardManager.TextCallBack.Change(&UI_Control_Manager, &UI::Control::Manager::RelayText);
	window.MouseManager.CallbackClick.Change(&UI_Control_Manager, &UI::Control::Manager::RelayClick);
	window.MouseManager.CallbackDrag.Change(&UI_Control_Manager, &UI::Control::Manager::RelayCursorDrag);
}
void FreeGraphics()
{ }



//PolyHedra * Test_Path_PH;
//PolyHedra * Test_Node_PH;

SplineCurve3D * Test_Spline;
Container::Binary<SplineObject> Test_Spline_Entrys;
//Container::Binary<EntryContainer::Entry<Simple3D::Data>> Test_Path_Instance_Entrys;
EntryContainer::Entry<Simple3D::Data> Test_Path_Instance_Entrys;
EntryContainer::Entry<Simple3D::Data> Test_Node_Instance_Entrys;



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
	{
		SplineNode3D nodes[6] {
			SplineNode3D(Point3D(+40, +10, -20), Point3D(+1, 0, +1)),
			SplineNode3D(Point3D(+40, -10, +20), Point3D(-1, 0, +1)),
			SplineNode3D(Point3D(  0,   0, +40), Point3D(-1, 0,  0)),
			SplineNode3D(Point3D(-40,   0, +20), Point3D(-1, 0, -1)),
			SplineNode3D(Point3D(-40,   0, -20), Point3D(+1, 0, -1)),
			SplineNode3D(Point3D(  0,   0, -40), Point3D(+1, 0,  0)),
		};
		Test_Spline = new SplineCurve3D(nodes, 6, true, 0, 0, 0);
	}
std::cout << __LINE__ << '\n';

	Test_Node_Instance_Entrys = PolyHedra_3D_Manager.Place(PolyHedra::Generate::HexaHedron(1.0f), (Test_Spline -> SegmentCount) * 2);
std::cout << __LINE__ << '\n';
	for (unsigned int i = 0; i < Test_Spline -> SegmentCount; i++)
	{
		Test_Node_Instance_Entrys[i * 2 + 0].Trans.Pos = Test_Spline -> Segments[i].Node0.Pos;
		Test_Node_Instance_Entrys[i * 2 + 1].Trans.Pos = Test_Spline -> Segments[i].Node1.Pos;
	}

	Test_Path_Instance_Entrys = PolyHedra_3D_Manager.Place(PolyHedra::Generate::ConeC(8, 0.5f, 2.0f), 96);
	for (unsigned int i = 0; i < Test_Path_Instance_Entrys.Length(); i++)
	{
		Test_Spline_Entrys.Insert(SplineObject(i, (((float)i) / Test_Path_Instance_Entrys.Length()) * Test_Spline -> SegmentCount));
	}
}
void TestSpline_Free()
{
	Test_Path_Instance_Entrys.Dispose();
	Test_Node_Instance_Entrys.Dispose();
}
void TestSpline_Update(float timeDelta)
{
	for (unsigned int i = 0; i < Test_Path_Instance_Entrys.Length(); i++)
	{
		SplineNode3D node = Test_Spline -> Interpolate0(Test_Spline_Entrys[i].SplineValue);

		Test_Path_Instance_Entrys[i].Trans.Pos = node.Pos;
		Test_Path_Instance_Entrys[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		//Test_Path_Instance_Entrys[i].Trans.Rot.CalcBack();

		Test_Spline_Entrys[i].SplineValue += 0.1f * timeDelta;
	}
}



UI::Control::Form * Form;
UI::Control::SplineSegment3D * SplineSegment3D_Control;

SplineCurve3D * Train_Spline;
Container::Binary<SplineObject> Train_Rail_Spline_Entrys;
float Train_Spline_Value;
float Train_WheelSpin;

EntryContainer::Entry<Simple3D::Data> Train_Rail_Instance_Entry;
EntryContainer::Entry<Simple3D::Data> Train_Wheel_Instance_Entry;

void TrainSpline_Init()
{
	Train_Spline_Value = 0;
	Train_WheelSpin = 0;

	{
		SplineNode3D nodes[4]
		{
			SplineNode3D(Point3D(+100, 0, +100), Point3D(+200, 0, -200)),
			SplineNode3D(Point3D(+100, 0, -100), Point3D(-200, 0, -200)),
			SplineNode3D(Point3D(-100, 0, -100), Point3D(-200, 0, +200)),
			SplineNode3D(Point3D(-100, 0, +100), Point3D(+200, 0, +200)),
		};
		Train_Spline = new SplineCurve3D(nodes, 4, true, -0.5f, 0, 0);
	}

	unsigned int idx_axis =	PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Achse.polyhedra")));
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Halter.polyhedra")));	//	Faces wrong way
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Rahmen.polyhedra")));	//	Faces Wrong way
	unsigned int idx_rail =	PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Gleis_Seg.polyhedra")));				//	Faces Wrong way
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Schienen_Seg.polyhedra")));			//	Faces Wrong way
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Wagen_Flach.polyhedra")));			//	Faces Wrong way, some Geometry Wrong
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Wagen_Tief.polyhedra")));			//	Faces Wrong way, some Geometry Wrong

	Train_Rail_Instance_Entry = PolyHedra_3D_Manager.Place(idx_rail, 128);
	/*for (unsigned int i = 0; i < Train_Rail_Instance_Entry.Length(); i++)
	{
		float t = i;
		t = t / (Train_Rail_Instance_Entry.Length());
		t = t * (Train_Spline -> SegmentCount);
		SplineNode3D node = Train_Spline -> Interpolate0(t);
		Train_Rail_Instance_Entry[i].Trans.Pos = node.Pos;
		Train_Rail_Instance_Entry[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		//Train_Rail_Instance_Entry[i].Trans.Rot.CalcBack();
	}*/

	Train_Wheel_Instance_Entry = PolyHedra_3D_Manager.Place(idx_axis, 2);
}
void TrainSpline_Free()
{
	Train_Rail_Instance_Entry.Dispose();
	Train_Wheel_Instance_Entry.Dispose();
}
void TrainSpline_Update(float timeDelta)
{
	for (unsigned int i = 0; i < Train_Rail_Instance_Entry.Length(); i++)
	{
		float t = i;
		t = t / (Train_Rail_Instance_Entry.Length());
		t = t * (Train_Spline -> SegmentCount);
		SplineNode3D node = Train_Spline -> InterpolateKochanekBartels(t);
		Train_Rail_Instance_Entry[i].Trans.Pos = node.Pos;
		Train_Rail_Instance_Entry[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
	}

	{
		SplineNode3D node = Train_Spline -> InterpolateKochanekBartels(Train_Spline_Value);
		Angle3D a = Angle3D::FromPoint3D(node.Dir);
		(*Train_Wheel_Instance_Entry).Trans.Pos = node.Pos + a.rotateBack(Point3D(0, 6, 0));
		(*Train_Wheel_Instance_Entry).Trans.Rot = a;
		(*Train_Wheel_Instance_Entry).Trans.Rot.Y -= Angle::Radians(Train_WheelSpin);
		(*Train_Wheel_Instance_Entry).Trans.Rot.CalcMatrix();
	}

	Train_Spline_Value += 0.01f * timeDelta;
	Train_WheelSpin = Train_Spline_Value * 24;
}



void MakeRun()
{
	SplineSegment3D_Control = new UI::Control::SplineSegment3D();
	UI_Control_Manager.Window.ChildInsert(SplineSegment3D_Control);
}

void InitRun()
{
	InitGraphics();
	TestSpline_Init();
	TrainSpline_Init();

	MakeRun();
	//if (Test_Spline -> SegmentCount != 0) { SplineSegment3D_Control -> ChangeObject(&(Test_Spline -> Segments[0])); }
	if (Train_Spline -> SegmentCount != 0) { SplineSegment3D_Control -> ChangeObject(&(Train_Spline -> Segments[0])); }
}
void FreeRun()
{
	TrainSpline_Free();
	TestSpline_Free();
	FreeGraphics();
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

	TestSpline_Update(timeDelta);
	TrainSpline_Update(timeDelta);

	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.View.Put(view.Trans);
	PolyHedra_3D_Manager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	Point2D mouse = window.MouseManager.CursorPixelPosition().Absolute;
	UI_Control_Manager.UpdateMouse(mouse);
	UI_Control_Manager.Window.UpdateEntrys();
	UI_Control_Manager.Draw();
	UI_Text_Manager.Draw();
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.WindowSize.Put(WindowSize);

	UI_Control_Manager.Shader.Bind();
	UI_Control_Manager.Shader.WindowSize.Put(WindowSize);

	UI_Text_Manager.Shader.Bind();
	UI_Text_Manager.Shader.WindowSize.Put(WindowSize);

	UI_Control_Manager.UpdateSize(WindowSize);
}



int Main()
{
	window.InitCallBack.Change<MainContext>(this, &MainContext::InitRun);
	window.FreeCallBack.Change<MainContext>(this, &MainContext::FreeRun);
	window.FrameCallBack.Change<MainContext>(this, &MainContext::Frame);
	window.ResizeCallBack.Change<MainContext>(this, &MainContext::Resize);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
};



int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
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
