#include "Physics2D/Manager.hpp"
#include "Physics2D/Collision.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"

#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Fixed.hpp"

#include "Graphics/Shader/Code.hpp"


#include "Arrow2D/Main/Data.hpp"
#include "ValueType/AxisBox2D.hpp"



Physics2D::Manager::~Manager()
{ }
Physics2D::Manager::Manager()
	: Shader_PolyGon()
	, Shader_WireFrame()
	, MainInstances()

	, Arrow()

	, Objects()

	, Gravity()
	, AirResistance(0.0f)
{
	Arrow.MakeCurrent();
}

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
	Arrow.InitExternal(ShaderDir);
}
void Physics2D::Manager::InitInternal(const DirectoryInfo & ImageDir)
{
	Arrow.InitInternal(ImageDir);
}



void Physics2D::Manager::GraphicsCreate()
{
	Shader_PolyGon.Create();
	Shader_WireFrame.Create(),
	Arrow.GraphicsCreate();
}
void Physics2D::Manager::GraphicsDelete()
{
	Shader_PolyGon.Delete();
	Shader_WireFrame.Delete();
	Arrow.GraphicsDelete();
}
void Physics2D::Manager::GraphicsUpdate()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Objects[i] -> UpdateEntrys();
	}

	for (unsigned int i = 0; i < MainInstances.Count(); i++)
	{
		MainInstances[i].UpdateInst();
	}

	for (unsigned int j = 0; j < MainInstances.Count(); j++)
	{
		unsigned int Count_PolyGon = 0;
		unsigned int Count_WireFrame = 0;
		unsigned int Count_WireFrameBox = 0;
		for (unsigned int i = 0; i < Objects.Count(); i++)
		{
			if (Objects[i] != nullptr && Objects[i] -> InstanceManager == &MainInstances[j])
			{
				if (Objects[i] -> DrawPolyGon) { Count_PolyGon++; }
				if (Objects[i] -> DrawWireFrame) { Count_WireFrame++; }
				if (Objects[i] -> DrawWireFrameBox) { Count_WireFrameBox++; }
			}
		}

		Container::Fixed<Physics2D::Inst::Data> Data_PolyGon(Count_PolyGon);
		Container::Fixed<Physics2D::Inst::Data> Data_WireFrame(Count_WireFrame);
		Container::Fixed<Physics2D::Inst::Data> Data_WireFrameBox(Count_WireFrameBox);
		for (unsigned int i = 0; i < Objects.Count(); i++)
		{
			if (Objects[i] != nullptr && Objects[i] -> InstanceManager == &MainInstances[j])
			{
				if (Objects[i] -> DrawPolyGon) { Data_PolyGon.Insert(Objects[i] -> Data); }
				if (Objects[i] -> DrawWireFrame) { Data_WireFrame.Insert(Objects[i] -> Data); }
				if (Objects[i] -> DrawWireFrameBox) { Data_WireFrameBox.Insert(Objects[i] -> Data); }
			}
		}

		MainInstances[j].Buffer_PolyGon.Inst.Change(Data_PolyGon);
		MainInstances[j].Buffer_WireFrame.Inst.Change(Data_WireFrame);
		MainInstances[j].Buffer_WireFrameBox.Inst.Change(Data_WireFrameBox);
	}
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

	Arrow.Draw();
}



void Physics2D::Manager::UpdateGravity(float timeDelta)
{
	Point2D GravityAccel = Gravity * timeDelta;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i] -> IsStatic)
		{
			Objects[i] -> Data.Vel.Pos += GravityAccel;
		}
	}
}
void Physics2D::Manager::UpdateAirResistance(float timeDelta)
{
	float factor = 1.0f - (AirResistance * timeDelta);
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		if (!Objects[i] -> IsStatic)
		{
			Objects[i] -> Data.Vel.Pos *= factor;
			Objects[i] -> Data.Vel.Rot *= factor;
		}
	}
}

void Physics2D::Manager::UpdateCollision(float timeDelta)
{
	for (unsigned int i0 = 0; i0 < Objects.Count(); i0++)
	{
		for (unsigned int i1 = i0 + 1; i1 < Objects.Count(); i1++)
		{
			Physics2D::CollideLinear(*Objects[i0], *Objects[i1]); // good
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
		if (!Objects[i] -> IsStatic)
		{
			Objects[i] -> Data.Now.Pos += (Objects[i] -> Data.Vel.Pos * timeDelta);
			Objects[i] -> Data.Now.Rot += (Objects[i] -> Data.Vel.Rot * timeDelta);
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
		if (Objects[u.Value] -> IsContaining(p))
		{
			return u;
		}
	}
	return Undex::Invalid();
}
