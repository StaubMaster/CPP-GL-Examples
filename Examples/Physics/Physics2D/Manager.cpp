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
	, GravityToY(0.0f)
{
	Arrow.MakeCurrent();
}

//Physics2D::Manager::Manager(const Manager & other);
//Physics2D::Manager & Physics2D::Manager::operator=(const Manager & other);

void Physics2D::Manager::Dispose()
{ }





void Physics2D::Manager::GraphicsInitExternal(const DirectoryInfo & ShaderDir)
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
	Arrow.GraphicsInitExternal(ShaderDir);
}
void Physics2D::Manager::GraphicsInitInternal(const DirectoryInfo & ImageDir)
{
	Arrow.GraphicsInitInternal(ImageDir);
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
		Objects[i] -> GraphicsUpdate();
	}

	for (unsigned int i = 0; i < MainInstances.Count(); i++)
	{
		MainInstances[i].GraphicsUpdateInst();
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
	(void)timeDelta;
	//Point2D Gravity_Accel = Gravity * timeDelta;
	//float GravityToY_Accel = GravityToY * timeDelta;
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Physics2D::Object & obj = *Objects[i];
		Trans2D & now = obj.ExtData.Now;
		//Trans2D & vel = obj.ExtData.Vel;
		Trans2D & acl = obj.ExtData.Acl;
		if (!obj.IsStatic)
		{
			//vel.Pos += Gravity_Accel;
			//if (now.Pos.Y > 0.0f) { vel.Pos.Y -= GravityToY_Accel; }
			//if (now.Pos.Y < 0.0f) { vel.Pos.Y += GravityToY_Accel; }
			acl.Pos += Gravity;
			if (now.Pos.Y > 0.0f) { acl.Pos.Y -= GravityToY; }
			if (now.Pos.Y < 0.0f) { acl.Pos.Y += GravityToY; }
		}
	}
}
void Physics2D::Manager::UpdateAirResistance(float timeDelta)
{
	(void)timeDelta;
	//float factor = 1.0f - (AirResistance * timeDelta);
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Physics2D::Object & obj = *Objects[i];
		Trans2D & vel = obj.ExtData.Vel;
		Trans2D & acl = obj.ExtData.Acl;
		if (!obj.IsStatic)
		{
			//vel.Pos *= factor;
			//vel.Rot *= factor;
			acl.Pos -= vel.Pos * AirResistance;
			acl.Rot -= vel.Rot * AirResistance;
		}
	}
}

void Physics2D::Manager::UpdateCollision(float timeDelta)
{
	for (unsigned int i0 = 0; i0 < Objects.Count(); i0++)
	{
		for (unsigned int i1 = i0 + 1; i1 < Objects.Count(); i1++)
		{
			Physics2D::Collide(*Objects[i0], *Objects[i1], timeDelta);
			//Physics2D::Seperate(*Objects[i0], *Objects[i1], timeDelta);
		}
	}
}

void Physics2D::Manager::Update(float timeDelta)
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Physics2D::Object & obj = *Objects[i];
		if (!obj.IsStatic)
		{
			obj.Update(timeDelta);
		}
		else
		{
			obj.ExtData.Vel = Trans2D();
		}
		obj.ExtData.Zero();
	}

	UpdateAirResistance(timeDelta);
	UpdateGravity(timeDelta);

	UpdateCollision(timeDelta);

	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Physics2D::Object & obj = *Objects[i];
		obj.ExtData.Update(obj.IntData);
	}
}



Undex Physics2D::Manager::FindObjectIndex(Point2D p) const
{
	for (Undex u; u.Value < Objects.Count(); u++)
	{
		if (Objects[u] -> IsContaining(p))
		{
			return u;
		}
	}
	return Undex::Invalid();
}
