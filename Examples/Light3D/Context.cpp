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





bool Light3DContext::IsHoveringUI() const
{
	return (UIManager.Hovering != &UIManager.WindowControl);
}



LightBase * Light3DContext::TakeLightAmbient()
{
	if (Light_Ambient_Count < Light_Ambient_Limit)
	{
		LightBase * light = &Light_Ambient;
		Light_Ambient_Count++;
		return light;
	}
	return nullptr;
}
LightDirection * Light3DContext::TakeLightSolar()
{
	if (Light_Solar_Count < Light_Solar_Limit)
	{
		LightDirection * light = &Light_Solar;
		Light_Solar_Count++;
		return light;
	}
	return nullptr;
}
LightSpot * Light3DContext::TakeLightSpot()
{
	if (Light_Spot_Count < Light_Spot_Limit)
	{
		LightSpot * light = &Light_Spot_Array[Light_Spot_Count];
		Light_Spot_Count++;
		return light;
	}
	return nullptr;
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
	if (!UserTrans3DChange.IsIdle()) { return; }

	Object_Hovering = FindObject(ViewRay);

	if (window.MouseManager[MouseButtons::MouseL].IsPress())
	{
		Object_Selected = Object_Hovering;
		if (Object_Selected != nullptr)
		{
			UserTrans3DChange.IndicatorsShow();
			UserTrans3DChange.SetTrans(Object_Selected -> GetTrans());
		}
		else
		{
			UserTrans3DChange.SelectedMakeNone();
			UserTrans3DChange.IndicatorsHide();
		}
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
	Light_Ambient_Count = 0;
	Light_Solar_Count = 0;
	Light_Spot_Count = 0;
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

	//Sphere -> UseCornerNormals = true;
	Torus -> UseCornerNormals = true;
	PolyHedraPalletManager * sphere_manager = PolyHedraManager.MakePallet(Sphere);
	PolyHedraPalletManager * torus_manager = PolyHedraManager.MakePallet(Torus);

	VectorF3 pos(0, 64, 0);
	Objects.Insert(new SceneObject_PolyHedraObject(sphere_manager, Trans3D(pos)));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(0, 8, 0), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(8, 0, 0), EulerAngle3D::Degrees(90, 0, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(0, 0, 8), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(0, 8, 0), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(8, 0, 0), EulerAngle3D::Degrees(90, 0, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(0, 0, 8), EulerAngle3D::Degrees(0, 90, 0))));
}
void Light3DContext::SceneInitLights()
{
	/*Light_Spot_Array[0] = LightSpot(
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
	Light_Spot_Count = 1;*/

	// Assign Object PolyHedras
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedraPalletManager * stage_light = PolyHedraManager.MakePallet(PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt")));
	//PolyHedraPalletManager * Cube_manager = PolyHedraManager.MakePallet(Cube);
	PolyHedraUIPalletManager * Cube_UI_manager = PolyHedraUIManager.PlacePallet(Cube);

	/* Light Meta Indicators
		LightBuld: LightPoint
	*/
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

	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		SceneObject * scene_obj = Objects[i];
		{
			SceneObject_LightAmbient * obj = dynamic_cast<SceneObject_LightAmbient*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.PalletManager = Cube_UI_manager;
			}
		}
		{
			SceneObject_LightDirection * obj = dynamic_cast<SceneObject_LightDirection*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.PalletManager = Cube_UI_manager;
			}
		}
		{
			SceneObject_LightSpot * obj = dynamic_cast<SceneObject_LightSpot*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.PalletManager = stage_light;
			}
		}
	}
}

#include "SceneParsingData.hpp"
#include "FileParsing/Text/TextCommandStream.hpp"
void Light3DContext::SceneLoad(FileInfo file)
{
	SceneParsingData data(file, *this);
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
	UserTrans3DChange.HoveringMakeNone();

	if (IsHoveringUI()) { return; }

	UserTrans3DChange.IndicatorsFind(ViewRay);

	// this is bad. check for release of the one being used ?
	if (window[MouseButtons::MouseL].IsRelease() ||
		window[MouseButtons::MouseR].IsRelease())
	{
		UserTrans3DChange.SelectedMakeNone();
	}
	else if (window[MouseButtons::MouseL].IsPress())
	{
		UserTrans3DChange.SelectedMakeL();
	}
	else if (window[MouseButtons::MouseR].IsPress())
	{
		UserTrans3DChange.SelectedMakeR();
	}
}
void Light3DContext::UserChange_Update()
{
	UserTrans3DChange.NewTrans(ViewRay);
	if (Object_Selected != nullptr)
	{
		if (!UserTrans3DChange.SelectedIsNone())
		{
			Object_Selected -> SetTrans(UserTrans3DChange.GetTrans());
		}
		else
		{
			UserTrans3DChange.SetTrans(Object_Selected -> GetTrans());
		}
	}
	UserTrans3DChange.IndicatorsUpdate(View, window.Size);
}



void Light3DContext::PolyHedraPalletChangeFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		DoPolyHedraPalletChange = true;
		{
			UIPolyHedraPalletList.Clear();
			for (unsigned int i = 0; i < PolyHedraManager.InstanceManagers.Count(); i++)
			{
				PolyHedraPalletManager * pallet_manager = PolyHedraManager.InstanceManagers[i];
				UI::Control::List::Item * item = new UI::Control::List::Item(UIPolyHedraPalletList, pallet_manager -> Pallet -> File.Path.ToString(), pallet_manager);
				UIPolyHedraPalletList.Items.Insert(item);
				UIPolyHedraPalletList.ChildInsert(item);
			}
			UIPolyHedraPalletList.Show();
			UIPolyHedraPalletList.AnchorFitChildrenY(); // this dosent work poperly if hidden
			// generic Fitting Enum
			// Flag to request Fitting
		}
		//UIPolyHedraPalletList.Change(PolyHedraManager);
	}
}
void Light3DContext::PolyHedraPalletUpdate()
{
	if (DoPolyHedraPalletChange)
	{
		if (!UIPolyHedraPalletList.IsVisible())
		{
			SceneObject_PolyHedraObject * obj = dynamic_cast<SceneObject_PolyHedraObject*>(Object_Selected);
			if (UIPolyHedraPalletList.Object != nullptr && obj != nullptr)
			{
				obj -> Data.PalletManager = (PolyHedraPalletManager*)UIPolyHedraPalletList.Object;
			}
			DoPolyHedraPalletChange = false;
		}
	}
}





#include "PolyHedra/Skin/Skin.hpp"
void Light3DContext::NewPolyHedraStuff::Init()
{
	Manager.ObjectManagers.Insert(&ObjectManager);

	PolyHedra * polyhedra = PolyHedraGenerate::SphereY(2, 5, 12.0f);
	polyhedra -> Skins[0] -> Images[0].Pixel(0) = ColorU4(255, 0, 255);

	NewPolyHedra_Pallet * pallet = Manager.FindMakePallet(polyhedra);

	NewPolyHedra_Type_Object<TestBasic3D::ObjectData> * object = new NewPolyHedra_Type_Object<TestBasic3D::ObjectData>();
	object -> Create(pallet);
}

void Light3DContext::NewPolyHedraStuff::ChangeMedia(const DirectoryInfo & dir)
{
	// Pallet
	{
		PalletBufferLayout.Position.Change(0);
		PalletBufferLayout.Normal.Change(1);
		PalletBufferLayout.Texture.Change(2);
	}
	for (unsigned int i = 0; i < Manager.Pallets.Count(); i++)
	{
		Manager.Pallets[i] -> Buffer.Init(PalletBufferLayout);
	}
	// ObjectManager
	{
		ObjectManager.Shader.Change({
			dir.File("Shaders/Basic3D/Full.vert"),
			dir.File("Shaders/Basic3D/Full.frag"),
		});
		ObjectManager.Shader.UniformLayout = &ObjectManagerShaderLayout;
		ObjectManagerShaderLayout.Shader = &ObjectManager.Shader;
	}
	{
		ObjectManagerBufferLayout.Trans.Change(3);
		ObjectManagerBufferLayout.Normal.Change(7);
	}
	for (unsigned int i = 0; i < ObjectManager.Managers.Count(); i++)
	{
		ObjectManager.Managers[i] -> Buffer.Init(ObjectManagerBufferLayout);
	}
}
void Light3DContext::NewPolyHedraStuff::GraphicsInit()
{
	VertexArray::BindNone();
	for (unsigned int i = 0; i < Manager.Pallets.Count(); i++)
	{
		Manager.Pallets[i] -> Object -> CalcNormals();
		Container::Array<PolyHedraFull::Main::Data> data = Manager.Pallets[i] -> Object -> ToMainData();

		Manager.Pallets[i] -> Buffer.DataFull(data.ToVoid());
		Manager.Pallets[i] -> Texture = Manager.Pallets[i] -> Object -> Skins[0] -> ToTexture();
	}
	for (unsigned int i = 0; i < Manager.ObjectManagers.Count(); i++)
	{
		for (unsigned int j = 0; j < Manager.ObjectManagers[i] -> Managers.Count(); j++)
		{
			Manager.ObjectManagers[i] -> Managers[j] -> BufferVertexArray.Bind();
			Manager.ObjectManagers[i] -> Managers[j] -> Buffer.Bind();
			Manager.ObjectManagers[i] -> Managers[j] -> Buffer.Update();
			Manager.ObjectManagers[i] -> Managers[j] -> Pallet -> Buffer.Bind();
			Manager.ObjectManagers[i] -> Managers[j] -> Pallet -> Buffer.Update();
		}
	}
	VertexArray::BindNone();
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
	, NewPolyHedraStuff()
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
		&NewPolyHedraStuff.ObjectManagerShaderLayout,
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

	NewPolyHedraStuff.ChangeMedia(MediaDirectory);

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

	NewPolyHedraStuff.Manager.GraphicsCreate();
}
void Light3DContext::GraphicsDelete()
{
	PolyHedraManager.GraphicsDelete();
	LightShader.Delete();
	UIManager.GraphicsDelete();
	PolyHedraUIManager.GraphicsDelete();

	LightShaderLayout.Delete();

	NewPolyHedraStuff.Manager.GraphicsDelete();
}



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
	UISceneObject.PolyHedraObject.PalletChange.ClickFunc.Assign(this, &Light3DContext::PolyHedraPalletChangeFunc);
	UISceneObject.Hide();

	UIManager.WindowControl.ChildInsert(UIPolyHedraPalletList);
	UIPolyHedraPalletList.Hide();

	UserTrans3DChange.IndicatorsInit(MediaDirectory.Child("YMT/Meta/"));
	UserTrans3DChange.IndicatorsHide();

	NewPolyHedraStuff.GraphicsInit();

	std::cout << "Make 1\n";
}

void Light3DContext::Init()
{
	NewPolyHedraStuff.Init();

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
				UserTrans3DChange.SelectedMakeNone();
				UserTrans3DChange.IndicatorsHide();
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

	NewPolyHedraStuff.Manager.InstancesClear();
	NewPolyHedraStuff.Manager.InstancesMake();
	NewPolyHedraStuff.Manager.Draw();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	UIManager.Draw();



	NewPolyHedraStuff.Manager.UpdatePalletObjectDatas();
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
