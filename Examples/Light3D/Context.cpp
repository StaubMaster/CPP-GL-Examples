#include "Context.hpp"
#include "General/UnitToString.hpp"

#include "PolyHedra/Generate.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "PolyHedraUI/PalletManager.hpp"
#include "PolyHedraUI/ObjectData.hpp"

#include "ValueType/Intersect.hpp"

#include "UserTrans3DChange.hpp"



static ::UserTrans3DChange	UserTrans3DChange;



MultiformLayout::~MultiformLayout()
{ }
MultiformLayout::MultiformLayout()
	: Multiform::Layout()
	, DisplaySize("DisplaySize")
	, View("View")
	, Depth("Depth")
	, FOV("FOV")
{
	Multiforms.Insert(&DisplaySize);
	Multiforms.Insert(&View);
	Multiforms.Insert(&Depth);
	Multiforms.Insert(&FOV);
}



Light3DContext::~Light3DContext()
{ }
Light3DContext::Light3DContext()
	: ContextBase()
	, PolyHedraManager()
	, UIManager()
	, UISceneObject()
	, PolyHedraUIManager()
	, LightShaderLayout()
{
	PolyHedraManager.MakeCurrent();
	PolyHedraUIManager.MakeCurrent();

	Container::Array<Uniform::Layout*> layouts({
		&PolyHedraManager.ShaderLayoutFullDefault,
		&PolyHedraManager.ShaderLayoutWireDefault,
		&UIManager.ControlManager.ShaderLayout,
		&UIManager.TextManager.ShaderLayout,
		&UIManager.GraphManager.ShaderLayout,
		&LightShaderLayout,
		&PolyHedraUIManager.ShaderLayoutFullDefault,
		&PolyHedraUIManager.ShaderLayoutWireDefault,
	});
	MultiformLayout.Find(layouts);
}



void Light3DContext::ChangeMedia()
{
	std::cout << "ChangeMedia 0\n";

	PolyHedraManager.ChangeMedia(MediaDirectory);
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/PolyHedra/Default.vert")),
			Shader::Code(MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag")),
		});
		LightShader.Change(code);
		LightShader.UniformLayout = &LightShaderLayout;
		LightShaderLayout.Shader = &LightShader;

		PolyHedraManager.ShaderFullOther = &LightShader;
	}

	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	PolyHedraUIManager.ChangeMedia(MediaDirectory);

	std::cout << "ChangeMedia 1\n";
}
void Light3DContext::GraphicsCreate()
{
	PolyHedraManager.GraphicsCreate();
	LightShader.Create();
	UIManager.GraphicsCreate();
	PolyHedraUIManager.GraphicsCreate();

	MultiformLayout.Depth.ChangeData(View.Depth);
	MultiformLayout.FOV.ChangeData(View.FOV);

	LightShaderLayout.Create();

	LightShaderLayout.BindBlock();

	LightShaderLayout.Info();
}
void Light3DContext::GraphicsDelete()
{
	PolyHedraManager.GraphicsDelete();
	LightShader.Delete();
	UIManager.GraphicsDelete();
	PolyHedraUIManager.GraphicsDelete();

	LightShaderLayout.Delete();
}



static LightSpot LightSpotLook(LightBase base, Line3D line, Range range)
{
	LightSpot light;
	light.Base = base;
	light.Pos = line.Origin;
	light.Dir = line.Differance().normalize();
	light.Range = range;
	return light;
}

void Light3DContext::LightsMake()
{
	Light_Ambient = LightBase(0.1f, ColorF4(1.0f, 1.0f, 1.0f));
	Light_Solar = LightSolar(0.8f, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(+1, -3, +2).normalize());
	Light_Spot_Array[0] = LightSpotLook(LightBase(1.0f, ColorF4(1.0f, 0.0f, 0.0f)), Line3D(VectorF3(+22, 30, -22), VectorF3(0, 0, 0)), Range(0.8, 0.95));
	Light_Spot_Array[1] = LightSpotLook(LightBase(1.0f, ColorF4(0.0f, 1.0f, 0.0f)), Line3D(VectorF3(  0, 30, +22), VectorF3(0, 0, 0)), Range(0.8, 0.95));
	Light_Spot_Array[2] = LightSpotLook(LightBase(1.0f, ColorF4(0.0f, 0.0f, 1.0f)), Line3D(VectorF3(-22, 30, -22), VectorF3(0, 0, 0)), Range(0.8, 0.95));
	Light_Spot_Array[3] = LightSpotLook(LightBase(1.0f, ColorF4(1.0f, 1.0f, 1.0f)), Line3D(VectorF3(  0, 30, -22), VectorF3(0, 0, 0)), Range(0.8, 0.95));
	Light_Spot_Count = 3;

	LightAmbientObject.Light = &Light_Ambient;
	LightSolarObject.Light = &Light_Solar;
	LightSpotObjects[0].Light = &Light_Spot_Array[0];
	LightSpotObjects[1].Light = &Light_Spot_Array[1];
	LightSpotObjects[2].Light = &Light_Spot_Array[2];
	LightSpotObjects[3].Light = &Light_Spot_Array[3];
	
	Objects.Insert(&LightAmbientObject);
	Objects.Insert(&LightSolarObject);
	Objects.Insert(&LightSpotObjects[0]);
	Objects.Insert(&LightSpotObjects[1]);
	Objects.Insert(&LightSpotObjects[2]);
	Objects.Insert(&LightSpotObjects[3]);
}

static PolyHedra * Cube = nullptr;

void Light3DContext::RandomCubes()
{
	Cube = PolyHedra::Generate::HexaHedron();
	CenterCube.Data.PalletManager = PolyHedraManager.MakePallet(Cube);
	Objects.Insert(&CenterCube);

	/*int Range_Size1 = 0x1FF;
	int Range_SizeH = 0x0FF;
	int j_len = 16;
	int i_len = 16;
	for (int j = 0; j < j_len; j++)
	{
		VectorF3 center(
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH
		);
		EulerAngle3D rot = EulerAngle3D::Radians(
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH,
			(std::rand() & Range_Size1) - Range_SizeH
		);

		for (int i = 0; i < i_len; i++)
		{
			Objects.Insert(new SceneObject_PolyHedraObject(Cube, Trans3D(
				center + VectorF3(
					(std::rand() & Range_Size1) - Range_SizeH,
					(std::rand() & Range_Size1) - Range_SizeH,
					(std::rand() & Range_Size1) - Range_SizeH
				), rot
			)));
		}
	}*/
}

void Light3DContext::FancyLights()
{
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedraPalletManager * stage_light =			PolyHedraManager.MakePallet(PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt")));
	PolyHedraPalletManager * stage_light_holder =	PolyHedraManager.MakePallet(PolyHedra::Load(dir.File("Stage_Light_Holder.polyhedra.ymt")));

	LightAmbientObject.Data.PalletManager = PolyHedraManager.MakePallet(Cube);
	LightAmbientObject.Data.Trans.Position.Y = 40.0f;

	LightSolarObject.Data.PalletManager = PolyHedraManager.MakePallet(Cube);
	LightSolarObject.Data.Trans.Position.Y = 45.0f;

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		const LightSpot * light = LightSpotObjects[i].Light;

		VectorF3 pos = light -> Pos;
		EulerAngle3D rot = EulerAngle3D::PointToZ(light -> Dir);

		LightSpotObjects[i].Data0.PalletManager = stage_light;
		LightSpotObjects[i].Data0.Trans.Position = pos;
		LightSpotObjects[i].Data0.Trans.Rotation = rot;

		rot.Z0 = Angle();
		rot.X1 = Angle();
		LightSpotObjects[i].Data1.PalletManager = stage_light_holder;
		LightSpotObjects[i].Data1.Trans.Position = pos;
		LightSpotObjects[i].Data1.Trans.Rotation = rot;
	}
}



#include "SceneParsingData.hpp"
#include "FileParsing/Text/TextCommandStream.hpp"
void Light3DContext::Fancify()
{
	SceneParsingData data(MediaDirectory.File("YMT/Light/Light.scene"), PolyHedraManager, Objects);
	TextCommandStream stream(data.File.LoadText());
	TextCommand cmd;
	while (stream.Continue(cmd))
	{
		data.Parse(cmd);
	}
}



static PolyHedra * MoveAxisXIndicator = nullptr;
static PolyHedra * MoveAxisYIndicator = nullptr;
static PolyHedra * MoveAxisZIndicator = nullptr;
static PolyHedra * SpinRingXIndicator = nullptr;
static PolyHedra * SpinRingYIndicator = nullptr;
static PolyHedra * SpinRingZIndicator = nullptr;

void Light3DContext::Make()
{
	std::cout << "Make 0\n";
	
	window.DefaultColor = ColorF4(0.25f, 0.0f, 0.0f);
	View.Depth.Color = window.DefaultColor;
	//View.Trans = Trans3D(VectorF3(0, 10, -65), EulerAngle3D());
	View.Trans = Trans3D(VectorF3(0, 0, -5), EulerAngle3D());

	LightsMake();

	RandomCubes();
	Fancify();
	FancyLights();

	UIManager.WindowControl.ChildInsert(UISceneObject);
	UISceneObject.Hide();

	MoveAxisXIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/MoveAxis/AxisX.polyhedra"));
	MoveAxisYIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/MoveAxis/AxisY.polyhedra"));
	MoveAxisZIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/MoveAxis/AxisZ.polyhedra"));
	SpinRingXIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/SpinRing/RingX.polyhedra"));
	SpinRingYIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/SpinRing/RingY.polyhedra"));
	SpinRingZIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/SpinRing/RingZ.polyhedra"));

	UserTrans3DChange.MoveAxisXIndicator.Create(MoveAxisXIndicator);
	UserTrans3DChange.MoveAxisYIndicator.Create(MoveAxisYIndicator);
	UserTrans3DChange.MoveAxisZIndicator.Create(MoveAxisZIndicator);
	UserTrans3DChange.SpinRingXIndicator.Create(SpinRingXIndicator);
	UserTrans3DChange.SpinRingYIndicator.Create(SpinRingYIndicator);
	UserTrans3DChange.SpinRingZIndicator.Create(SpinRingZIndicator);

	UserTrans3DChange.MoveAxisXIndicator.HideFull();
	UserTrans3DChange.MoveAxisYIndicator.HideFull();
	UserTrans3DChange.MoveAxisZIndicator.HideFull();
	UserTrans3DChange.SpinRingXIndicator.HideFull();
	UserTrans3DChange.SpinRingYIndicator.HideFull();
	UserTrans3DChange.SpinRingZIndicator.HideFull();

	std::cout << "Make 1\n";
}

void Light3DContext::Init()
{
	ChangeMedia();

	std::cout << "Init 0\n";

	GraphicsCreate();

	std::cout << "Init 1\n";

	Make();
}
void Light3DContext::Free()
{
	std::cout << "Free 0\n";

	GraphicsDelete();

	std::cout << "Free 1\n";
}



void Light3DContext::User(FrameTime frame_time)
{
	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();

		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Position *= 10; }
		trans.Position *= 2;
		trans.Rotation *= View.FOV.ToRadians() * 0.05f;

		trans.Position *= frame_time.Delta;
		trans.Rotation *= frame_time.Delta;

		View.ChangeAbsoluteFlatY(trans);

		//View.Trans.Position += View.Trans.Rotation.forward(trans.Position);
		//View.Trans.Rotation = View.Trans.Rotation.reverse(trans.Rotation);
	}

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
}
void Light3DContext::Draw()
{
	MultiformLayout.View.ChangeData(Matrix4x4::TransformReverse(View.Trans));

	LightShader.Bind();
	//LightShaderLayout.Light_Ambient.Put(Light_Ambient);
	//LightShaderLayout.Light_Solar.Put(Light_Solar);
	/*for (unsigned int i = 0; i < Light_Spot_Count; i++)
	{
		LightShaderLayout.Light_Spot_Array[i].Put(Light_Spot_Array[i]);
	}*/
	//LightShaderLayout.Light_Spot_Count.Put(Light_Spot_Count);

	LightShaderLayout::LightData data;
	data.Ambient = Light_Ambient;
	data.Solar = Light_Solar;
	for (unsigned int i = 0; i < Light_Spot_Count; i++)
	{
		data.Spot[i] = Light_Spot_Array[i];
	}
	data.SpotCount = Light_Spot_Count;
	LightShaderLayout.Put(data);



	PolyHedraManager.MakeInstances();
	PolyHedraUIManager.MakeInstances();

	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Objects[i] -> DisplayObject();
	}



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	LightShaderLayout.LightBuffer.Bind();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();

	GL::Clear(GL::ClearMask::DepthBufferBit);

	PolyHedraUIManager.DrawFull();
	PolyHedraUIManager.DrawWire();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	UIManager.Draw();
}



#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"

static SceneObject * SceneObject_Selected = nullptr;

void Light3DContext::ViewObjectFunc()
{
	// just dont cast ray if hovering ?

	Ray3D_Hit_Type<unsigned int> hit;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Ray3D_Hit hit_temp = Objects[i] -> Hit(ViewRay);
		hit.Consider(hit_temp, i);
	}

	if (UIManager.Hovering == &UIManager.WindowControl && hit.Is())
	{
		SceneObject * obj = Objects[hit.Index];
		if (obj != nullptr)
		{
			obj -> ShowWire();
		}
	}

	if (UIManager.Hovering == &UIManager.WindowControl && window.MouseManager[MouseButtons::MouseL] == State::Press)
	{
		if (hit.Is())
		{
			SceneObject_Selected = Objects[hit.Index];
			UISceneObject.Show();
			UserTrans3DChange.MoveAxisXIndicator.ShowFull();
			UserTrans3DChange.MoveAxisYIndicator.ShowFull();
			UserTrans3DChange.MoveAxisZIndicator.ShowFull();
			UserTrans3DChange.SpinRingXIndicator.ShowFull();
			UserTrans3DChange.SpinRingYIndicator.ShowFull();
			UserTrans3DChange.SpinRingZIndicator.ShowFull();
		}
		else
		{
			SceneObject_Selected = nullptr;
			UISceneObject.Hide();
			UserTrans3DChange.MoveAxisXIndicator.HideFull();
			UserTrans3DChange.MoveAxisYIndicator.HideFull();
			UserTrans3DChange.MoveAxisZIndicator.HideFull();
			UserTrans3DChange.SpinRingXIndicator.HideFull();
			UserTrans3DChange.SpinRingYIndicator.HideFull();
			UserTrans3DChange.SpinRingZIndicator.HideFull();
		}
		UISceneObject.Change(SceneObject_Selected);

		if (SceneObject_Selected != nullptr)
		{
			UserTrans3DChange.Trans = SceneObject_Selected -> GetTrans();
		}
	}
}
void Light3DContext::ViewChangeTransFunc()
{
	if (UserTrans3DChange.TypeIsNone())
	{
		UserTrans3DChange.FindIndicator(ViewRay);
	}
	UserTrans3DChange.UpdateIndicator(View, window.Size);

	if (window.MouseManager[MouseButtons::MouseL] == State::Release ||
		window.MouseManager[MouseButtons::MouseR] == State::Release)
	{
		UserTrans3DChange.TypeUseNone();
		if (SceneObject_Selected != nullptr)
		{
			UserTrans3DChange.Trans = SceneObject_Selected -> GetTrans();
		}
	}
	else if (window.MouseManager[MouseButtons::MouseL] == State::Press)
	{ UserTrans3DChange.TypeUseL(); }
	else if (window.MouseManager[MouseButtons::MouseR] == State::Press)
	{ UserTrans3DChange.TypeUseR(); }

	Trans3D trans = UserTrans3DChange.NewTrans(ViewRay);
	trans.Position = trans.Position.round(0.1f);
	trans.Rotation = trans.Rotation.round(Angle::Degrees(15));

	UserTrans3DChange.Trans = trans;
	if (!UserTrans3DChange.TypeIsNone() && SceneObject_Selected != nullptr)
	{
		SceneObject_Selected -> SetTrans(trans);
	}
}
void Light3DContext::ViewFunc()
{
	VectorF2 pos;
	if (!window.MouseManager.CursorModeIsLocked())
	{
		pos = window.Size.Convert(window.MouseManager.CursorPosition());
	}
	ViewRay = Ray3D(View.Trans.Position, View.Trans.Rotation.forward(VectorF3(pos.X, pos.Y, 1)));

	ViewChangeTransFunc();
	if (UserTrans3DChange.TypeIsNone())
	{
		ViewObjectFunc();
	}
	if (SceneObject_Selected != nullptr)
	{
		SceneObject_Selected -> ShowWire();
		UISceneObject.Update();
	}
}



void Light3DContext::Frame(FrameTime frame_time)
{
	static float frameSum = 0;
	frameSum += frame_time.Delta;

	User(frame_time);

	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Objects[i] -> Update();
	}

	CenterCube.Data.Trans.Position = VectorF3(0, 10, 0);
	CenterCube.Data.Trans.Rotation.Y2 += Angle::Radians(0.01f);

	ViewFunc();

	Draw();
}

void Light3DContext::Resize(DisplaySize display_size)
{
	MultiformLayout.DisplaySize.ChangeData(display_size);
	UIManager.Resize(display_size);
}



void Light3DContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void Light3DContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void Light3DContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void Light3DContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void Light3DContext::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void Light3DContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
