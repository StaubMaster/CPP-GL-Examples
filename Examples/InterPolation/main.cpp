
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



UI::Control::Manager * UI_Control_Manager;
UI::Text::Manager * UI_Text_Manager;

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
	float fov_rad = Angle3D::DegreeToRadian(view.FOV);
	PolyHedra_3D_Manager.DefaultShader.FOV.PutData(&fov_rad);

	UI_Control_Manager = new UI::Control::Manager(ShaderDir);
	UI_Text_Manager = new UI::Text::Manager(ShaderDir, TextDir);
	UI_Control_Manager -> UpdateSize(window.Size);
}
void FreeGraphics()
{
	delete UI_Control_Manager;
	delete UI_Text_Manager;
}



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

	Test_Node_Instance_Entrys = PolyHedra_3D_Manager.Place(PolyHedra::Generate::HexaHedron(1.0f), (Test_Spline -> SegmentCount) * 2);
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
		SplineNode3D node = Test_Spline -> Calculate(Test_Spline_Entrys[i].SplineValue);

		Test_Path_Instance_Entrys[i].Trans.Pos = node.Pos;
		Test_Path_Instance_Entrys[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		Test_Path_Instance_Entrys[i].Trans.Rot.CalcBack();

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
		SplineNode3D nodes[4] {
			SplineNode3D(Point3D(+100, 0, +100), Point3D()),
			SplineNode3D(Point3D(+100, 0, -100), Point3D()),
			SplineNode3D(Point3D(-100, 0, -100), Point3D()),
			SplineNode3D(Point3D(-100, 0, +100), Point3D()),
		};
		Train_Spline = new SplineCurve3D(nodes, 4, true, -0.5f, 0, 0);
	}

	unsigned int idx_axis =	PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Achse.polyhedra.ymt")));
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Halter.polyhedra.ymt")));	//	Faces wrong way
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Drehgestell_Rahmen.polyhedra.ymt")));	//	Faces Wrong way
	unsigned int idx_rail =	PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Gleis_Seg.polyhedra.ymt")));			//	Faces Wrong way
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Schienen_Seg.polyhedra.ymt")));			//	Faces Wrong way
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Wagen_Flach.polyhedra.ymt")));			//	Faces Wrong way, some Geometry Wrong
							PolyHedra_3D_Manager.Insert(PolyHedra::Load(PolyHedraDir.File("Wagen_Tief.polyhedra.ymt")));			//	Faces Wrong way, some Geometry Wrong

	Train_Rail_Instance_Entry = PolyHedra_3D_Manager.Place(idx_rail, 128);
	for (unsigned int i = 0; i < Train_Rail_Instance_Entry.Length(); i++)
	{
		float t = i;
		t = t / (Train_Rail_Instance_Entry.Length());
		t = t * (Train_Spline -> SegmentCount);
		SplineNode3D node = Train_Spline -> Calculate(t);
		Train_Rail_Instance_Entry[i].Trans.Pos = node.Pos;
		Train_Rail_Instance_Entry[i].Trans.Rot = Angle3D::FromPoint3D(node.Dir);
		Train_Rail_Instance_Entry[i].Trans.Rot.CalcBack();
	}

	Train_Wheel_Instance_Entry = PolyHedra_3D_Manager.Place(idx_axis, 2);
}
void TrainSpline_Free()
{
	Train_Rail_Instance_Entry.Dispose();
	Train_Wheel_Instance_Entry.Dispose();
}
void TrainSpline_Update(float timeDelta)
{
	{
		SplineNode3D node = Train_Spline -> Calculate(Train_Spline_Value);
		Angle3D a = Angle3D::FromPoint3D(node.Dir);
		a.CalcBack();

		(*Train_Wheel_Instance_Entry).Trans.Pos = node.Pos + a.rotate(Point3D(0, 6, 0));
		(*Train_Wheel_Instance_Entry).Trans.Rot = a;
		(*Train_Wheel_Instance_Entry).Trans.Rot.Y -= Train_WheelSpin;
		(*Train_Wheel_Instance_Entry).Trans.Rot.CalcBack();
	}

	Train_Spline_Value += 0.01f * timeDelta;
	Train_WheelSpin = Train_Spline_Value * 24;
}



UI::Control::Form * Example_Form;
UI::Control::TextBox * Example_TextBox_0;
UI::Control::TextBox * Example_TextBox_1;
UI::Control::TextBox * Example_TextBox_2;
void UI_Make_Example()
{
	UI::Control::Form * form;
	UI::Control::GroupBox * group_box;
	UI::Control::Button * button;
	UI::Control::TextBox * text;
	UI::Control::Slider * slider;
	UI::Control::CheckBox * check_box;

	form = new UI::Control::Form();
	UI_Control_Manager -> Window -> ChildInsert(form);
	//form -> Hide();
	Example_Form = form;

	float w = 0;
	float h = 0;

	group_box = new UI::Control::GroupBox();
	group_box -> Anchor.X.Anchor = ANCHOR_BOTH;
	group_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	group_box -> Anchor.X.SetPaddedMinDist(0);
	group_box -> Anchor.X.SetPaddedMaxDist(0);
	group_box -> Anchor.Y.SetPaddedMaxDist(h);
	form -> ChildInsert(group_box);

	button = new UI::Control::Button();
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> Anchor.X.SetPaddedMinDist(w);
	button -> Anchor.Y.SetPaddedMaxDist(h);
	//button -> ClickFunc = click0;
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetPaddedMinSize();

	button = new UI::Control::Button();
	button -> Anchor.X.Anchor = ANCHOR_MIN;
	button -> Anchor.Y.Anchor = ANCHOR_MAX;
	button -> Anchor.X.SetPaddedMinDist(w);
	button -> Anchor.Y.SetPaddedMaxDist(h);
	//button -> ClickFunc = click1;
	group_box -> ChildInsert(button);

	w = button -> Anchor.X.GetPaddedMinSize();

	check_box = new UI::Control::CheckBox();
	check_box -> Anchor.X.Anchor = ANCHOR_MIN;
	check_box -> Anchor.Y.Anchor = ANCHOR_MAX;
	check_box -> Anchor.X.SetPaddedMinDist(w);
	check_box -> Anchor.Y.SetPaddedMaxDist(h);
	group_box -> ChildInsert(check_box);

	w = 0;
	h = check_box -> Anchor.Y.GetPaddedMaxSize();

	text = new UI::Control::TextBox(*UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_MAX;
	text -> Anchor.X.SetPaddedMinDist(0);
	text -> Anchor.X.SetPaddedMaxDist(0);
	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("Text0");
	group_box -> ChildInsert(text);
	Example_TextBox_0 = text;

	w = 0;
	h = text -> Anchor.Y.GetPaddedMaxSize();

	text = new UI::Control::TextBox(*UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_MAX;
	text -> Anchor.X.SetPaddedMinDist(0);
	text -> Anchor.X.SetPaddedMaxDist(0);
	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("Text1");
	group_box -> ChildInsert(text);
	Example_TextBox_1 = text;

	w = 0;
	h = group_box -> Anchor.Y.GetPaddedMaxSize();

	slider = new UI::Control::Slider();
	slider -> Anchor.X.Anchor = ANCHOR_MIN;
	slider -> Anchor.Y.Anchor = ANCHOR_MAX;
	slider -> Anchor.X.SetPaddedMinDist(w);
	slider -> Anchor.X.SetSize(200);
	slider -> Anchor.Y.SetPaddedMaxDist(h);
	//slider -> ValueChangedFunc = &slider_changed_callback;
	form -> ChildInsert(slider);

	w = slider -> Anchor.X.GetPaddedMinSize();

	text = new UI::Control::TextBox(*UI_Text_Manager);
	text -> Anchor.X.Anchor = ANCHOR_BOTH;
	text -> Anchor.Y.Anchor = ANCHOR_MAX;
	text -> Anchor.X.SetPaddedMinDist(w);
	text -> Anchor.X.SetPaddedMaxDist(0);
	text -> Anchor.Y.SetPaddedMaxDist(h);
	text -> SetText("0");
	text -> ReadOnly = true;
	form -> ChildInsert(text);
	Example_TextBox_2 = text;
}



void MakeRun()
{
	//Form = new UI::Control::Form();
	//UI_Control_Manager -> Window -> ChildInsert(Form);

	SplineSegment3D_Control = new UI::Control::SplineSegment3D(*UI_Text_Manager);
	//Form -> ChildInsert(SplineSegment3D_Control);

	//SplineSegment3D_Control -> ChildInsert(&(SplineSegment3D_Control -> T_Slider));
	//SplineSegment3D_Control -> ChildInsert(&(SplineSegment3D_Control -> T_Text));
	//SplineSegment3D_Control -> ChildInsert(&(SplineSegment3D_Control -> B_Slider));
	//SplineSegment3D_Control -> ChildInsert(&(SplineSegment3D_Control -> B_Text));
	//SplineSegment3D_Control -> ChildInsert(&(SplineSegment3D_Control -> C_Slider));
	//SplineSegment3D_Control -> ChildInsert(&(SplineSegment3D_Control -> C_Text));
	UI_Control_Manager -> Window -> ChildInsert(SplineSegment3D_Control);

	//UI_Make_Example();
}

void InitRun()
{
	InitGraphics();
	TestSpline_Init();
	TrainSpline_Init();

	MakeRun();
}
void FreeRun()
{
	TrainSpline_Free();
	TestSpline_Free();
	FreeGraphics();
}



void Frame(double timeDelta)
{
	if (window.Keys[GLFW_KEY_TAB].IsPress()) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();
		if (window.Keys[GLFW_KEY_LEFT_CONTROL].IsDown()) { trans.Pos *= 10; }
		trans.Pos *= 2;
		trans.Rot.X *= view.FOV * 0.005f;
		trans.Rot.Y *= view.FOV * 0.005f;
		trans.Rot.Z *= view.FOV * 0.005f;
		view.TransformFlatX(trans, timeDelta);
	}

	TestSpline_Update(timeDelta);
	TrainSpline_Update(timeDelta);

	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.View.Put(view.Trans);
	PolyHedra_3D_Manager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	Point2D mouse = window.MouseManager.CursorPixelPosition().Absolute;
	UI_Control_Manager -> UpdateMouse(mouse);
	UI_Control_Manager -> Window -> UpdateEntrys();
	UI_Control_Manager -> Draw();
	UI_Text_Manager -> Draw();

	std::cout << "Anchor:\n";
	std::cout << (UI_Control_Manager -> Window -> AnchorBox) << '\n';
	//std::cout << (SplineSegment3D_Control -> AnchorBox) << '\n';
	//std::cout << (SplineSegment3D_Control -> T_Slider.AnchorBox) << '\n';
	std::cout << '\n';
	{
		std::cout << "Count: " << (UI_Control_Manager -> Inst_Data_Container.Count()) << '\n';
		for (unsigned int i = 0; i < UI_Control_Manager -> Inst_Data_Container.Count(); i++)
		{
			std::cout << (UI_Control_Manager -> Inst_Data_Container[i].Min) << ' ' << (UI_Control_Manager -> Inst_Data_Container[i].Max) << '\n';
		}
	}
	std::cout << '\n';
}

void Resize(const WindowBufferSize2D & WindowSize)
{
	PolyHedra_3D_Manager.DefaultShader.Bind();
	PolyHedra_3D_Manager.DefaultShader.WindowSize.Put(WindowSize);

	UI_Control_Manager -> Shader.Bind();
	UI_Control_Manager -> Shader.WindowSize.Put(WindowSize);

	UI_Text_Manager -> Shader.Bind();
	UI_Text_Manager -> Shader.WindowSize.Put(WindowSize);

	UI_Control_Manager -> UpdateSize(WindowSize);
}

int Main()
{
	window.Create();
	window.InitCallBack.Change(ObjectFunction<MainContext, void>::New(this, &MainContext::InitRun));
	window.FreeCallBack.Change(ObjectFunction<MainContext, void>::New(this, &MainContext::FreeRun));
	window.FrameCallBack.Change(ObjectFunction<MainContext, void, double>::New(this, &MainContext::Frame));
	window.ResizeCallBack.Change(ObjectFunction<MainContext, void, const WindowBufferSize2D &>::New(this, &MainContext::Resize));

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
