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
	, UIPolyHedraObject()
	, UISpotLightEntry()
	, LightShaderLayout(Light_Spot_Limit)
{
	PolyHedraManager.MakeCurrent();
}



void Light3DContext::LightsInit()
{
	//Light_Ambient_Intensity = 0.01f;
	//Light_Solar_Intensity = 0.2f;
	Light_Ambient_Intensity = 0.1f;
	Light_Solar_Intensity = 0.8f;
	Light_Ambient = LightBase(Light_Ambient_Intensity, ColorF4(1.0f, 1.0f, 1.0f));
	Light_Solar = LightSolar(Light_Solar_Intensity, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(+1, -3, +2).normalize());

	Light_Spot_Array = new LightSpot[Light_Spot_Limit];
	Light_Spot_Array[0] = LightSpot(1.0f, ColorF4(1.0f, 0.0f, 0.0f), VectorF3(), VectorF3(), Range(0.8, 0.95));
	Light_Spot_Array[1] = LightSpot(1.0f, ColorF4(0.0f, 1.0f, 0.0f), VectorF3(), VectorF3(), Range(0.8, 0.95));
	Light_Spot_Array[2] = LightSpot(1.0f, ColorF4(0.0f, 0.0f, 1.0f), VectorF3(), VectorF3(), Range(0.8, 0.95));
	Light_Spot_Array[3] = LightSpot(1.0f, ColorF4(1.0f, 1.0f, 1.0f), VectorF3(), VectorF3(), Range(0.8, 0.95));
	Light_Spot_Count = 3;

	Light_Spot_Entry_Array = new SpotLightEntry[Light_Spot_Limit];
	Light_Spot_Entry_Array[0].Look(VectorF3(+22, 30, -22), VectorF3(0, 0, 0));
	Light_Spot_Entry_Array[1].Look(VectorF3(  0, 30, +22), VectorF3(0, 0, 0));
	Light_Spot_Entry_Array[2].Look(VectorF3(-22, 30, -22), VectorF3(0, 0, 0));
	Light_Spot_Entry_Array[3].Look(VectorF3(  0, 30, -22), VectorF3(0, 0, 0));

	Light_Spot_Entry_Array[0].Light = &Light_Spot_Array[0];
	Light_Spot_Entry_Array[1].Light = &Light_Spot_Array[1];
	Light_Spot_Entry_Array[2].Light = &Light_Spot_Array[2];
	Light_Spot_Entry_Array[3].Light = &Light_Spot_Array[3];
}
void Light3DContext::LightsFree()
{
	delete[] Light_Spot_Entry_Array;
	delete[] Light_Spot_Array;
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



static PolyHedra * Cube = nullptr;
void Light3DContext::RandomCubes()
{
	Cube = PolyHedra::Generate::HexaHedron();

	Objects.Insert(PolyHedraObject(Cube));

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
			Objects.Insert(PolyHedraObject(Cube, Trans3D(
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
	PolyHedra * stage_light =			PolyHedra::Load(dir.File("Stage_Light.polyhedra.ymt"));
	PolyHedra * stage_light_holder =	PolyHedra::Load(dir.File("Stage_Light_Holder.polyhedra.ymt"));

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].EntryLight = PolyHedraObject(stage_light);
		Light_Spot_Entry_Array[i].EntryHolder = PolyHedraObject(stage_light_holder);
	}
}
void Light3DContext::Fancify()
{
	DirectoryInfo dir = MediaDirectory.Child("YMT/Light");
	PolyHedra * stage =					PolyHedra::Load(dir.File("Stage.polyhedra.ymt"));
	//PolyHedra * truss =					PolyHedra::Load(dir.File("Truss_Square40cm_Len200cm.polyhedra"));
	PolyHedra * truss =					PolyHedra::Load(MediaDirectory.File("YMT/Spline/Gleis_Seg.polyhedra"));
	PolyHedra * truss_cube =			PolyHedra::Load(dir.File("Truss_Cube40cm.polyhedra"));
	PolyHedra * chair =					PolyHedra::Load(dir.File("Chair.polyhedra"));

	Objects.Insert(PolyHedraObject(stage, VectorF3(0, 0, 0)));

	float truss_long = 20.0f;
	float truss_wide = 4.5f;

	float w0 = truss_long * 1.0f;
	float w1 = truss_long * 1.5f + truss_wide * 0.5f;

	float h0 = truss_long * 0.5f;
	float h1 = truss_long * 1.5f;
	float h2 = truss_long * 2.0f + truss_wide * 0.5f;

	float d0 = truss_long * 0.5f;
	float d1 = truss_long * 1.0f + truss_wide * 0.5f;

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss_cube, Trans3D(VectorF3(-w1, h2, -d1))));

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss_cube, Trans3D(VectorF3(+w1, h2, -d1))));

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(  0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90))));

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h2, -d0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h2, -d0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h2, +d0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h2, +d0))));

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss_cube, Trans3D(VectorF3(-w1, h2, +d1))));

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(PolyHedraObject(truss_cube, Trans3D(VectorF3(+w1, h2, +d1))));

	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(-w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(  0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(PolyHedraObject(truss,      Trans3D(VectorF3(+w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90))));

	for (int y = 0; y < 5; y++)
	{
		for (int x = -5; x <= +5; x++)
		{
			Objects.Insert(PolyHedraObject(chair, Trans3D(VectorF3(x * +5.0f, (y * 2.0f), (y * -7.5f) -50), EulerAngle3D())));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Objects.Insert(PolyHedraObject(chair, Trans3D(VectorF3(-50, i, -40), EulerAngle3D::Degrees(0, 0, 90))));
	}
	for (int i = 0; i < 3; i++)
	{
		Objects.Insert(PolyHedraObject(chair, Trans3D(VectorF3(-50, i, -45), EulerAngle3D::Degrees(0, 0, 90))));
	}
}



void Light3DContext::Make()
{
	std::cout << "Make 0\n";
	
	window.DefaultColor = ColorF4(0.25f, 0.0f, 0.0f);
	view.Depth.Color = window.DefaultColor;
	view.Trans = Trans3D(VectorF3(0, 10, -65), EulerAngle3D());

	RandomCubes();
	Fancify();
	FancyLights();

	UIManager.WindowControl.ChildInsert(UIPolyHedraObject);
	UIManager.WindowControl.ChildInsert(UISpotLightEntry);
	UIPolyHedraObject.Hide();
	UISpotLightEntry.Hide();

	std::cout << "Make 1\n";
}

void Light3DContext::Init()
{
	ChangeMedia();

	std::cout << "Init 0\n";

	GraphicsCreate();
	LightsInit();

	std::cout << "Init 1\n";

	Make();
}
void Light3DContext::Free()
{
	std::cout << "Free 0\n";

	GraphicsDelete();
	LightsFree();

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

	//Light_Spot.Pos = ViewTrans.Pos;
	//Light_Spot.Dir = ViewTrans.Rot.rotate(VectorF3(0, 0, 1));

	// change Lights with UI ?
	if (window.KeyBoardManager[Keys::D1].State == State::Press)
	{
		if (Light_Ambient.Intensity == 0.0f)
		{ Light_Ambient.Intensity = Light_Ambient_Intensity; }
		else
		{ Light_Ambient.Intensity = 0.0f; }
	}
	if (window.KeyBoardManager[Keys::D2].State == State::Press)
	{
		if (Light_Solar.Base.Intensity == 0.0f)
		{ Light_Solar.Base.Intensity = Light_Solar_Intensity; }
		else
		{ Light_Solar.Base.Intensity = 0.0f; }
	}
	if (window.KeyBoardManager[Keys::D3].State == State::Press) { Light_Spot_Entry_Array[0].Toggle(); }
	if (window.KeyBoardManager[Keys::D4].State == State::Press) { Light_Spot_Entry_Array[1].Toggle(); }
	if (window.KeyBoardManager[Keys::D5].State == State::Press) { Light_Spot_Entry_Array[2].Toggle(); }

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
	for (unsigned int i = 0; i < LightShaderLayout.Light_Spot_Array.Limit; i++)
	{
		if (Light_Spot_Entry_Array[i].Light != nullptr)
		{
			LightShaderLayout.Light_Spot_Array[i].Put(*(Light_Spot_Entry_Array[i].Light));
		}
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

static unsigned int SelectedIndex[4] = {
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
};

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
	{
		Ray3D_Hit hit_temp = Ray3D_Hit::IntersectHit(ray, Objects.ToArray());
		hit_temp.Index[0] = 0;
		hit.Consider(hit_temp);
	}
	{
		Ray3D_Hit hit_temp = Ray3D_Hit::IntersectHit(ray, Light_Spot_Entry_Array, Light_Spot_Limit);
		hit_temp.Index[0] = 1;
		hit.Consider(hit_temp);
	}

	if (UIManager.Hovering == &UIManager.WindowControl && hit.Is())
	{
		if (hit.Index[0] == 0)
		{
			PolyHedraObject obj = Objects[hit.Index[2]];
			obj.HideFull();
			obj.ShowWire();
		}
		else if (hit.Index[0] == 1)
		{
			if (hit.Index[1] == 0)
			{
				PolyHedraObject obj = Light_Spot_Entry_Array[hit.Index[2]].EntryLight;
				obj.HideFull();
				obj.ShowWire();
			}
			else if (hit.Index[1] == 1)
			{
				PolyHedraObject obj = Light_Spot_Entry_Array[hit.Index[2]].EntryHolder;
				obj.HideFull();
				obj.ShowWire();
			}
		}
	}

	if (UIManager.Hovering == &UIManager.WindowControl && window.MouseManager[MouseButtons::MouseL] == State::Press)
	{
		UIPolyHedraObject.Hide();
		UISpotLightEntry.Hide();
		if (hit.Is())
		{
			SelectedIndex[0] = hit.Index[0];
			SelectedIndex[1] = hit.Index[1];
			SelectedIndex[2] = hit.Index[2];
			SelectedIndex[3] = hit.Index[3];
			if (SelectedIndex[0] == 0)
			{
				UIPolyHedraObject.Show();
			}
			else if (SelectedIndex[0] == 1)
			{
				UISpotLightEntry.Show();
			}
		}
		else
		{
			SelectedIndex[0] = 0xFFFFFFFF;
			SelectedIndex[1] = 0xFFFFFFFF;
			SelectedIndex[2] = 0xFFFFFFFF;
			SelectedIndex[3] = 0xFFFFFFFF;
		}
	}

	if (SelectedIndex[0] != 0xFFFFFFFF)
	{
		if (SelectedIndex[0] == 0)
		{
			UIPolyHedraObject.Change(&Objects[SelectedIndex[2]]);
			{
				PolyHedraObject obj = Objects[SelectedIndex[2]];
				obj.HideFull();
				obj.ShowWire();
			}
		}
		else if (SelectedIndex[0] == 1)
		{
			SpotLightEntry & light = Light_Spot_Entry_Array[SelectedIndex[2]];
			UISpotLightEntry.Change(&light);
			{
				PolyHedraObject obj(Cube);
				obj.Trans().Position = light.Origin;
				obj.HideFull();
				obj.ShowWire();
			}
			{
				PolyHedraObject obj(Cube);
				obj.Trans().Position = light.Target;
				obj.HideFull();
				obj.ShowWire();
			}
			{
				PolyHedraObject obj = light.EntryLight;
				obj.HideFull();
				obj.ShowWire();
			}
			{
				PolyHedraObject obj = light.EntryHolder;
				obj.HideFull();
				obj.ShowWire();
			}
		}
	}
}



void Light3DContext::Frame(FrameTime frame_time)
{
	static float frameSum = 0;
	frameSum += frame_time.Delta;

	User(frame_time);

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		Light_Spot_Entry_Array[i].Update();
	}

	Objects[0].Trans().Position = VectorF3(0, 10, 0);
	Objects[0].Trans().Rotation.Y2 += Angle::Radians(0.01f);

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
