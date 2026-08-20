#include "Context.hpp"
#include "UnitToString.hpp"

#include "PolyHedra/Generate.hpp"

//
#include <iostream>
#include "OpenGL.hpp"
#include "Debug.hpp"

// ValueType
#include "ValueType/_Include.hpp"
#include "ValueType/Intersect.hpp"
#include "ValueType/_Show.hpp"
#include "ValueType/Ray/Hit/F3Type.hpp"

//
#include "Graphics/Shader/Code.hpp"

// SceneObject
#include "SceneObject/SceneObject.hpp"
#include "SceneObject/PolyHedraObject.hpp"
#include "SceneObject/LightAmbient.hpp"
#include "SceneObject/LightDirection.hpp"
#include "SceneObject/LightPoint.hpp"
#include "SceneObject/LightSpot.hpp"



GL::BlockBinding Light3DContext::BindingLight = 3;



void Light3DContext::PolyHedra_ChangeMedia()
{

	// NewPolyHedra
	{
		{
			PalletManager.BufferFullLayout.Position.Change(0);
			PalletManager.BufferFullLayout.Normal.Change(1);
			PalletManager.BufferFullLayout.Texture.Change(2);
			PalletManager.BufferFullLayout.Color.Change(15);
		}
		{
			PalletManager.BufferWireLayout.Pos.Change(0);
			PalletManager.BufferWireLayout.Col.Change(1);
		}
	}

	// Object Manager Basic
	{
		{
			ObjectManagerBasic.ShaderFull.Change({
				MediaDirectory.File("Shaders/PolyHedra/Default.vert"),
				MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag"),
			});
			/*{
				ObjectManagerBasic.ShaderFull.AssignLayout(ObjectManagerBasic_ShaderFullLayout);
			}*/
			{
				Uniform::Layout * layout = new Uniform::Layout(ObjectManagerBasic.ShaderFull);
				new Uniform::DisplaySize	(*layout, "DisplaySize");
				new Uniform::Matrix4x4		(*layout, "View");
				new Uniform::Depth			(*layout, "Depth");
				new Uniform::Angle			(*layout, "FOV");
				ObjectManagerBasic_ShaderFull_Lights = new Uniform::Buffer(*layout, "ILights");
				ObjectManagerBasic.ShaderFull.AssignLayout(layout);
			}
			{
				Attribute::Layout * layout = new Attribute::Layout(1, sizeof(NewPolyHedra::Basic3D::InstanceData));
				new Attribute::Matrix4x4	(*layout, 3);
				new Attribute::Matrix4x4	(*layout, 7);
				ObjectManagerBasic.BufferFullLayout = layout;
			}

			ObjectManagerBasic.ShaderWire.Change({
				MediaDirectory.File("Shaders/Basic3D/Wire.vert"),
				MediaDirectory.File("Shaders/Basic3D/Wire.frag"),
			});
			{
				Uniform::Layout * layout = new Uniform::Layout(ObjectManagerBasic.ShaderWire);
				new Uniform::DisplaySize	(*layout, "DisplaySize");
				new Uniform::Matrix4x4		(*layout, "View");
				new Uniform::Depth			(*layout, "Depth");
				new Uniform::Angle			(*layout, "FOV");
				ObjectManagerBasic.ShaderWire.AssignLayout(layout);
			}
			{
				Attribute::Layout * layout = new Attribute::Layout(1, sizeof(NewPolyHedra::Basic3D::InstanceData));
				new Attribute::Matrix4x4	(*layout, 3);
				new Attribute::Matrix4x4	(*layout, -1);
				ObjectManagerBasic.BufferWireLayout = layout;
			}
		}
		/*{
			ObjectManagerBasic.ShaderFull.Change({
				MediaDirectory.File("Shaders/PolyHedra/Default.vert"),
				MediaDirectory.File("Shaders/PolyHedra/UniformLight.frag"),
			});
			{
				ObjectManagerBasic.ShaderFull.AssignLayout(ObjectManagerBasic_ShaderFullLayout);
			}
			{
				ObjectManagerBasic.BufferFullLayout = AttributeLayoutParser::Parse(MediaDirectory.File("Layout/Basic3D/AttributeFull"));
			}

			ObjectManagerBasic.ShaderWire.Change({
				MediaDirectory.File("Shaders/Basic3D/Wire.vert"),
				MediaDirectory.File("Shaders/Basic3D/Wire.frag"),
			});
			{
				Uniform::Layout * layout = UniformLayoutParser::Parse(MediaDirectory.File("Layout/Basic3D/UniformWire"));
				ObjectManagerBasic.ShaderWire.AssignLayout(layout);
			}
			{
				ObjectManagerBasic.BufferWireLayout = AttributeLayoutParser::Parse(MediaDirectory.File("Layout/Basic3D/AttributeWire"));
			}
		}*/
	}

	// Object Manager TSC
	{
		{
			ObjectManagerTSC.ShaderFull.Change({
				MediaDirectory.File("Shaders/PolyHedra/UserInterface.vert"),
				MediaDirectory.File("Shaders/PolyHedra/TexturedNoLight.frag"),
			});
			ObjectManagerTSC.ShaderFull.AssignLayout(ObjectManagerTSC_ShaderFullLayout);
		}
		{
			// no Shader
			ObjectManagerTSC.ShaderWire.AssignLayout(ObjectManagerTSC_ShaderWireLayout);
		}
		{
			ObjectManagerTSC_BufferFullLayout.Trans.Change(3);
			ObjectManagerTSC_BufferFullLayout.Normal.Change(7);
			ObjectManagerTSC_BufferFullLayout.Scale.Change(11);
			ObjectManagerTSC_BufferFullLayout.Color.Change(12);
			ObjectManagerTSC.BufferFullLayout = &ObjectManagerTSC_BufferFullLayout;
		}
		{
			// no Shader
			ObjectManagerTSC.BufferWireLayout = &ObjectManagerTSC_BufferWireLayout;
		}
	}
}



bool Light3DContext::IsHoveringControl() const
{
	return (UIManager.Hovering != nullptr && UIManager.Hovering != &UIManager.WindowControl);
}

void Light3DContext::Objects_Change()
{
	Object_Hovering = nullptr;

	if (IsHoveringControl()) { return; }
	if (!UserChange.IsNone()) { return; }

	Object_Hovering = Collection.FindObject(ViewRay);

	if (window.MouseManager[MouseButtons::MouseL].IsPress())
	{
		Object_Selected = Object_Hovering;
		UserChange_ChangeObject(Object_Selected);
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
		UISceneObject.Syncronize();
	}
}



void Light3DContext::SceneClear()
{
	Object_Selected = nullptr;
	Object_Hovering = nullptr;
	Collection.Clear();
	LightManager.Clear();
//	UserTrans3DChange.HoveringMakeNone();
//	UserTrans3DChange.SelectedMakeNone();
}

static PolyHedra * Cube = nullptr;

void Light3DContext::SceneInitCubes()
{
	Cube = PolyHedraGenerate::RegularHexaHedron();
	CenterCube = new SceneObject_PolyHedraObject();
	CenterCube -> Data.Manager = ObjectManagerBasic.FindMakePalletObjectManager(Cube);
	Collection.Objects.Insert(CenterCube);

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
	//Sphere = PolyHedra::Load(MediaDirectory.File("YMT/Light/Chair.polyhedra"));

	//Torus = PolyHedraGenerate::TorusY(8, 2.0f, 16, 4.0f);
	//Torus = PolyHedraGenerate::TorusY(32, 3.0f, 64, 8.0f);

	//Sphere -> UseCornerNormals = true;
	//Torus -> UseCornerNormals = true;
	//NewPolyHedra_PalletObjectManager * sphere_manager = ObjectManagerBasic.FindMakePalletObjectManager(Sphere);
	//NewPolyHedra_PalletObjectManager * torus_manager = ObjectManagerBasic.FindMakePalletObjectManager(Torus);

	/*VectorF3 pos(0, 64, 0);
	Objects.Insert(new SceneObject_PolyHedraObject(sphere_manager, Trans3D(pos)));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(0, 8, 0), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(8, 0, 0), EulerAngle3D::Degrees(90, 0, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos - VectorF3(0, 0, 8), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(0, 8, 0), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(8, 0, 0), EulerAngle3D::Degrees(90, 0, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(torus_manager, Trans3D(pos + VectorF3(0, 0, 8), EulerAngle3D::Degrees(0, 90, 0))));*/
}

static NewPolyHedra::PalletObjectManager * Cube_UI_manager = nullptr;
static NewPolyHedra::PalletObjectManager * stage_light_manager = nullptr;
static NewPolyHedra::PalletObjectManager * light_bulb_manager = nullptr;
void Light3DContext::InitLights()
{
	DirectoryInfo dir(MediaDirectory.Child("YMT/Light"));
	if (Cube_UI_manager == nullptr) { Cube_UI_manager = ObjectManagerTSC.FindMakePalletObjectManager(Cube); }
	if (stage_light_manager == nullptr) { stage_light_manager = ObjectManagerBasic.FindMakePalletObjectManager(PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt"), PolyHedraFileCollection)); }
	if (light_bulb_manager == nullptr) { light_bulb_manager = ObjectManagerTSC.FindMakePalletObjectManager(PolyHedra::Load(dir.File("LightBulb.polyhedra"), PolyHedraFileCollection)); }
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

	// set Bodys of Light Objects
	for (unsigned int i = 0; i < Collection.Objects.Count(); i++)
	{
		SceneObject * scene_obj = Collection.Objects[i];
		{
			SceneObject_LightAmbient * obj = dynamic_cast<SceneObject_LightAmbient*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.Manager = light_bulb_manager;
			}
		}
		{
			SceneObject_LightDirection * obj = dynamic_cast<SceneObject_LightDirection*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.Manager = Cube_UI_manager;
			}
		}
		{
			SceneObject_LightPoint * obj = dynamic_cast<SceneObject_LightPoint*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.Manager = light_bulb_manager;
			}
		}
		{
			SceneObject_LightSpot * obj = dynamic_cast<SceneObject_LightSpot*>(scene_obj);
			if (obj != nullptr)
			{
				obj -> Data.Manager = stage_light_manager;
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
	TextCommandArgs cmd_args;
	while (stream.Continue(cmd_args))
	{
		data.Parse(cmd_args);
	}
}
void Light3DContext::SceneSave(FileInfo file)
{
	std::stringstream ss;

	file.SaveText(ss.str());
}

void Light3DContext::SceneReMake()
{
	// segfault when something is selected
	std::cout << "Scene ReMake ....\n";
	SceneClear();
	SceneInitCubes();
	//SceneLoad(MediaDirectory.File("YMT/Light/Light.scene"));
	SceneLoad(MediaDirectory.File("YMT/Tower/Tower.scene"));
	SceneInitLights();
	std::cout << "Scene ReMake done\n";
}



void Light3DContext::UserChange_ChangeObject(SceneObject * obj)
{
	if (obj != nullptr)
	{
		UserChange.IndicatorsShow();

		Trans3D trans = obj -> GetTrans();

		UserChange.VectorF3.Set(trans.Position);

		UserChange.EulerAngle3D.Set(trans.Rotation);
		UserChange.EulerAngle3D.Center = trans.Position;
	}
	else
	{
		UserChange.SelectedMakeNone();
		UserChange.IndicatorsHide();
	}
}

void Light3DContext::UserChange_HoverSelect()
{
	if (UserChange.SelectedIsNone())
	{
		if (IsHoveringControl())
		{
			UserChange.HoveringMakeNone();
		}
		else
		{
			unsigned int idx = UserChange.IndicatorsFind(ViewRay);
			if (window[MouseButtons::MouseL].IsPress())
			{
				UserChange.SelectedMakeL(idx);
			}
			if (window[MouseButtons::MouseR].IsPress())
			{
				UserChange.SelectedMakeR(idx);
			}
		}
	}
	else
	{
		if (IsHoveringControl())
		{
		}
		else
		{
			if (window[MouseButtons::MouseL].IsRelease())
			{
				UserChange.SelectedMakeNone();
			}
			if (window[MouseButtons::MouseR].IsRelease())
			{
				UserChange.SelectedMakeNone();
			}
		}
	}
}
void Light3DContext::UserChange_Update()
{
	// skip this if
	//  Object_Selected == nullptr
	//  UserChange.SelectedIsNone()

	UserChange.ChangeValue(ViewRay);

	Trans3D trans;

	trans.Position = UserChange.VectorF3.Get();
	trans.Rotation = UserChange.EulerAngle3D.Get();

	UserChange.VectorF3.Set(trans.Position);
	UserChange.EulerAngle3D.Set(trans.Rotation);
	UserChange.EulerAngle3D.Center = trans.Position;

	if (Object_Selected != nullptr)
	{
		Object_Selected -> SetTrans(trans);
	}

	// UserChange.EulerAngle3D Indicators Update Scale 1 frame later
	// noticable when Scale changes a lot between frames
	// like when moving something far away
	UserChange.IndicatorsUpdate(View, window.Size);
}



void Light3DContext::PolyHedraPalletChangeFunc(ClickArgs args)
{
	if (args.Action == Action::Press)
	{
		DoPolyHedraPalletChange = true;
		{
			UIPolyHedraPalletList.Show();
			UIPolyHedraPalletList.List.ItemsClear();
			UIPolyHedraPalletList.Object = nullptr;
			for (unsigned int i = 0; i < PalletManager.Pallets.Count(); i++)
			{
				NewPolyHedra::Pallet * pallet = PalletManager.Pallets[i];
				//UIPolyHedraPalletList.List.ItemNew(pallet -> Object -> File.Path.ToString(), pallet);
				UIPolyHedraPalletList.List.ItemNew(pallet -> Object -> File.Path.Name(), pallet);
			}
			UIPolyHedraPalletList.UpdateAutoAnchor();
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
				obj -> Data.Manager = ObjectManagerBasic.FindMakePalletObjectManager((NewPolyHedra::Pallet *)UIPolyHedraPalletList.Object);
			}
			DoPolyHedraPalletChange = false;
		}
	}
}



Light3DContext::~Light3DContext()
{ }
Light3DContext::Light3DContext()
	: ContextBase()
	, LightBuffer(GL::BufferDataUsage::StreamDraw)
{
	MediaDirectory = DirectoryInfo("../../media/"); // Set Media Directory with MakeFile Macro ?

	NewPolyHedra_Manager.PalletManager = &PalletManager;
	NewPolyHedra_Manager.ObjectManagers.Insert(&ObjectManagerBasic);
	NewPolyHedra_Manager.ObjectManagers.Insert(&ObjectManagerTSC);

	DisplayMode.Indicators = SceneObjectDisplayMode::EIndicators::Show;
	DisplayMode.Objects = SceneObjectDisplayMode::EObjects::Full;
}



#include "Layout/Parser/Attribute.hpp"
#include "Layout/Parser/Uniform.hpp"
void Light3DContext::ChangeMedia()
{
	std::cout << "ChangeMedia 0\n";

	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	PolyHedra_ChangeMedia();

	Container::Array<Uniform::Layout*> layouts({
		&UIManager.ControlManager.ShaderLayout,
		&UIManager.TextManager.ShaderLayout,
		&UIManager.GraphManager.ShaderLayout,
		//&ObjectManagerBasic_ShaderFullLayout,
		//&ObjectManagerBasic_ShaderWireLayout,
		ObjectManagerBasic.ShaderFull.Layout,
		ObjectManagerBasic.ShaderWire.Layout,
		&ObjectManagerTSC_ShaderFullLayout,
		&ObjectManagerTSC_ShaderWireLayout,
	});
	MultiformLayout.Find(layouts);

	std::cout << "ChangeMedia 1\n";
}
void Light3DContext::GraphicsCreate()
{
	UIManager.GraphicsCreate();

	MultiformLayout.Depth.ChangeData(View.Depth);
	MultiformLayout.FOV.ChangeData(View.FOV);

	LightBuffer.Create();

	NewPolyHedra_Manager.GraphicsCreate();
}
void Light3DContext::GraphicsDelete()
{
	UIManager.GraphicsDelete();

	LightBuffer.Delete();

	NewPolyHedra_Manager.GraphicsDelete();
}



static ::PolyHedra * TestPolyHedraSphere;

void Light3DContext::Make()
{
	std::cout << "Light3DContext::Make() ....\n";

	window.DefaultColor = ColorF4(0.25f, 0.0f, 0.0f);
	View.Depth.Color = window.DefaultColor;
//	View.Trans = Trans3D(VectorF3(0, 64, -2), EulerAngle3D());
	View.Trans = Trans3D(VectorF3(0, 430, -24), EulerAngle3D());

	UserChange.IndicatorsInit(MediaDirectory.Child("YMT/Meta/"));
	UserChange.IndicatorsHide();

	TestPolyHedraSphere = PolyHedraGenerate::SphereY(2, 5, 12.0f);

	InitLights();

	SceneReMake();

	{
		std::cout << "PolyHedraFileCollection[" << PolyHedraFileCollection.FileObjects.Count() << "]\n";
		std::cout << "[\n";
		for (unsigned int i = 0; i < PolyHedraFileCollection.FileObjects.Count(); i++)
		{
			std::cout << "  " << PolyHedraFileCollection.FileObjects[i].File << '\n';
		}
		std::cout << "]\n";
	}

	UIManager.WindowControl.ChildInsert(UISceneObject);
	UIManager.WindowControl.ChildInsert(UIPolyHedraPalletList);
	UIManager.WindowControl.UpdateDepth();

	UISceneObject.Hide();
	UIPolyHedraPalletList.Hide();

	UISceneObject.PolyHedraObject.PalletChange.ClickFunc.Assign(this, &Light3DContext::PolyHedraPalletChangeFunc);

	Shader::Base::BindNone();
	LightBuffer.BindBase(BindingLight);

	ObjectManagerBasic.ShaderFull.Bind();
	ObjectManagerBasic.ShaderFull.BindUniformBlockIndex(ObjectManagerBasic_ShaderFull_Lights -> Index, BindingLight);

	std::cout << "Light3DContext::Make() done\n";
}

void Light3DContext::Init()
{
	ChangeMedia();

	std::cout << "Light3DContext::Init() ....\n";

	GraphicsCreate();

	UIManager.GraphicsInit();

	std::cout << "Light3DContext::Init() done\n";

	Make();
}
void Light3DContext::Free()
{
	std::cout << "Light3DContext::Free() ....\n";

	GraphicsDelete();

	std::cout << "Light3DContext::Free() done\n";
}



// Scrolling to change move Speed
// View Distance from View Center ?
void Light3DContext::User(FrameTime frame_time)
{
	if (window.KeyBoardManager[Keys::Tab].State == State::Press) { window.MouseManager.CursorModeToggle(); }
	if (window.MouseManager.CursorModeIsLocked())
	{
		Trans3D trans = window.MoveSpinFromKeysCursor();

		if (window.KeyBoardManager[Keys::LeftControl].State == State::Down) { trans.Position *= 10; }
		trans.Position *= 20;
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
			std::cout << "UISceneObject.Hide();\n";
			UISceneObject.Hide();
		}
		else
		{
			std::cout << "UISceneObject.Show();\n";
			UISceneObject.Show();
		}
	}

	if (window[Keys::Delete] == State::Press)
	{
		if (Object_Selected != nullptr)
		{
			unsigned int idx = Collection.FindObjectIndex(Object_Selected);
			if (idx != 0xFFFFFFFF)
			{
				Collection.Objects.RemoveAt(idx);
				UserChange.SelectedMakeNone();
				UserChange.IndicatorsHide();
				Object_Selected = nullptr;
			}
		}
	}

	if (window[Keys::Insert] == State::Press)
	{
		NewPolyHedra::PalletObjectManager * manager = ObjectManagerBasic.FindMakePalletObjectManager(Cube);
		Collection.Objects.Insert(new SceneObject_PolyHedraObject(manager, Trans3D()));
	}

	if (window[Keys::D1] == State::Press)
	{
		switch (DisplayMode.Objects)
		{
			case SceneObjectDisplayMode::EObjects::Full: DisplayMode.Objects = SceneObjectDisplayMode::EObjects::Wire; break;
			case SceneObjectDisplayMode::EObjects::Wire: DisplayMode.Objects = SceneObjectDisplayMode::EObjects::None; break;
			case SceneObjectDisplayMode::EObjects::None: DisplayMode.Objects = SceneObjectDisplayMode::EObjects::Full; break;
		}
	}
	if (window[Keys::D2] == State::Press)
	{
		switch (DisplayMode.Indicators)
		{
			case SceneObjectDisplayMode::EIndicators::Show: DisplayMode.Indicators = SceneObjectDisplayMode::EIndicators::Hide; break;
			case SceneObjectDisplayMode::EIndicators::Hide: DisplayMode.Indicators = SceneObjectDisplayMode::EIndicators::Show; break;
		}
	}

	if (window[Keys::F5] == State::Press)
	{
		SceneReMake();
	}
}
void Light3DContext::Draw()
{
	// Uniforms

	MultiformLayout.View.ChangeData(Matrix4x4::TransformReverse(View.Trans));

	LightBufferData data;
	data.Ambient = LightManager.Ambient;
	data.Solar = LightManager.Solar;
	for (unsigned int i = 0; i < LightManager.Point_Count; i++)
	{
		data.Point[i] = LightManager.Point_Array[i];
	}
	data.PointCount = LightManager.Point_Count;
	for (unsigned int i = 0; i < LightManager.Spot_Count; i++)
	{
		data.Spot[i] = LightManager.Spot_Array[i];
	}
	data.SpotCount = LightManager.Spot_Count;

	VertexArray::Base::BindNone();
	LightBuffer.DataFull(Container::Void(data));

	// Instances

	NewPolyHedra_Manager.InstancesClear();
	NewPolyHedra_Manager.InstancesMake();

	Collection.Display(DisplayMode);



	// Draw

	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	ObjectManagerBasic.GraphicsDrawFull();
	ObjectManagerBasic.GraphicsDrawWire();

	GL::Clear(GL::ClearMask::DepthBufferBit);

	ObjectManagerTSC.GraphicsDrawFull();
	ObjectManagerTSC.GraphicsDrawWire();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	UIManager.Draw();



	// Remove

	NewPolyHedra_Manager.UpdatePalletObjectDatas();
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



	UserChange_HoverSelect();
	Objects_Change();

	UserChange_Update();
	Objects_Update();
}



void Light3DContext::Frame(FrameTime frame_time)
{
	static float frameSum = 0;
	frameSum += frame_time.Delta;

	User(frame_time);

	PolyHedraPalletUpdate();
	Collection.Update();

	CenterCube -> Data.Data.Trans.Position = VectorF3(0, 10, 0);
	CenterCube -> Data.Data.Trans.Rotation.Y2 += Angle::Radians(0.01f);

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
