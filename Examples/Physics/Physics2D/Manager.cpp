#include "Physics2D/Manager.hpp"
#include "Physics2D/Collision.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"

#include "Miscellaneous/Container/Array.hpp"

#include "Graphics/Shader/Code.hpp"


#include "Arrow2D/Main/Data.hpp"
#include "ValueType/AxisBox2D.hpp"



Physics2D::Manager::~Manager()
{ }
Physics2D::Manager::Manager()
	: Shader_PolyGon()
	, Shader_WireFrame()
	, MainInstances()

	, Shader_Arrow()
	, Buffer_Arrow(GL::DrawMode::Triangles)
	, Texture_Arrow()
	, Instances_Arrow()

	, Objects()

	, Gravity()
	, AirResistance(0.0f)
{ }

//Physics2D::Manager::Manager(const Manager & other);
//Physics2D::Manager & Physics2D::Manager::operator=(const Manager & other);



void Physics2D::Manager::Dispose()
{ }



void Physics2D::Manager::InitExternal(const DirectoryInfo & ShaderDir)
{
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(ShaderDir.File("Physics/2D.vert")),
			::Shader::Code(ShaderDir.File("Physics/2D.frag")),
		});
		Shader_PolyGon.Change(code);
	}
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(ShaderDir.File("Wire/2D.vert")),
			::Shader::Code(ShaderDir.File("Wire/2D.frag")),
		});
		Shader_WireFrame.Change(code);
	}
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(ShaderDir.File("Arrow/2D.vert")),
			::Shader::Code(ShaderDir.File("Arrow/2D.frag")),
		});
		Shader_Arrow.Change(code);
	}
	{
		Buffer_Arrow.Main.Pos.Change(0);
		Buffer_Arrow.Main.Tex.Change(1);
		Buffer_Arrow.Inst.Pos0.Change(2);
		Buffer_Arrow.Inst.Pos1.Change(3);
		Buffer_Arrow.Inst.Size.Change(4);
		Buffer_Arrow.Inst.Col.Change(5);
	}
}
void Physics2D::Manager::InitInternal(const DirectoryInfo & ImageDir)
{
	{
		Texture_Arrow.Bind();
		Container::Array<FileInfo> files({
			ImageDir.File("Arrow/96x32.png"),
		});
		Texture_Arrow.Assign(96, 32, files);
	}
}



void Physics2D::Manager::GraphicsCreate()
{
	Shader_PolyGon.Create();
	Shader_WireFrame.Create(),
	Shader_Arrow.Create();

	Buffer_Arrow.Create();
	Texture_Arrow.Create();
}
void Physics2D::Manager::GraphicsDelete()
{
	Shader_PolyGon.Delete();
	Shader_WireFrame.Delete();
	Shader_Arrow.Delete();

	Buffer_Arrow.Delete();
	Texture_Arrow.Delete();
}



void Physics2D::Manager::Arrow_Main_Default()
{
	AxisBox2D	Pos;
	AxisBox2D	Tex;

	Container::Binary<Arrow2D::Main::Data> data;

	Pos = AxisBox2D(Point2D(-3, -1), Point2D(-1, +1));
	Tex = AxisBox2D(Point2D(0 / 96.0f, 0), Point2D(32 / 96.0f, 1));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

	Pos = AxisBox2D(Point2D(-1, -1), Point2D(+1, +1));
	Tex = AxisBox2D(Point2D(32 / 96.0f, 0), Point2D(64 / 96.0f, 1));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

	Pos = AxisBox2D(Point2D(+1, -1), Point2D(+3, +1));
	Tex = AxisBox2D(Point2D(64 / 96.0f, 0), Point2D(96 / 96.0f, 1));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Min.Y), Point3D(Tex.Min.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Min.Y), Point3D(Tex.Max.X, Tex.Min.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Min.X, Pos.Max.Y), Point3D(Tex.Min.X, Tex.Max.Y, 0)));
	data.Insert(Arrow2D::Main::Data(Point2D(Pos.Max.X, Pos.Max.Y), Point3D(Tex.Max.X, Tex.Max.Y, 0)));

	Buffer_Arrow.Main.Change(data);
}
void Physics2D::Manager::Arrow_Inst_Update()
{
	Instances_Arrow.CompactHere();
	Buffer_Arrow.Inst.Change(Instances_Arrow);
}
void  Physics2D::Manager::Arrow_Draw()
{
	Arrow_Inst_Update();
	Shader_Arrow.Bind();
	Texture_Arrow.Bind();
	Buffer_Arrow.Draw();
}



void Physics2D::Manager::Draw()
{
	Shader_PolyGon.Bind();
	for (unsigned int i = 0; i < MainInstances.Count(); i++)
	{
		MainInstances[i].Buffer_PolyGon.Draw();
	}

	Shader_WireFrame.Bind();
	for (unsigned int i = 0; i < MainInstances.Count(); i++)
	{
		MainInstances[i].Buffer_WireFrame.Draw();
	}
	for (unsigned int i = 0; i < MainInstances.Count(); i++)
	{
		MainInstances[i].Buffer_WireFrameBox.Draw();
	}

	Arrow_Draw();
}
void Physics2D::Manager::UpdateGraphics()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Objects[i].UpdateEntrys();
	}
	
	for (unsigned int i = 0; i < MainInstances.Count(); i++)
	{
		MainInstances[i].UpdateInst();
	}
}



void Physics2D::Manager::UpdateGravity(float timeDelta)
{
	Point2D GravityAccel = Gravity * timeDelta;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i].IsStatic)
		{
			Objects[i].Data.Vel.Pos += GravityAccel;
		}
	}
}
void Physics2D::Manager::UpdateAirResistance(float timeDelta)
{
	float factor = 1.0f - (AirResistance * timeDelta);
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i].IsStatic)
		{
			Objects[i].Data.Vel.Pos *= factor;
			Objects[i].Data.Vel.Rot *= factor;
		}
	}
}

void Physics2D::Manager::UpdateCollision(float timeDelta)
{
	for (unsigned int i0 = 0; i0 < Objects.Count(); i0++)
	{
		for (unsigned int i1 = i0 + 1; i1 < Objects.Count(); i1++)
		{
			Physics2D::CollideLinear(Objects[i0], Objects[i1]); // good
			//Physics2D::CollideRotate(Objects[i0], Objects[i1]); // wack
			//Physics2D::Collide(Objects[i0], Objects[i1]);
		}
	}
	(void)timeDelta;
}
void Physics2D::Manager::UpdateOrientation(float timeDelta)
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i].IsStatic)
		{
			Objects[i].Data.Now.Pos += (Objects[i].Data.Vel.Pos * timeDelta);
			Objects[i].Data.Now.Rot += (Objects[i].Data.Vel.Rot * timeDelta);
		}
	}
}
void Physics2D::Manager::Update(float timeDelta)
{
	UpdateAirResistance(timeDelta);
	UpdateGravity(timeDelta);

	UpdateCollision(timeDelta);
	UpdateOrientation(timeDelta);
}



Undex Physics2D::Manager::FindObjectIndex(Point2D p) const
{
	for (Undex u; u.Value < Objects.Count(); u++)
	{
		if (Objects[u.Value].IsContaining(p))
		{
			return u;
		}
	}
	return Undex::Invalid();
}