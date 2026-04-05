#include "Physics2D/Manager.hpp"
#include "Physics2D/Collision.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"

#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Fixed.hpp"

#include "Graphics/Shader/Code.hpp"


#include "Arrow2D/Main/Data.hpp"
#include "ValueType/AxisBox2D.hpp"



Physics2D::Manager::~Manager() { }
Physics2D::Manager::Manager()
	: MainInstances()
	, Objects()

	, Gravity()
	, AirResistance(0.0f)
	, GravityToY(0.0f)
{ }

void Physics2D::Manager::Dispose() { }





void Physics2D::Manager::GraphicsUpdate()
{
	for (unsigned int i = 0; i < Objects.Count(); i++)
	{
		Objects[i] -> GraphicsUpdate();
	}
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
