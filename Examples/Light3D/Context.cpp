#include "Context.hpp"
#include "General/UnitToString.hpp"

#include "PolyHedra/Generate.hpp"
#include "PolyHedra/ObjectData.hpp"

#include "ValueType/Intersect.hpp"



static void Approach(const Ray3D & ray0, Ray3D_Hit & hit0 , const Ray3D & ray1, Ray3D_Hit & hit1)
{
	VectorF3 diff = ray1.Pos - ray0.Pos;
	VectorF3 norm = VectorF3::cross(ray0.Dir, ray1.Dir);

	float norm_inv = 1.0f / norm.length2();

	if (norm_inv != 0.0f)
	{
		hit0 = Ray3D_Hit(ray0, ray1.Dir.cross(norm).dot(diff) * norm_inv);
		hit1 = Ray3D_Hit(ray1, ray0.Dir.cross(norm).dot(diff) * norm_inv);
	}
	else
	{
		hit0 = Ray3D_Hit();
		hit1 = Ray3D_Hit();
	}
}
static Ray3D_Hit IntersectHit(const Ray3D & ray, VectorF3 pos, VectorF3 norm)
{
	VectorF3 diff = pos - ray.Pos;

	float dot = ray.Dir.dot(norm);
	if (dot != 0.0f)
	{
		return Ray3D_Hit(ray, diff.dot(norm) / dot);
	}
	else
	{
		return Ray3D_Hit();
	}
}

struct UserTrans3DChange
{
	enum class EChangeType
	{
		None,
		AxisX,
		AxisY,
		AxisZ,
		PlaneX,
		PlaneY,
		PlaneZ,
	};
	EChangeType		ChangeType;

	VectorF3	AxisX;
	VectorF3	AxisY;
	VectorF3	AxisZ;

	PolyHedraUIObject		AxisXIndicator;
	PolyHedraUIObject		AxisYIndicator;
	PolyHedraUIObject		AxisZIndicator;

	Trans3D		Trans;

	UserTrans3DChange()
		: ChangeType(EChangeType::None)
		, AxisX(1, 0, 0)
		, AxisY(0, 1, 0)
		, AxisZ(0, 0, 1)
	{ }

	void Update(const View3D & view)
	{
		float dist = (view.Trans.Position - Trans.Position).length();

		AxisXIndicator.Color() = ColorF4(1, 0, 0);
		AxisYIndicator.Color() = ColorF4(0, 1, 0);
		AxisZIndicator.Color() = ColorF4(0, 0, 1);

		AxisXIndicator.Scale() = dist * 0.25f;
		AxisYIndicator.Scale() = dist * 0.25f;
		AxisZIndicator.Scale() = dist * 0.25f;

		AxisXIndicator.Trans().Position = Trans.Position;
		AxisYIndicator.Trans().Position = Trans.Position;
		AxisZIndicator.Trans().Position = Trans.Position;
	}

	bool TypeIsNone() const
	{
		return (ChangeType == EChangeType::None);
	}
	void TypeNone()
	{
		ChangeType = EChangeType::None;
	}
	void TypeFindL(const Ray3D & ray)
	{
		Ray3D_Hit hit;
		Ray3D_Hit hit_temp;

		hit_temp = Ray3D_Hit::IntersectHit(ray, AxisXIndicator);
		hit_temp.Index[0] = 0;
		hit.Consider(hit_temp);

		hit_temp = Ray3D_Hit::IntersectHit(ray, AxisYIndicator);
		hit_temp.Index[0] = 1;
		hit.Consider(hit_temp);

		hit_temp = Ray3D_Hit::IntersectHit(ray, AxisZIndicator);
		hit_temp.Index[0] = 2;
		hit.Consider(hit_temp);

		if (hit.Is())
		{
			switch (hit.Index[0])
			{
				case 0: ChangeType = EChangeType::AxisX; break;
				case 1: ChangeType = EChangeType::AxisY; break;
				case 2: ChangeType = EChangeType::AxisZ; break;
				default: ChangeType = EChangeType::None; break;
			}
		}
		else
		{
			ChangeType = EChangeType::None;
		}
	}
	void TypeFindR(const Ray3D & ray)
	{
		Ray3D_Hit hit;
		Ray3D_Hit hit_temp;

		hit_temp = Ray3D_Hit::IntersectHit(ray, AxisXIndicator);
		hit_temp.Index[0] = 0;
		hit.Consider(hit_temp);

		hit_temp = Ray3D_Hit::IntersectHit(ray, AxisYIndicator);
		hit_temp.Index[0] = 1;
		hit.Consider(hit_temp);

		hit_temp = Ray3D_Hit::IntersectHit(ray, AxisZIndicator);
		hit_temp.Index[0] = 2;
		hit.Consider(hit_temp);

		if (hit.Is())
		{
			switch (hit.Index[0])
			{
				case 0: ChangeType = EChangeType::PlaneX; break;
				case 1: ChangeType = EChangeType::PlaneY; break;
				case 2: ChangeType = EChangeType::PlaneZ; break;
				default: ChangeType = EChangeType::None; break;
			}
		}
		else
		{
			ChangeType = EChangeType::None;
		}
	}

	Trans3D NewTransAxis(const Ray3D & ray, const VectorF3 & axis) const
	{
		Ray3D axis_ray(Trans.Position, axis);
		Ray3D_Hit axis_hit;
		Ray3D_Hit hit;
		Approach(ray, hit, axis_ray, axis_hit);
		if (hit.Interval < 0.0f) { return Trans; }
		return Trans3D(axis_hit.Pos(), Trans.Rotation);
	}
	Trans3D NewTransPlane(const Ray3D & ray, const VectorF3 & axis) const
	{
		Ray3D_Hit hit = IntersectHit(ray, Trans.Position, axis);
		if (!hit.Is()) { return Trans; }
		return Trans3D(hit.Pos(), Trans.Rotation);
	}

	Trans3D NewTrans(const Ray3D & ray)
	{
		if (ChangeType == EChangeType::None) { return Trans; }
		else if (ChangeType == EChangeType::AxisX) { return NewTransAxis(ray, AxisX); }
		else if (ChangeType == EChangeType::AxisY) { return NewTransAxis(ray, AxisY); }
		else if (ChangeType == EChangeType::AxisZ) { return NewTransAxis(ray, AxisZ); }
		else if (ChangeType == EChangeType::PlaneX) { return NewTransPlane(ray, AxisX); }
		else if (ChangeType == EChangeType::PlaneY) { return NewTransPlane(ray, AxisY); }
		else if (ChangeType == EChangeType::PlaneZ) { return NewTransPlane(ray, AxisZ); }
		else { return Trans; }
	}
};
static ::UserTrans3DChange	UserTrans3DChange;



Light3DContext::~Light3DContext()
{ }
Light3DContext::Light3DContext()
	: ContextBase()
	, PolyHedraManager()
	, UIManager()
	, UISceneObject()
	, PolyHedraUIManager()
	, LightShaderLayout(Light_Spot_Limit)
{
	PolyHedraManager.MakeCurrent();
	PolyHedraUIManager.MakeCurrent();
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

	PolyHedraUIManager.ChangeMedia(MediaDirectory);

	std::cout << "ChangeMedia 1\n";
}
void Light3DContext::GraphicsCreate()
{
	PolyHedraManager.GraphicsCreate();
	LightShader.Create();
	UIManager.GraphicsCreate();
	PolyHedraUIManager.GraphicsCreate();

	{
		PolyHedraManager.ShaderFullDefault.Bind();
		PolyHedraManager.ShaderLayoutFullDefault.Depth.Put(View.Depth);
		PolyHedraManager.ShaderLayoutFullDefault.FOV.Put(View.FOV);

		PolyHedraManager.ShaderWireDefault.Bind();
		PolyHedraManager.ShaderLayoutWireDefault.Depth.Put(View.Depth);
		PolyHedraManager.ShaderLayoutWireDefault.FOV.Put(View.FOV);

		LightShader.Bind();
		LightShaderLayout.Depth.Put(View.Depth);
		LightShaderLayout.FOV.Put(View.FOV);

		PolyHedraUIManager.ShaderFullDefault.Bind();
		PolyHedraUIManager.ShaderLayoutFullDefault.Depth.Put(View.Depth);
		PolyHedraUIManager.ShaderLayoutFullDefault.FOV.Put(View.FOV);

		PolyHedraUIManager.ShaderWireDefault.Bind();
		PolyHedraUIManager.ShaderLayoutWireDefault.Depth.Put(View.Depth);
		PolyHedraUIManager.ShaderLayoutWireDefault.FOV.Put(View.FOV);
	}
}
void Light3DContext::GraphicsDelete()
{
	PolyHedraManager.GraphicsDelete();
	LightShader.Delete();
	UIManager.GraphicsDelete();
	PolyHedraUIManager.GraphicsDelete();
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

	(void)stage;
	//Objects.Insert(new SceneObject_PolyHedraObject(stage, VectorF3(0, 0, 0)));

	float truss_long = 20.0f;
	float truss_wide = 4.5f;

	float w0 = truss_long * 1.0f;
	float w1 = truss_long * 1.5f + truss_wide * 0.5f;

	float h0 = truss_long * 0.5f;
	float h1 = truss_long * 1.5f;
	float h2 = truss_long * 2.0f + truss_wide * 0.5f;

	float d0 = truss_long * 0.5f;
	float d1 = truss_long * 1.0f + truss_wide * 0.5f;

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss_cube, Trans3D(VectorF3(-w1, h2, -d1))));

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h0, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h1, -d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss_cube, Trans3D(VectorF3(+w1, h2, -d1))));

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(  0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w0, h2, -d1), EulerAngle3D::Degrees(0, 0, 90))));

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h2, -d0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h2, -d0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h2, +d0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h2, +d0))));

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss_cube, Trans3D(VectorF3(-w1, h2, +d1))));

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h0, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w1, h1, +d1), EulerAngle3D::Degrees(0, 90, 0))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss_cube, Trans3D(VectorF3(+w1, h2, +d1))));

	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(-w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(  0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90))));
	Objects.Insert(new SceneObject_PolyHedraObject(truss,      Trans3D(VectorF3(+w0, h2, +d1), EulerAngle3D::Degrees(0, 0, 90))));

	for (int y = 0; y < 5; y++)
	{
		for (int x = -5; x <= +5; x++)
		{
			Objects.Insert(new SceneObject_PolyHedraObject(chair, Trans3D(VectorF3(x * +5.0f, (y * 2.0f), (y * -7.5f) -50), EulerAngle3D())));
		}
	}

	for (int i = 0; i < 10; i++)
	{
		Objects.Insert(new SceneObject_PolyHedraObject(chair, Trans3D(VectorF3(-50, i, -40), EulerAngle3D::Degrees(0, 0, 90))));
	}
	for (int i = 0; i < 3; i++)
	{
		Objects.Insert(new SceneObject_PolyHedraObject(chair, Trans3D(VectorF3(-50, i, -45), EulerAngle3D::Degrees(0, 0, 90))));
	}
}



static PolyHedra * AxisXIndicator = nullptr;
static PolyHedra * AxisYIndicator = nullptr;
static PolyHedra * AxisZIndicator = nullptr;

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

	AxisXIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/MoveAxis/AxisX.polyhedra"));
	AxisYIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/MoveAxis/AxisY.polyhedra"));
	AxisZIndicator = PolyHedra::Load(MediaDirectory.File("YMT/Meta/MoveAxis/AxisZ.polyhedra"));

	UserTrans3DChange.AxisXIndicator.Create(AxisXIndicator);
	UserTrans3DChange.AxisYIndicator.Create(AxisYIndicator);
	UserTrans3DChange.AxisZIndicator.Create(AxisZIndicator);

	UserTrans3DChange.AxisXIndicator.HideFull();
	UserTrans3DChange.AxisYIndicator.HideFull();
	UserTrans3DChange.AxisZIndicator.HideFull();

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
		View.ChangeFlatX(trans, frame_time.Delta);
	}

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
}
void Light3DContext::Draw()
{
	PolyHedraManager.ShaderFullDefault.Bind();
	PolyHedraManager.ShaderLayoutFullDefault.View.Put(Matrix4x4::TransformReverse(View.Trans));

	PolyHedraManager.ShaderWireDefault.Bind();
	PolyHedraManager.ShaderLayoutWireDefault.View.Put(Matrix4x4::TransformReverse(View.Trans));

	LightShader.Bind();
	LightShaderLayout.View.Put(Matrix4x4::TransformReverse(View.Trans));
	LightShaderLayout.Light_Ambient.Put(Light_Ambient);
	LightShaderLayout.Light_Solar.Put(Light_Solar);
	for (unsigned int i = 0; i < Light_Spot_Count; i++)
	{
		LightShaderLayout.Light_Spot_Array[i].Put(Light_Spot_Array[i]);
	}
	LightShaderLayout.Light_Spot_Count.Put(Light_Spot_Count);

	PolyHedraUIManager.ShaderFullDefault.Bind();
	PolyHedraUIManager.ShaderLayoutFullDefault.View.Put(Matrix4x4::TransformReverse(View.Trans));

	PolyHedraUIManager.ShaderWireDefault.Bind();
	PolyHedraUIManager.ShaderLayoutWireDefault.View.Put(Matrix4x4::TransformReverse(View.Trans));



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

	PolyHedraManager.MakeInstances();
	PolyHedraManager.DrawFull();
	PolyHedraManager.DrawWire();

	PolyHedraUIManager.MakeInstances();
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

	Ray3D_Hit hit;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Ray3D_Hit hit_temp = Objects[i] -> Hit(ViewRay);
		hit_temp.Index[2] = i;
		hit.Consider(hit_temp);
	}

	if (UIManager.Hovering == &UIManager.WindowControl && hit.Is())
	{
		SceneObject * obj = Objects[hit.Index[2]];
		if (obj != nullptr)
		{
			obj -> ShowWire();
		}
	}

	if (UIManager.Hovering == &UIManager.WindowControl && window.MouseManager[MouseButtons::MouseL] == State::Press)
	{
		if (hit.Is())
		{
			SceneObject_Selected = Objects[hit.Index[2]];
			UISceneObject.Show();
			UserTrans3DChange.AxisXIndicator.ShowFull();
			UserTrans3DChange.AxisYIndicator.ShowFull();
			UserTrans3DChange.AxisZIndicator.ShowFull();
		}
		else
		{
			SceneObject_Selected = nullptr;
			UISceneObject.Hide();
			UserTrans3DChange.AxisXIndicator.HideFull();
			UserTrans3DChange.AxisYIndicator.HideFull();
			UserTrans3DChange.AxisZIndicator.HideFull();
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
	UserTrans3DChange.Update(View);
	if (window.MouseManager[MouseButtons::MouseL] == State::Release ||
		window.MouseManager[MouseButtons::MouseR] == State::Release)
	{
		UserTrans3DChange.TypeNone();
		if (SceneObject_Selected != nullptr)
		{
			UserTrans3DChange.Trans = SceneObject_Selected -> GetTrans();
		}
	}
	else if (window.MouseManager[MouseButtons::MouseL] == State::Press)
	{ UserTrans3DChange.TypeFindL(ViewRay); }
	else if (window.MouseManager[MouseButtons::MouseR] == State::Press)
	{ UserTrans3DChange.TypeFindR(ViewRay); }

	Trans3D trans = UserTrans3DChange.NewTrans(ViewRay);
	trans.Position = trans.Position.round(0.1f);

	if (!UserTrans3DChange.TypeIsNone() && SceneObject_Selected != nullptr)
	{
		SceneObject_Selected -> SetTrans(trans);
		//PolyHedraUIObject obj(Cube);
		//obj.Trans() = trans;
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

	CenterCube.Object.Trans().Position = VectorF3(0, 10, 0);
	CenterCube.Object.Trans().Rotation.Y2 += Angle::Radians(0.01f);

	ViewFunc();

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

	PolyHedraUIManager.ShaderFullDefault.Bind();
	PolyHedraUIManager.ShaderLayoutFullDefault.DisplaySize.Put(display_size);

	PolyHedraUIManager.ShaderWireDefault.Bind();
	PolyHedraUIManager.ShaderLayoutWireDefault.DisplaySize.Put(display_size);
}



void Light3DContext::MouseMove(MoveArgs args) { UIManager.MouseMove(args); }
void Light3DContext::MouseClick(ClickArgs args) { UIManager.MouseClick(args); }
void Light3DContext::MouseScroll(ScrollArgs args) { UIManager.MouseScroll(args); }
void Light3DContext::MouseDrag(DragArgs args) { UIManager.MouseDrag(args); }
void Light3DContext::KeyBoardKey(KeyArgs args) { UIManager.KeyBoardKey(args); }
void Light3DContext::KeyBoardText(TextArgs args) { UIManager.KeyBoardText(args); }
