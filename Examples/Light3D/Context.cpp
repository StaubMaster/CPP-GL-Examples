#include "Context.hpp"
#include "General/UnitToString.hpp"

#include "PolyHedra/Generate.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "PolyHedraUI/PalletManager.hpp"
#include "PolyHedraUI/ObjectData.hpp"

#include "ValueType/Intersect.hpp"



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





UIPolyHedraPalletItem::UIPolyHedraPalletItem(UIPolyHedraPalletList & list, PolyHedraPalletManager * obj)
	: UI::Control::Button()
	, List(list)
	, Object(obj)
{
	AnchorMargin = BoxF2(VectorF2(0.0f), VectorF2(0.0f));
	Anchor.X.AnchorBoth(0, 0);
	if (obj != nullptr)
	{
		SetText(obj -> Pallet -> File.Name());
	}
	ClickFunc.Assign(this, UIPolyHedraPalletItem::Func);
}
void UIPolyHedraPalletItem::Func(ClickArgs args)
{
	List.Func(args, Object);
}

UIPolyHedraPalletList::UIPolyHedraPalletList()
	: UI::Control::Form()
{
	AnchorPadding = BoxF2(VectorF2(0.0f), VectorF2(0.0f));
}
void UIPolyHedraPalletList::Clear()
{
	Children.Clear();
	for (unsigned int i = 0; i < List.Count(); i++)
	{
		delete List[i];
	}
	List.Clear();
	Pallet = nullptr;
}
void UIPolyHedraPalletList::Change(PolyHedraManager & manager)
{
	Clear();

	for (unsigned int i = 0; i < manager.InstanceManagers.Count(); i++)
	{
		PolyHedraPalletManager * pallet_manager = manager.InstanceManagers[i];
		List.Insert(new UIPolyHedraPalletItem(*this, pallet_manager));
		ChildInsert(List[i]);
	}

	Show();
	AnchorFitChildrenY(); // this dosent work poperly if hidden
	// generic Fitting Enum
	// Flag to request Fitting
}
void UIPolyHedraPalletList::Func(ClickArgs args, PolyHedraPalletManager * obj)
{
	if (args.Action == Action::Press)
	{
		Pallet = obj;
		Hide();
	}
}



bool Light3DContext::IsHoveringUI() const
{
	return (UIManager.Hovering != &UIManager.WindowControl);
}

SceneObject * Light3DContext::FindObject(const RayF3 & ray) const
{
	Ray3D_Hit_Type<unsigned int> hit;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Ray3D_Hit hit_temp = Objects[i] -> Hit(ray);
		hit.Consider(hit_temp, i);
	}
	if (hit.Is())
	{
		return Objects[hit.Index];
	}
	return nullptr;
}
unsigned int Light3DContext::FindObjectIndex(const SceneObject * obj) const
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == obj)
		{
			return i;
		}
	}
	return 0xFFFFFFFF;
}

void Light3DContext::Objects_Change()
{
	Object_Hovering = nullptr;

	if (IsHoveringUI()) { return; }
	if (!UserTrans3DChange.HoveringIsNone()) { return; }
	if (!UserTrans3DChange.SelectedIsNone()) { return; }

	//Object_Hovering = FindObject(ViewRay);

	if (window.MouseManager[MouseButtons::MouseL].IsPress())
	{
		if (Object_Hovering != nullptr)
		{
			UserTrans3DChange.ShowIndicator();
		}
		else
		{
			UserTrans3DChange.HideIndicator();
		}
		Object_Selected = Object_Hovering;
		UISceneObject.Change(Object_Selected);
	}
}
void Light3DContext::Objects_Update()
{
	if (Object_Hovering != nullptr)
	{
		//Object_Hovering -> ShowWire();
	}

	if (Object_Selected != nullptr)
	{
		Object_Selected -> ShowWire();
		UISceneObject.Update();
	}
}



void Light3DContext::SceneClear()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		delete Objects[i];
	}
	Objects.Clear();
}

static PolyHedra * Cube = nullptr;
static PolyHedra * Sphere = nullptr;
static PolyHedra * Torus = nullptr;

void Light3DContext::SceneInitCubes()
{
	Cube = PolyHedraGenerate::RegularHexaHedron();
	CenterCube.Data.PalletManager = PolyHedraManager.MakePallet(Cube);
	Objects.Insert(&CenterCube);

	/* Random
	int Range_Size1 = 0x1FF;
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

	//Sphere = PolyHedraGenerate::SphereY(1, 4, 1.0f); // TetraHedron
	//Sphere = PolyHedraGenerate::SphereY(2, 5, 1.0f); // IcosaHedron
	//Sphere = PolyHedraGenerate::SphereY(6, 12, 4.0f);
	Sphere = PolyHedra::Load(MediaDirectory.File("YMT/Light/Chair.polyhedra"));

	//Torus = PolyHedraGenerate::TorusY(8, 2.0f, 16, 4.0f);
	Torus = PolyHedraGenerate::TorusY(32, 3.0f, 64, 8.0f);

	Sphere -> UseCornerNormals = true;
	Torus -> UseCornerNormals = true;
	PolyHedraPalletManager * sphere_manager = PolyHedraManager.MakePallet(Sphere);
	PolyHedraPalletManager * torus_manager = PolyHedraManager.MakePallet(Torus);

	VectorF3 pos(0, 64, 0);
	Objects.Insert(new SceneObject_PolyHedraObject(sphere_manager, Trans3D(pos)));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(0, 8, 0), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(8, 0, 0), EulerAngle3D::Degrees(90, 0, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(0, 0, 8), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(0, 8, 0), EulerAngle3D::Degrees(0, 0, 90))));
	//Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(8, 0, 0), EulerAngle3D::Degrees(90, 0, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(0, 0, 8), EulerAngle3D::Degrees(0, 90, 0))));
}
void Light3DContext::SceneInitLights()
{
	// seperate into PolyHedra and Light Objects
	// put Light Objects in Scene File

	// Init Lights
	Light_Ambient = LightBase(0.1f, ColorF4(1.0f, 1.0f, 1.0f));
	Light_Solar = LightDirection(0.8f, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(+1, -3, +2).normalize());
	Light_Spot_Array[0] = LightSpot(LightBase(1.0f, ColorF4(1.0f, 0.0f, 0.0f)), LineF3(VectorF3(+22, 30, -22), VectorF3(0, 0, 0)), RangeF(0.8, 0.95));
	Light_Spot_Array[1] = LightSpot(LightBase(1.0f, ColorF4(0.0f, 1.0f, 0.0f)), LineF3(VectorF3(  0, 30, +22), VectorF3(0, 0, 0)), RangeF(0.8, 0.95));
	Light_Spot_Array[2] = LightSpot(LightBase(1.0f, ColorF4(0.0f, 0.0f, 1.0f)), LineF3(VectorF3(-22, 30, -22), VectorF3(0, 0, 0)), RangeF(0.8, 0.95));
	Light_Spot_Array[3] = LightSpot(LightBase(1.0f, ColorF4(1.0f, 1.0f, 1.0f)), LineF3(VectorF3(  0, 30, -22), VectorF3(0, 0, 0)), RangeF(0.8, 0.95));
	Light_Spot_Count = 3;

	Light_Spot_Array[0] = LightSpot(
		LightBase(1.0f, ColorF4(0.0f, 1.0f, 0.0f)),
		LineF3(
			//VectorF3(+32, 96, -32),
			VectorF3(+16, 80, -16),
			//VectorF3(+12, 76, -12),
			VectorF3(0, 64, 0)
		),
		RangeF(0.80f, 0.95f)
		//RangeF(0.80f, 0.80f)
		//RangeF(0.95f, 0.95f)
	);
	Light_Spot_Count = 1;

	// Assign Lights to Objects
	LightAmbientObject.Light = &Light_Ambient;
	LightSolarObject.Light = &Light_Solar;
	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		LightSpotObjects[i].Light = &Light_Spot_Array[i];
	}

	// Assign Object PolyHedras
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedraPalletManager * stage_light =			PolyHedraManager.MakePallet(PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt")));

	/* Ambient
		takes the color of the light
		difficult to find when same color as background ?
		Sphere / Cube
	*/
	/* Solar
		takes the color of the light
		difficult to find when same color as background ?
		Sphere with Cone
		Cone points toward direction
	*/
	/* Spot / Cone
		multiple thin Lines
		Lines start at Position
		Center Line Points in direction
		Ring Lines show Cone
	*/
	/* all these would be nice if they had both fixed Color and optional Color
	*/

	LightAmbientObject.Data.PalletManager = PolyHedraManager.MakePallet(Cube);
	LightSolarObject.Data.PalletManager = PolyHedraManager.MakePallet(Cube);
	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		LightSpotObjects[i].Data.PalletManager = stage_light;
	}

	// Assign Object Trans
	LightAmbientObject.Data.Trans.Position.Y = 40.0f;
	LightSolarObject.Data.Trans.Position.Y = 45.0f;

	// Put Light Objects into Objects
	Objects.Insert(&LightAmbientObject);
	Objects.Insert(&LightSolarObject);
	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Objects.Insert(&LightSpotObjects[i]);
	}
}

#include "SceneParsingData.hpp"
#include "FileParsing/Text/TextCommandStream.hpp"
void Light3DContext::SceneLoad(FileInfo file)
{
	SceneParsingData data(file, PolyHedraManager, Objects);
	TextCommandStream stream(file.LoadText());
	TextCommand cmd;
	while (stream.Continue(cmd))
	{
		data.Parse(cmd);
	}
}
void Light3DContext::SceneSave(FileInfo file)
{
	std::stringstream ss;

	file.SaveText(ss.str());
}



void Light3DContext::UserChange_Change()
{
	UserTrans3DChange.HoveringType = UserTrans3DChange::EIndicatorType::None;
	UserTrans3DChange.HoveringOffset = Trans3D();
	UserTrans3DChange.UpdateIndicatorColor();

	if (IsHoveringUI()) { return; }

	if (Object_Selected != nullptr && UserTrans3DChange.SelectedIsNone())
	{
		UserTrans3DChange.FindIndicator(ViewRay);
	}

	if (window[MouseButtons::MouseL].IsRelease() ||
		window[MouseButtons::MouseR].IsRelease())
	{
		UserTrans3DChange.UseNone();
		if (Object_Selected != nullptr)
		{
			UserTrans3DChange.Trans = Object_Selected -> GetTrans();
			UserTrans3DChange.UpdateIndicatorTrans(UserTrans3DChange.Trans);
		}
	}
	else if (window[MouseButtons::MouseL].IsPress())
	{
		UserTrans3DChange.UseL();
	}
	else if (window[MouseButtons::MouseR].IsPress())
	{
		UserTrans3DChange.UseR();
	}
}
void Light3DContext::UserChange_Update()
{
	if (!UserTrans3DChange.SelectedIsNone())
	{
		Trans3D trans = UserTrans3DChange.NewTrans(ViewRay);
		trans.Position = trans.Position.round(0.1f);
		trans.Rotation = trans.Rotation.round(Angle::Degrees(15));

		if (Object_Selected != nullptr)
		{
			Object_Selected -> SetTrans(trans);
		}

		UserTrans3DChange.UpdateIndicator(trans, View, window.Size);
	}
	else
	{
		UserTrans3DChange.UpdateIndicator(UserTrans3DChange.Trans, View, window.Size);
	}

	if (Object_Selected != nullptr)
	{
		UserTrans3DChange.Trans = Object_Selected -> GetTrans();
		UserTrans3DChange.UpdateIndicator(UserTrans3DChange.Trans, View, window.Size);
	}
}



void Light3DContext::PolyHedraPalletChangeFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		DoPolyHedraPalletChange = true;
		UIPolyHedraPalletList.Change(PolyHedraManager);
	}
}
void Light3DContext::PolyHedraPalletUpdate()
{
	if (DoPolyHedraPalletChange)
	{
		if (!UIPolyHedraPalletList.IsVisible())
		{
			SceneObject_PolyHedraObject * obj = dynamic_cast<SceneObject_PolyHedraObject*>(Object_Selected);
			if (UIPolyHedraPalletList.Pallet != nullptr && obj != nullptr)
			{
				obj -> Data.PalletManager = UIPolyHedraPalletList.Pallet;
			}
			DoPolyHedraPalletChange = false;
		}
	}
}



Light3DContext::~Light3DContext()
{ }
Light3DContext::Light3DContext()
	: ContextBase()
	, PolyHedraManager()
	, UIManager()
	, UISceneObject()
	, PolyHedraUIManager()
	, Objects()
	, Object_Selected(nullptr)
	, Object_Hovering(nullptr)
	, UIPolyHedraPalletList()
	, DoPolyHedraPalletChange(false)
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
	//View.Trans = Trans3D(VectorF3(0, 0, -5), EulerAngle3D());
	//View.Trans = Trans3D(VectorF3(0, 64, -16), EulerAngle3D());
	View.Trans = Trans3D(VectorF3(0, 64, 0), EulerAngle3D());

	SceneClear();
	SceneInitCubes();
	SceneLoad(MediaDirectory.File("YMT/Light/Light.scene"));
	SceneInitLights();

	UIManager.WindowControl.ChildInsert(UISceneObject);
	UISceneObject.PolyHedraObject.PalletChange.ClickFunc.Assign(this, Light3DContext::PolyHedraPalletChangeFunc);
	UISceneObject.Hide();

	UIManager.WindowControl.ChildInsert(UIPolyHedraPalletList);
	UIPolyHedraPalletList.Hide();
	
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
	}

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());

	if (window[Keys::Enter] == State::Press)
	{
		if (UISceneObject.IsVisible())
		{
			UISceneObject.Hide();
		}
		else
		{
			UISceneObject.Show();
		}
	}

	if (window[Keys::Delete] == State::Press)
	{
		if (Object_Selected != nullptr)
		{
			unsigned int idx = FindObjectIndex(Object_Selected);
			if (idx != 0xFFFFFFFF)
			{
				Objects.RemoveAt(idx);
				UserTrans3DChange.UseNone();
				UserTrans3DChange.HideIndicator();
				Object_Selected = nullptr;
			}
		}
	}

	if (window[Keys::Insert] == State::Press)
	{
		PolyHedraPalletManager * pallet = PolyHedraManager.FindPallet(Cube);
		Objects.Insert(new SceneObject_PolyHedraObject(pallet, Trans3D()));
	}

	if (window[Keys::Menu] == State::Press)
	{
		//UIPolyHedraPalletList.Change(&PolyHedraManager);
	}
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

/* lots of repeating

put functions in UserChange struct

no change
	to use then Object is selected
	or when changing is done
	sets Trans, moves Iniciators to Trans
	FrameUpdate
		scales Indicators

start change
	FrameUpdate
		change Indicators to calculated trans
		scales Indicators
*/

void Light3DContext::ViewFunc()
{
	VectorF2 pos;
	if (!window.MouseManager.CursorModeIsLocked())
	{
		pos = window.Size.Convert(window.MouseManager.CursorPosition());
	}
	ViewRay = RayF3(View.Trans.Position, View.Trans.Rotation.forward(VectorF3(pos.X, pos.Y, 1)));



	UserChange_Change();
	Objects_Change();

	UserChange_Update();	
	Objects_Update();
}



// FPS sucks because Ray Hit is slow
// check Bounding Box first
void Light3DContext::Frame(FrameTime frame_time)
{
	static float frameSum = 0;
	frameSum += frame_time.Delta;

	User(frame_time);

	PolyHedraPalletUpdate();
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
