
#include <iostream>
#include <exception>
#include "OpenGL.hpp"
#include "Debug.hpp"

// Value Types
#include "ValueType/_Include.hpp"
#include "ValueType/_Show.hpp"

// Graphics
#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/Uniform/_Include.hpp"
#include "Graphics/Multiform/_Include.hpp"

// PolyHedra
#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "PolyHedra/Manager.hpp"
#include "PolyHedra/Object.hpp"

// General
#include "Window.hpp"
#include "FrameTime.hpp"
#include "Miscellaneous/Function/Object.hpp"
#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"

// FileManager
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

// Spline
#include "Factors.hpp"
#include "SplineNode3D.hpp"
#include "SplineSegment3D.hpp"
#include "SplineCurve3D.hpp"
#include "SplineObject.hpp"

// UI
#include "Control/Base/Manager.hpp"
#include "Text/Manager.hpp"
#include "Text/Font/Font.hpp"
#include "SplineSegment3DControl.hpp"

// Spline
#include "ChainNeighbours3D.hpp"
#include "CubicSpline3D.hpp"
#include "CubicSplineCurve3D.hpp"



struct MainContext
{
DirectoryInfo MediaDirectory;
DirectoryInfo ImageDir;
DirectoryInfo ShaderDir;
DirectoryInfo PolyHedraDir;
DirectoryInfo TextDir;

Window	window;
View3D	view;

::PolyHedraManager		PolyHedraManager;
UI::Text::Manager		TextManager;
UI::Control::Manager	ControlManager;

MainContext()
	: MediaDirectory("../../media")
	, ImageDir("../../media/Images")
	, ShaderDir("../../media/Shaders")
	, PolyHedraDir("../../media/YMT/Spline")
	, TextDir("../../media/Text")
	, window()
	, view()
	, PolyHedraManager()
	, TextManager()
	, ControlManager()
{
	PolyHedraManager.MakeCurrent();
	TextManager.MakeCurrent();
	ControlManager.MakeCurrent();
}
~MainContext()
{ }



void InitGraphics()
{
	PolyHedraManager.InitExternal(MediaDirectory); // do this outside ? so in MainContext ?
	PolyHedraManager.GraphicsCreate();
	PolyHedraManager.InitInternal(); // do this in GraphicsCreate ?

	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Text.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Text.frag")),
		});
		TextManager.Shader.Change(code);
	}
	{
		TextManager.Buffer.Main.Pos.Change(0);
		TextManager.Buffer.Inst.Pos.Change(1);
		TextManager.Buffer.Inst.PalletMin.Change(2);
		TextManager.Buffer.Inst.PalletMax.Change(3);
		TextManager.Buffer.Inst.BoundMin.Change(4);
		TextManager.Buffer.Inst.BoundMax.Change(5);
	}
	{
		TextManager.TextFont = UI::Text::Font::Parse(
			MediaDirectory.File("Text/Font0.atlas")
		);
	}

	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.vert")),
			Shader::Code(MediaDirectory.File("Shaders/UI/Control.frag")),
		});
		ControlManager.Shader.Change(code);
	}
	{
		ControlManager.Buffer.Main.Pos.Change(0);
		ControlManager.Buffer.Inst.Min.Change(1);
		ControlManager.Buffer.Inst.Max.Change(2);
		ControlManager.Buffer.Inst.Layer.Change(3);
		ControlManager.Buffer.Inst.Col.Change(4);
	}
	{
		ControlManager.Window.ChangeManager(&ControlManager);
		ControlManager.Window.ChangeManager(&TextManager);
	}

	TextManager.GraphicsCreate();
	ControlManager.GraphicsCreate();

	window.KeyBoardManager.CallBack_KeyEvent.Assign(&ControlManager, &UI::Control::Manager::RelayKey);
	window.KeyBoardManager.CallBack_TextEvent.Assign(&ControlManager, &UI::Control::Manager::RelayText);
	window.MouseManager.Callback_ClickEvent.Assign(&ControlManager, &UI::Control::Manager::RelayClick);
	window.MouseManager.Callback_DragEvent.Assign(&ControlManager, &UI::Control::Manager::RelayCursorDrag);
}
void FreeGraphics()
{
	PolyHedraManager.GraphicsDelete();
	TextManager.GraphicsDelete();
	ControlManager.GraphicsDelete();
}

struct PolyHedraObjectArray
{
	unsigned int		Count;
	PolyHedraObject *	Array;

	PolyHedraObject &	operator[](unsigned int i)
	{
		return Array[i];
	}

	~PolyHedraObjectArray()
	{
		delete[] Array;
	}
	PolyHedraObjectArray()
		: Count(0)
		, Array(nullptr)
	{ }
	PolyHedraObjectArray(const PolyHedraObjectArray & other) = delete;
	PolyHedraObjectArray & operator=(const PolyHedraObjectArray & other) = delete;

	void Create(PolyHedra * polyhedra, unsigned int count)
	{
		Count = count;
		Array = new PolyHedraObject[Count];
		for (unsigned int i = 0; i < Count; i++)
		{
			Array[i].Create(polyhedra);
		}
	}
	void Create(unsigned int polyhedra, unsigned int count)
	{
		Count = count;
		Array = new PolyHedraObject[Count];
		for (unsigned int i = 0; i < Count; i++)
		{
			Array[i].Create(polyhedra);
		}
	}

	void Delete()
	{
		delete[] Array;
		Array = nullptr;
		Count = 0;
	}
};



//PolyHedra * Test_Path_PH;
//PolyHedra * Test_Node_PH;

SplineCurve3D * Test_Spline;
Container::Binary<SplineObject> Test_Spline_Entrys;
//Container::Binary<EntryContainer::Entry<Simple3D::Data>> Test_Path_Instance_Entrys;
//EntryContainer::Entry<Simple3D::Data> Test_Path_Instance_Entrys;
//EntryContainer::Entry<Simple3D::Data> Test_Node_Instance_Entrys;
PolyHedraObjectArray Test_Path_Instance_Entrys;
PolyHedraObjectArray Test_Node_Instance_Entrys;



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

	Test_Node_Instance_Entrys.Create(PolyHedra::Generate::HexaHedron(1.0f), (Test_Spline -> SegmentCount) * 2);
	for (unsigned int i = 0; i < Test_Spline -> SegmentCount; i++)
	{
		Test_Node_Instance_Entrys[i * 2 + 0].Trans().Position = Test_Spline -> Segments[i].Node0.Pos;
		Test_Node_Instance_Entrys[i * 2 + 1].Trans().Position = Test_Spline -> Segments[i].Node1.Pos;
	}

	Test_Path_Instance_Entrys.Create(PolyHedra::Generate::ConeC(8, 0.5f, 2.0f), 96);
	for (unsigned int i = 0; i < Test_Path_Instance_Entrys.Count; i++)
	{
		Test_Spline_Entrys.Insert(SplineObject(i, (((float)i) / Test_Path_Instance_Entrys.Count) * Test_Spline -> SegmentCount));
	}
}
void TestSpline_Free()
{
	Test_Path_Instance_Entrys.Delete();
	Test_Node_Instance_Entrys.Delete();
}
void TestSpline_Update(float timeDelta)
{
	for (unsigned int i = 0; i < Test_Path_Instance_Entrys.Count; i++)
	{
		SplineNode3D node = Test_Spline -> Interpolate0(Test_Spline_Entrys[i].SplineValue);

		Test_Path_Instance_Entrys[i].Trans().Position = node.Pos;
		Test_Path_Instance_Entrys[i].Trans().Rotation = EulerAngle3D::PointToZ(node.Dir);
		//Test_Path_Instance_Entrys[i].Trans.Rot.CalcBack();

		Test_Spline_Entrys[i].SplineValue += 0.1f * timeDelta;
	}
}



UI::Control::Form * Form;
UI::Control::SplineSegment3D * SplineSegment3D_Control;
CubicSpline3D::FactorsTCB	TCB;

//SplineCurve3D * Train_Spline;
CubicSplineCurve3D * Train_Spline;
Container::Binary<SplineObject> Train_Rail_Spline_Entrys;
float Train_Spline_Value;
float Train_WheelSpin;

//EntryContainer::Entry<Simple3D::Data> Train_Node_Instance_Entrys;
//EntryContainer::Entry<Simple3D::Data> Train_Rail_Instance_Entry;
//EntryContainer::Entry<Simple3D::Data> Train_Wheel_Instance_Entry;
PolyHedraObjectArray Train_Node_Instance_Entrys;
PolyHedraObjectArray Train_Rail_Instance_Entry;
PolyHedraObjectArray Train_Wheel_Instance_Entry;

void TrainSpline_Init()
{
	Train_Spline_Value = 0;
	Train_WheelSpin = 0;

	{
		Train_Spline = new CubicSplineCurve3D();
		Train_Spline -> Nodes.List({
			Point3D(+100, 0, +100),
			Point3D(+100, 0, -100),
			Point3D(-100, 0, -100),
			Point3D(-100, 0, +100),
		});
		/*Train_Spline -> Nodes.List({
			Point3D(+50, 0, +100),
			Point3D(+50, 0,    0),
			Point3D(+50, 0, -100),
			Point3D(-50, 0, -100),
			Point3D(-50, 0,    0),
			Point3D(-50, 0, +100),
		});*/
		/*Train_Spline -> Nodes.List({
			Point3D(+ 25, 0, +100),
			Point3D(+ 75, 0, +100),
			Point3D(+100, 0, + 75),
			Point3D(+100, 0, + 25),

			Point3D(+100, 0, - 25),
			Point3D(+100, 0, - 75),
			Point3D(+ 75, 0, -100),
			Point3D(+ 25, 0, -100),

			Point3D(- 25, 0, -100),
			Point3D(- 75, 0, -100),
			Point3D(-100, 0, - 75),
			Point3D(-100, 0, - 25),

			Point3D(-100, 0, + 25),
			Point3D(-100, 0, + 75),
			Point3D(- 75, 0, +100),
			Point3D(- 25, 0, +100),
		});*/
		Train_Spline -> FiniteDifference();
	}

	Train_Node_Instance_Entrys.Create(PolyHedra::Generate::HexaHedron(2.0f), Train_Spline -> Nodes.Count());
	for (unsigned int i = 0; i < Train_Node_Instance_Entrys.Count; i++)
	{
		Train_Node_Instance_Entrys[i].Trans().Position = Train_Spline -> Nodes[i];
	}

	unsigned int idx_axis =	PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Achse.polyhedra")));
							PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Halter.polyhedra")));	//	Faces wrong way
							PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Rahmen.polyhedra")));	//	Faces Wrong way
	unsigned int idx_rail =	PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Gleis_Seg.polyhedra")));				//	Faces Wrong way
							PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Schienen_Seg.polyhedra")));			//	Faces Wrong way
							PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Wagen_Flach.polyhedra")));			//	Faces Wrong way, some Geometry Wrong
							PolyHedraManager.PlacePolyHedra(PolyHedra::Load(PolyHedraDir.File("Wagen_Tief.polyhedra")));			//	Faces Wrong way, some Geometry Wrong

	Train_Rail_Instance_Entry.Create(idx_rail, 64);
	//Train_Rail_Instance_Entry = PolyHedra_3D_Manager.Place(idx_rail, 128);
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

	Train_Wheel_Instance_Entry.Create(idx_axis, 1);
}
void TrainSpline_Free()
{
	Train_Rail_Instance_Entry.Delete();
	Train_Wheel_Instance_Entry.Delete();
}
void TrainSpline_Update(float timeDelta)
{
	Train_Spline -> KochanekBartels(TCB);

	for (unsigned int i = 0; i < Train_Rail_Instance_Entry.Count; i++)
	{
		float t = i;
		t = t / (Train_Rail_Instance_Entry.Count);
		//t = t * (Train_Spline -> SegmentCount);
		t = t * (Train_Spline -> Segments.Count());
		//SplineNode3D node = Train_Spline -> InterpolateKochanekBartels(t);
		SplineNode3D node;
		node.Pos = Train_Spline -> InterPolatePos(t);
		node.Dir = Train_Spline -> InterPolateDir(t);
		Train_Rail_Instance_Entry[i].Trans().Position = node.Pos;
		Train_Rail_Instance_Entry[i].Trans().Rotation = EulerAngle3D::PointToZ(node.Dir);
	}

	{
		//SplineNode3D node = Train_Spline -> InterpolateKochanekBartels(Train_Spline_Value);
		SplineNode3D node;
		node.Pos = Train_Spline -> InterPolatePos(Train_Spline_Value);
		node.Dir = Train_Spline -> InterPolateDir(Train_Spline_Value);
		EulerAngle3D a = EulerAngle3D::PointToZ(node.Dir);
		Train_Wheel_Instance_Entry[0].Trans().Position = node.Pos + a.reverse(Point3D(0, 6, 0));
		Train_Wheel_Instance_Entry[0].Trans().Rotation = a;
		Train_Wheel_Instance_Entry[0].Trans().Rotation.X1 += Angle::Radians(Train_WheelSpin);
	}

	Train_Spline_Value += 0.01f * timeDelta;
	Train_WheelSpin = Train_Spline_Value * 24;
}



void MakeRun()
{
	SplineSegment3D_Control = new UI::Control::SplineSegment3D();
	ControlManager.Window.ChildInsert(SplineSegment3D_Control);
}

void InitRun()
{
	InitGraphics();
	TestSpline_Init();
	TrainSpline_Init();

	MakeRun();
	//if (Test_Spline -> SegmentCount != 0) { SplineSegment3D_Control -> ChangeObject(&(Test_Spline -> Segments[0])); }
	//if (Train_Spline -> Segments.Count() != 0) { SplineSegment3D_Control -> ChangeObject(&(Train_Spline -> Segments[0])); }
	SplineSegment3D_Control -> ChangeObject(&TCB);
}
void FreeRun()
{
	TrainSpline_Free();
	TestSpline_Free();
	FreeGraphics();
}

void UpdateView(FrameTime frame_time)
{
	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Position *= 10; }
		trans.Position *= 2;
		trans.Rotation *= view.FOV.ToRadians() * 0.05f;
		view.ChangeFlatX(trans, frame_time.Delta);
	}
}

void Frame(double timeDelta)
{
	FrameTime frame_time(60);
	frame_time.Update(timeDelta);
	UpdateView(frame_time);

	TestSpline_Update(timeDelta);
	TrainSpline_Update(timeDelta);

	PolyHedraManager.ClearInstances();
	PolyHedraManager.UpdateInstances();
	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderFullDefault.DisplaySize.Put(window.Size);
		PolyHedraManager.ShaderFullDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderFullDefault.View.Put(Matrix4x4::TransformReverse(view.Trans));
		PolyHedraManager.ShaderFullDefault.FOV.Put(view.FOV);
		PolyHedraManager.DrawFull();
	}
	{
		PolyHedraManager.ShaderWireDefault.Bind();
		PolyHedraManager.ShaderWireDefault.DisplaySize.Put(window.Size);
		PolyHedraManager.ShaderWireDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderWireDefault.View.Put(Matrix4x4::TransformReverse(view.Trans));
		PolyHedraManager.ShaderWireDefault.FOV.Put(view.FOV);
		PolyHedraManager.DrawWire();
	}

	GL::Clear(GL::ClearMask::DepthBufferBit);
	{
		Point2D mouse = window.MouseManager.CursorPosition().Buffer.Corner;
		ControlManager.UpdateMouse(mouse);
		ControlManager.Window.UpdateEntrys();
		ControlManager.Draw();
	}
	TextManager.Draw();
}

void Resize(const DisplaySize & DisplaySize)
{
	PolyHedraManager.ShaderFullDefault.DisplaySize.Put(DisplaySize);
	PolyHedraManager.ShaderWireDefault.DisplaySize.Put(DisplaySize);

	TextManager.Shader.DisplaySize.Put(DisplaySize);

	ControlManager.UpdateSize(DisplaySize);
	ControlManager.Shader.DisplaySize.Put(DisplaySize);
}



int Main()
{
	window.InitCallBack.Assign<MainContext>(this, &MainContext::InitRun);
	window.FreeCallBack.Assign<MainContext>(this, &MainContext::FreeRun);
	window.FrameCallBack.Assign<MainContext>(this, &MainContext::Frame);
	window.ResizeCallBack.Assign<MainContext>(this, &MainContext::Resize);

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
