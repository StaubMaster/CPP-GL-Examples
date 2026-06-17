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
	enum class EIndicatorType
	{
		None,
		MoveAxisX,
		MoveAxisY,
		MoveAxisZ,
		SpinRingX,
		SpinRingY,
		SpinRingZ,
	};
	EIndicatorType	IndicatorHovering;
	VectorF3		IndicatorOffset;

	PolyHedraUIObject	MoveAxisXIndicator;
	PolyHedraUIObject	MoveAxisYIndicator;
	PolyHedraUIObject	MoveAxisZIndicator;

	PolyHedraUIObject	SpinRingXIndicator;
	PolyHedraUIObject	SpinRingYIndicator;
	PolyHedraUIObject	SpinRingZIndicator;

	void FindIndicator(const Ray3D & ray)
	{
		Ray3D_Hit_Type<EIndicatorType> hit(EIndicatorType::None);

		hit.Consider(RayIntersectHit(ray, MoveAxisXIndicator), EIndicatorType::MoveAxisX);
		hit.Consider(RayIntersectHit(ray, MoveAxisYIndicator), EIndicatorType::MoveAxisY);
		hit.Consider(RayIntersectHit(ray, MoveAxisZIndicator), EIndicatorType::MoveAxisZ);

		hit.Consider(RayIntersectHit(ray, SpinRingXIndicator), EIndicatorType::SpinRingX);
		hit.Consider(RayIntersectHit(ray, SpinRingYIndicator), EIndicatorType::SpinRingY);
		hit.Consider(RayIntersectHit(ray, SpinRingZIndicator), EIndicatorType::SpinRingZ);

		if (hit.Is())
		{
			IndicatorOffset = hit.Pos();
			IndicatorHovering = hit.Index;
		}
		else
		{
			IndicatorOffset = VectorF3();
			IndicatorHovering = EIndicatorType::None;
		}
	}
	void UpdateIndicator(const View3D & view)
	{
		float dist = (view.Trans.Position - Trans.Position).length();

		if (IndicatorHovering == EIndicatorType::None)
		{
			MoveAxisXIndicator.Color() = ColorF4(1, 0, 0);
			MoveAxisYIndicator.Color() = ColorF4(0, 1, 0);
			MoveAxisZIndicator.Color() = ColorF4(0, 0, 1);
			SpinRingXIndicator.Color() = ColorF4(1, 0, 0);
			SpinRingYIndicator.Color() = ColorF4(0, 1, 0);
			SpinRingZIndicator.Color() = ColorF4(0, 0, 1);
		}
		else
		{
			MoveAxisXIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
			MoveAxisYIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
			MoveAxisZIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
			SpinRingXIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
			SpinRingYIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
			SpinRingZIndicator.Color() = ColorF4(0.5f, 0.5f, 0.5f);
			switch (IndicatorHovering)
			{
				case EIndicatorType::MoveAxisX: MoveAxisXIndicator.Color() = ColorF4(1, 0, 0); break;
				case EIndicatorType::MoveAxisY: MoveAxisYIndicator.Color() = ColorF4(0, 1, 0); break;
				case EIndicatorType::MoveAxisZ: MoveAxisZIndicator.Color() = ColorF4(0, 0, 1); break;
				case EIndicatorType::SpinRingX: SpinRingXIndicator.Color() = ColorF4(1, 0, 0); break;
				case EIndicatorType::SpinRingY: SpinRingYIndicator.Color() = ColorF4(0, 1, 0); break;
				case EIndicatorType::SpinRingZ: SpinRingZIndicator.Color() = ColorF4(0, 0, 1); break;
				default: break;
			}
		}

		MoveAxisXIndicator.Scale() = dist * 0.25f;
		MoveAxisYIndicator.Scale() = dist * 0.25f;
		MoveAxisZIndicator.Scale() = dist * 0.25f;
		SpinRingXIndicator.Scale() = dist * 0.25f;
		SpinRingYIndicator.Scale() = dist * 0.25f;
		SpinRingZIndicator.Scale() = dist * 0.25f;

		MoveAxisXIndicator.Trans().Position = Trans.Position;
		MoveAxisYIndicator.Trans().Position = Trans.Position;
		MoveAxisZIndicator.Trans().Position = Trans.Position;
		SpinRingXIndicator.Trans().Position = Trans.Position;
		SpinRingYIndicator.Trans().Position = Trans.Position;
		SpinRingZIndicator.Trans().Position = Trans.Position;
	}



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

	Trans3D		Trans;

	VectorF3	Offset;

	UserTrans3DChange()
		: IndicatorHovering(EIndicatorType::None)
		, ChangeType(EChangeType::None)
		, AxisX(1, 0, 0)
		, AxisY(0, 1, 0)
		, AxisZ(0, 0, 1)
	{ }

	bool TypeIsNone() const
	{
		return (ChangeType == EChangeType::None);
	}
	void TypeUseNone()
	{
		ChangeType = EChangeType::None;
	}
	void TypeUseL()
	{
		if (IndicatorHovering == EIndicatorType::None) { return; }
		switch (IndicatorHovering)
		{
			case EIndicatorType::MoveAxisX: ChangeType = EChangeType::AxisX; break;
			case EIndicatorType::MoveAxisY: ChangeType = EChangeType::AxisY; break;
			case EIndicatorType::MoveAxisZ: ChangeType = EChangeType::AxisZ; break;
			default: ChangeType = EChangeType::None; break;
		}
		Offset = Trans.Position - IndicatorOffset;
	}
	void TypeUseR()
	{
		if (IndicatorHovering == EIndicatorType::None) { return; }
		switch (IndicatorHovering)
		{
			case EIndicatorType::MoveAxisX: ChangeType = EChangeType::PlaneX; break;
			case EIndicatorType::MoveAxisY: ChangeType = EChangeType::PlaneY; break;
			case EIndicatorType::MoveAxisZ: ChangeType = EChangeType::PlaneZ; break;
			default: ChangeType = EChangeType::None; break;
		}
		Offset = Trans.Position - IndicatorOffset;
	}

	Trans3D NewTransAxis(const Ray3D & ray, const VectorF3 & axis) const
	{
		Ray3D axis_ray(Trans.Position - Offset, axis);
		Ray3D_Hit axis_hit;
		Ray3D_Hit hit;
		Approach(ray, hit, axis_ray, axis_hit);
		if (hit.Interval < 0.0f) { return Trans; }
		return Trans3D(axis_hit.Pos() + Offset, Trans.Rotation);
	}
	Trans3D NewTransPlane(const Ray3D & ray, const VectorF3 & axis) const
	{
		Ray3D_Hit hit = IntersectHit(ray, Trans.Position - Offset, axis);
		if (!hit.Is()) { return Trans; }
		return Trans3D(hit.Pos() + Offset, Trans.Rotation);
	}
	Trans3D NewTrans(const Ray3D & ray)
	{
		if (ChangeType == EChangeType::None) { return Trans; }
		else if (ChangeType == EChangeType::AxisX)  { return NewTransAxis(ray, AxisX); }
		else if (ChangeType == EChangeType::AxisY)  { return NewTransAxis(ray, AxisY); }
		else if (ChangeType == EChangeType::AxisZ)  { return NewTransAxis(ray, AxisZ); }
		else if (ChangeType == EChangeType::PlaneX) { return NewTransPlane(ray, AxisX); }
		else if (ChangeType == EChangeType::PlaneY) { return NewTransPlane(ray, AxisY); }
		else if (ChangeType == EChangeType::PlaneZ) { return NewTransPlane(ray, AxisZ); }
		else { return Trans; }
	}
};
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
	, LightShaderLayout(Light_Spot_Limit)
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

	MultiformLayout.Depth.ChangeData(View.Depth);
	MultiformLayout.FOV.ChangeData(View.FOV);
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

	LightAmbientObject.Pallet = PolyHedraManager.MakePallet(Cube);
	LightAmbientObject.Position.Y = 40.0f;

	LightSolarObject.Pallet = PolyHedraManager.MakePallet(Cube);
	LightSolarObject.Position.Y = 45.0f;

	for (unsigned int i = 0; i < Light_Spot_Limit; i++)
	{
		const LightSpot * light = LightSpotObjects[i].Light;
		EulerAngle3D angle = EulerAngle3D::PointToZ(light -> Dir);

		LightSpotObjects[i].Pallet0 = stage_light;
		LightSpotObjects[i].Pallet1 = stage_light_holder;
		LightSpotObjects[i].Trans.Position = light -> Pos;
		LightSpotObjects[i].Trans.Rotation = angle;
	}
}



#include "FileParsing/Text/Exceptions.hpp"
struct SceneParsingData
{
	FileInfo		File;

	::PolyHedraManager &				PolyHedraManager;
	Container::Binary<SceneObject*> &	Objects;

	PolyHedraPalletManager *					MissingPolyHedra;
	Container::Binary<PolyHedraPalletManager*>	PolyHedras;

	struct MapVariableFloat
	{
		struct Variable
		{
			std::string		Name;
			float			Value;
		};
		Container::Binary<Variable>		Variables;
		Variable * Find(std::string name)
		{
			for (unsigned int i = 0; i < Variables.Count(); i++)
			{
				if (Variables[i].Name == name)
				{
					return &Variables[i];
				}
			}
			return nullptr;
		}
		void Put(const TextCommand & cmd)
		{
			if (!(cmd.Count() == 2)) { throw InvalidCommandArgumentCount(cmd, "n == 2"); }
			Variable * var = Find(cmd.ToString(0));
			if (var != nullptr)
			{
				var -> Value = cmd.ToFloat(1);
			}
			else
			{
				Variable v;
				v.Name = cmd.ToString(0);
				v.Value = cmd.ToFloat(1);
				Variables.Insert(v);
			}
		}
		float To(const TextCommand & cmd, unsigned int idx)
		{
			std::string str = cmd.ToString(idx);
			char c = str[0];

			bool s = false;
			s = (c == '+' || c == '-');

			if (s) { c = str[1]; }

			if ((c >= '0' && c <= '9')) { return cmd.ToFloat(idx); }

			if (s) { c = str[0]; str.erase(0, 1); }

			Variable * var = Find(str);
			if (var != nullptr)
			{
				float v = var -> Value;
				if (s)
				{
					if (c == '+') { v = +v; }
					if (c == '-') { v = -v; }
				}
				return v;
			}
			return 0.0f; // return NaN ?
		}
	};
	MapVariableFloat	VarsFloat;

	~SceneParsingData()
	{ }
	SceneParsingData(const FileInfo & file, ::PolyHedraManager & manager, Container::Binary<SceneObject*> & objects)
		: File(file)
		, PolyHedraManager(manager)
		, Objects(objects)
		, PolyHedras()
	{
		MissingPolyHedra = PolyHedraManager.MakePallet(PolyHedra::Generate::HexaHedron(1.0f));
	}

	void Parse(const TextCommand & cmd)
	{
		try
		{
			std::string name = cmd.Name();
			if (name == "") { /*std::cout << "empty\n";*/ }

			else if (name == "varFloat")	{ VarsFloat.Put(cmd); }

			else if (name == "polyhedra")	{ Parse_PolyHedra(cmd); }
			else if (name == "place")		{ Parse_Place(cmd); }

			else { std::cout << "unknown: " << cmd << '\n'; }
		}
		catch (std::exception & ex)
		{
			std::cout << "Exception while Parsing Scene: " << ex.what() << '\n';
			std::cout << "Exception on TextCommand: " << cmd << '\n';
		}
	}

	void Parse_PolyHedra(const TextCommand & cmd)
	{
		if (!(cmd.Count() == 1)) { throw InvalidCommandArgumentCount(cmd, "n == 1"); }

		FileInfo file((File.DirectoryString() + "/" + cmd.ToString(0)).c_str());
		if (!file.Exists()) { std::cout << cmd.Name() << ": " << "Bad Skin File" << "\n"; return; }
		PolyHedras.Insert(PolyHedraManager.MakePallet(PolyHedra::Load(file)));
	}
	void Parse_Place(const TextCommand & cmd)
	{
		if (!(cmd.Count() == 7)) { throw InvalidCommandArgumentCount(cmd, "n == 7"); }

		std::string name = cmd.ToString(0);
		PolyHedraPalletManager * polyhedra = MissingPolyHedra;
		for (unsigned int i = 0; i < PolyHedras.Count(); i++)
		{
			if (PolyHedras[i] -> Pallet -> Name == name)
			{
				polyhedra = PolyHedras[i];
			}
		}

		Trans3D trans(
			VectorF3(
				VarsFloat.To(cmd, 1),
				VarsFloat.To(cmd, 2),
				VarsFloat.To(cmd, 3)
			),
			EulerAngle3D::Degrees(
				VarsFloat.To(cmd, 4),
				VarsFloat.To(cmd, 5),
				VarsFloat.To(cmd, 6)
			)
		);

		Objects.Insert(new SceneObject_PolyHedraObject(polyhedra, trans));
	}
};

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
		View.ChangeFlatX(trans, frame_time.Delta);
	}

	UIManager.UpdateMouse(window.MouseManager.CursorPosition());
}
void Light3DContext::Draw()
{
	MultiformLayout.View.ChangeData(Matrix4x4::TransformReverse(View.Trans));

	LightShader.Bind();
	LightShaderLayout.Light_Ambient.Put(Light_Ambient);
	LightShaderLayout.Light_Solar.Put(Light_Solar);
	for (unsigned int i = 0; i < Light_Spot_Count; i++)
	{
		LightShaderLayout.Light_Spot_Array[i].Put(Light_Spot_Array[i]);
	}
	LightShaderLayout.Light_Spot_Count.Put(Light_Spot_Count);



	PolyHedraManager.MakeInstances();
	PolyHedraUIManager.MakeInstances();

	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (Objects[i] == nullptr) { continue; }
		Objects[i] -> DisplayObject();
	}



	GL::Enable(GL::Capability::DepthTest);
	GL::Enable(GL::Capability::CullFace);

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
		UserTrans3DChange.UpdateIndicator(View);
	}

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
