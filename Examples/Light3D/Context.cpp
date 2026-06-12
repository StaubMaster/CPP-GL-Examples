#include "Context.hpp"
#include "General/UnitToString.hpp"

#include "PolyHedra/Generate.hpp"
#include "PolyHedra/ObjectData.hpp"



Light3DContext::~Light3DContext()
{ }
Light3DContext::Light3DContext()
	: ContextBase()
	, PolyHedraManager()
	, UIManager()
	, UISceneObject()
	, LightShaderLayout(Light_Spot_Limit)
{
	PolyHedraManager.MakeCurrent();
}



void Light3DContext::ChangeMedia()
{
	std::cout << "ChangeMedia 0\n";

	PolyHedraManager.ChangeMedia(MediaDirectory);
	{
		Container::Array<Shader::Code> code({
			Shader::Code(MediaDirectory.File("Shaders/PH/Simple3D.vert")),
			Shader::Code(MediaDirectory.File("Shaders/PH/UniLight4.frag")),
			//Shader::Code(MediaDirectory.File("Shaders/PH/Direct.frag")),
		});
		LightShader.Change(code);
		LightShader.UniformLayout = &LightShaderLayout;
		LightShaderLayout.Shader = &LightShader;

		PolyHedraManager.ShaderFullOther = &LightShader;
	}

	UIManager.ChangeMedia(MediaDirectory, window.glfw_window);

	std::cout << "ChangeMedia 1\n";
}
void Light3DContext::GraphicsCreate()
{
	PolyHedraManager.GraphicsCreate();
	LightShader.Create();
	UIManager.GraphicsCreate();

	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderLayoutFullDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderLayoutFullDefault.FOV.Put(view.FOV);

		PolyHedraManager.ShaderWireDefault.Bind();
		PolyHedraManager.ShaderLayoutWireDefault.Depth.Put(view.Depth);
		PolyHedraManager.ShaderLayoutWireDefault.FOV.Put(view.FOV);

		LightShader.Bind();
		LightShaderLayout.Depth.Put(view.Depth);
		LightShaderLayout.FOV.Put(view.FOV);
	}
}
void Light3DContext::GraphicsDelete()
{
	PolyHedraManager.GraphicsDelete();
	LightShader.Delete();
	UIManager.GraphicsDelete();
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
	CenterCube.Object.Create(Cube);
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
			Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(Cube, Trans3D)(
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
	PolyHedraPalletManager * stage_light =			PolyHedraManager.PlacePallet(PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt")));
	PolyHedraPalletManager * stage_light_holder =	PolyHedraManager.PlacePallet(PolyHedra::Load(dir.File("Stage_Light_Holder.polyhedra.ymt")));

	LightAmbientObject.Object.Create(Cube);
	LightAmbientObject.Object.Trans().Position.Y = 40.0f;

	LightSolarObject.Object.Create(Cube);
	LightSolarObject.Object.Trans().Position.Y = 45.0f;
	LightSolarObject.Object.Trans().Rotation = EulerAngle3D::PointToZ(LightSolarObject.Light -> Dir);

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		const LightSpot * light = LightSpotObjects[i].Light;
		EulerAngle3D angle = EulerAngle3D::PointToZ(light -> Dir);

		LightSpotObjects[i].Object0.Create(stage_light);
		LightSpotObjects[i].Object0.Trans().Position = light -> Pos;
		LightSpotObjects[i].Object0.Trans().Rotation = angle;

		LightSpotObjects[i].Object1.Create(stage_light_holder);
		LightSpotObjects[i].Object1.Trans().Position = light -> Pos;
		LightSpotObjects[i].Object1.Trans().Rotation = EulerAngle3D(Angle(), Angle(), angle.Y2);
	}
}
void Light3DContext::Fancify()
{
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedraPalletManager * stage =		PolyHedraManager.PlacePallet(PolyHedra::Load(dir.File("Stage.polyhedra.ymt")));
	PolyHedraPalletManager * truss =		PolyHedraManager.PlacePallet(PolyHedra::Load(dir.File("Truss_Square40cm_Len200cm.polyhedra")));
	PolyHedraPalletManager * truss_cube =	PolyHedraManager.PlacePallet(PolyHedra::Load(dir.File("Truss_Cube40cm.polyhedra")));
	PolyHedraPalletManager * chair =		PolyHedraManager.PlacePallet(PolyHedra::Load(dir.File("Chair.polyhedra")));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(stage, VectorF3(0, 0, 0))));

	float truss_long = 20.0f;
	float truss_wide = 4.5f;

	float w0 = truss_long * 1.0f;
	float w1 = truss_long * 1.5f + truss_wide * 0.5f;

	float h0 = truss_long * 0.5f;
	float h1 = truss_long * 1.5f;
	float h2 = truss_long * 2.0f + truss_wide * 0.5f;

	float d0 = truss_long * 0.5f;
	float d1 = truss_long * 1.0f + truss_wide * 0.5f;

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss_cube, Trans3D(VectorF3(-w1, h2, -d1)))));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss_cube, Trans3D(VectorF3(+w1, h2, -d1)))));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(  0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90)))));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h2, -d0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h2, -d0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h2, +d0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h2, +d0)))));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss_cube, Trans3D(VectorF3(-w1, h2, +d1)))));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss_cube, Trans3D(VectorF3(+w1, h2, +d1)))));

	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(-w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(  0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90)))));
	Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(truss,      Trans3D(VectorF3(+w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90)))));

	for (int y = 0; y < 5; y++)
	{
		for (int x = -5; x <= +5; x++)
		{
			Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(chair, Trans3D(VectorF3(x * +5.0f, (y * 2.0f), (y * -7.5f) -50), EulerAngle3D()))));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(chair, Trans3D(VectorF3(-50, i, -40), EulerAngle3D::Degrees(0, 0, 90)))));
	}
	for (int i = 0; i < 3; i++)
	{
		Objects.Insert(new SceneObject_PolyHedraObject(PolyHedraObject(chair, Trans3D(VectorF3(-50, i, -45), EulerAngle3D::Degrees(0, 0, 90)))));
	}
}



void Light3DContext::Make()
{
	std::cout << "Make 0\n";
	
	window.DefaultColor = ColorF4(0.25f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	view.Trans = Trans3D(VectorF3(0, 10, -65), EulerAngle3D());

	LightsMake();

	RandomCubes();
	Fancify();
	FancyLights();

	UIManager.WindowControl.ChildInsert(UISceneObject);
	UISceneObject.Hide();

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
		trans.Rotation *= view.FOV.ToRadians() * 0.05f;
		view.ChangeFlatX(trans, frame_time.Delta);
	}

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
}
void Light3DContext::Draw()
{
	PolyHedraManager.ShaderFullDefault.Bind();
	PolyHedraManager.ShaderLayoutFullDefault.View.Put(Matrix4x4::TransformReverse(view.Trans));

	PolyHedraManager.ShaderWireDefault.Bind();
	PolyHedraManager.ShaderLayoutWireDefault.View.Put(Matrix4x4::TransformReverse(view.Trans));

	LightShader.Bind();
	LightShaderLayout.View.Put(Matrix4x4::TransformReverse(view.Trans));
	LightShaderLayout.Light_Ambient.Put(Light_Ambient);
	LightShaderLayout.Light_Solar.Put(Light_Solar);
	for (unsigned int i = 0; i < Light_Spot_Count; i++)
	{
		LightShaderLayout.Light_Spot_Array[i].Put(Light_Spot_Array[i]);
	}
	LightShaderLayout.Light_Spot_Count.Put(Light_Spot_Count);



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);
	PolyHedraManager.MakeInstances();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();

	GL::Clear(GL::ClearMask::DepthBufferBit);
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);
	UIManager.Draw();
}



#include "PolyHedra/Data.hpp"
#include "PolyHedra/Skin/Skin.hpp"

SceneObject * SceneObject_Selected = nullptr;

void Light3DContext::ViewRay()
{
	// just dont cast ray if hovering ?

	VectorF2 pos;
	if (!window.MouseManager.CursorModeIsLocked())
	{
		pos = window.Size.Convert(window.MouseManager.CursorPosition());
	}
	Ray3D ray(view.Trans.Position, view.Trans.Rotation.forward(VectorF3(pos.X, pos.Y, 1)));

	Ray3D_Hit hit;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Ray3D_Hit hit_temp = Objects[i] -> Hit(ray);
		hit_temp.Index[2] = i;
		hit.Consider(hit_temp);
	}

	if (UIManager.Hovering == &UIManager.WindowControl && hit.Is())
	{
		SceneObject * base = Objects[hit.Index[2]];
		if (base != nullptr)
		{
			{
				SceneObject_PolyHedraObject * obj = dynamic_cast<SceneObject_PolyHedraObject*>(base);
				if (obj != nullptr)
				{
					PolyHedraObject display_obj = obj -> Object;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
			{
				SceneObject_LightAmbient * obj = dynamic_cast<SceneObject_LightAmbient*>(base);
				if (obj != nullptr)
				{
					PolyHedraObject display_obj = obj -> Object;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
			{
				SceneObject_LightSolar * obj = dynamic_cast<SceneObject_LightSolar*>(base);
				if (obj != nullptr)
				{
					PolyHedraObject display_obj = obj -> Object;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
			{
				SceneObject_LightSpot * obj = dynamic_cast<SceneObject_LightSpot*>(base);
				if (obj != nullptr)
				{
					//if (hit.Index[1] == 0)
					{
						PolyHedraObject display_obj = obj -> Object0;
						display_obj.HideFull();
						display_obj.ShowWire();
					}
					//else if (hit.Index[1] == 1)
					{
						PolyHedraObject display_obj = obj -> Object1;
						display_obj.HideFull();
						display_obj.ShowWire();
					}
				}
			}
		}
	}

	if (UIManager.Hovering == &UIManager.WindowControl && window.MouseManager[MouseButtons::MouseL] == State::Press)
	{
		if (hit.Is())
		{
			SceneObject_Selected = Objects[hit.Index[2]];
			UISceneObject.Show();
		}
		else
		{
			SceneObject_Selected = nullptr;
			UISceneObject.Hide();
		}
		UISceneObject.Change(SceneObject_Selected);
	}

	if (SceneObject_Selected != nullptr)
	{
		UISceneObject.Update();
		{
			SceneObject_PolyHedraObject * obj = dynamic_cast<SceneObject_PolyHedraObject*>(SceneObject_Selected);
			if (obj != nullptr)
			{
				{
					PolyHedraObject display_obj = obj -> Object;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
		}
			{
				SceneObject_LightAmbient * obj = dynamic_cast<SceneObject_LightAmbient*>(SceneObject_Selected);
				if (obj != nullptr)
				{
					PolyHedraObject display_obj = obj -> Object;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
			{
				SceneObject_LightSolar * obj = dynamic_cast<SceneObject_LightSolar*>(SceneObject_Selected);
				if (obj != nullptr)
				{
					PolyHedraObject display_obj = obj -> Object;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
		{
			SceneObject_LightSpot * obj = dynamic_cast<SceneObject_LightSpot*>(SceneObject_Selected);
			if (obj != nullptr)
			{
				{
					PolyHedraObject display_obj = obj -> Object0;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
				{
					PolyHedraObject display_obj = obj -> Object1;
					display_obj.HideFull();
					display_obj.ShowWire();
				}
			}
		}
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

	CenterCube.Object.Trans().Position = VectorF3(0, 10, 0);
	CenterCube.Object.Trans().Rotation.Y2 += Angle::Radians(0.01f);

	ViewRay();

	Draw();
}

void Light3DContext::Resize(DisplaySize display_size)
{
	PolyHedraManager.ShaderFullDefault.Bind();
	PolyHedraManager.ShaderLayoutFullDefault.DisplaySize.Put(display_size);

	PolyHedraManager.ShaderWireDefault.Bind();
	PolyHedraManager.ShaderLayoutWireDefault.DisplaySize.Put(display_size);

	LightShader.Bind();
	LightShaderLayout.DisplaySize.Put(display_size);

	UIManager.Resize(display_size);
}



void Light3DContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void Light3DContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void Light3DContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void Light3DContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void Light3DContext::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void Light3DContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
