#include "Physics2D/Collision.hpp"
#include "Physics2D/Collision/Projection.hpp"
#include "Physics2D/Collision/Contact.hpp"
#include "Physics2D/Collision/Resolve.hpp"

#include "ValueType/Intersect.hpp"
#include "ValueType/Point3D.hpp"
#include "ValueType/Trans2D.hpp"

#include "ValueTypeShow.hpp"

#include "IntrinsicData.hpp"
#include "ExtrinsicData.hpp"

#include <cmath>




void Physics2D::Collide(
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	Collision::ContactData contact_data = Collision::ContactData::Contact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	Collision::ResolveData resolve_data = Collision::Resolve(contact_data, obj0, obj1, timeDelta);

	//std::cout << "Resolve.Pos[0] " << resolve_data.Pos0 << " dm/s^2\n";
	//std::cout << "Resolve.Pos[1] " << resolve_data.Pos1 << " dm/s^2\n";
	//std::cout << "Resolve.Rot[0] " << resolve_data.Rot0 << " dm/dm*s^2\n";
	//std::cout << "Resolve.Rot[1] " << resolve_data.Rot1 << " dm/dm*s^2\n";
	//std::cout << '\n';

	//Arrow2D::Object arrows(3);
	//arrows[0] = Arrow2D::Inst::Data(ColorF4(0, 0, 0), 16.0f, Line2D(obj0.ExtData.Now.Pos, contact_data.Position));
	//arrows[1] = Arrow2D::Inst::Data(ColorF4(0, 0, 0), 16.0f, Line2D(obj1.ExtData.Now.Pos, contact_data.Position));
	//arrows[2] = Arrow2D::Inst::Data(ColorF4(0, 1, 0), 16.0f, Ray2D(contact_data.Position, contact_data.Normal));

	if (timeDelta != 0.0f)
	{
		if (!obj0.IsStatic) { obj0.ExtData.Vel.Pos -= (resolve_data.Pos0); }
		if (!obj1.IsStatic) { obj1.ExtData.Vel.Pos += (resolve_data.Pos1); }
		if (!obj0.IsStatic) { obj0.ExtData.Vel.Rot -= (resolve_data.Rot0); }
		if (!obj1.IsStatic) { obj1.ExtData.Vel.Rot += (resolve_data.Rot1); }
	}
	if (obj0.IsStatic) { obj0.ExtData.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.ExtData.Vel = Trans2D(); }
	(void)timeDelta;
}

void Physics2D::Seperate(
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	Physics2D::Collision::ContactData contact_data = Physics2D::Collision::ContactData::Contact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	unsigned int IntersektCount = 0;
	Line2D edge0;
	Line2D edge1;

	for (unsigned int i0 = 0; i0 < obj0.CornerCount(); i0++)
	{
		edge0 = obj0.EdgeOfIndex(i0);
		for (unsigned int i1 = 0; i1 < obj0.CornerCount(); i1++)
		{
			edge1 = obj1.EdgeOfIndex(i1);
			if (IsIntersecting(edge0, edge1))
			{
				IntersektCount++;
			}
		}
	}

	Point2D inter;
	for (unsigned int i0 = 0; i0 < obj0.CornerCount(); i0++)
	{
		edge0 = obj0.EdgeOfIndex(i0);
		for (unsigned int i1 = 0; i1 < obj0.CornerCount(); i1++)
		{
			edge1 = obj1.EdgeOfIndex(i1);
			if (Intersection(edge0, edge1, inter))
			{
/* apply Force from inter to both Centers ?
how much Force ?
something relating to Mass ?
what if one Object is Static, then its Mass is assumed to be Infinite
so its Mass Inverse is 0, how to use Mass Inverse ?
also the Distance from the Intersection also plays a roll
and the Angle ?
just have a general Apply Impulse/Force funciton
what does the current one do ?
the current one does a Drag
I dont want that, but it wants that
*/
				Ray2D force0_ray(inter, obj0.ExtData.Now.Pos - inter);
				Ray2D force1_ray(inter, obj1.ExtData.Now.Pos - inter);
				ObjectForceData force0(obj0, force0_ray.Pos, force0_ray.Dir);
				ObjectForceData force1(obj1, force1_ray.Pos, force1_ray.Dir);
				force0.Apply(obj0);
				force1.Apply(obj1);

				//Arrow2D::Object arrows(4);
				//arrows[0] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.0f), 16.0f, force0_ray);
				//arrows[1] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.5f, 1.0f), 16.0f, force1_ray);
				//arrows[2] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.0f, 0.0f), 16.0f, Ray2D(inter, obj0.EdgeNormalOfIndex(i0)));
				//arrows[3] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.0f, 0.5f), 16.0f, Ray2D(inter, obj1.EdgeNormalOfIndex(i1)));
/*
for the Force, figure out the potential Energy that both objects have
calculate the potential Energy to all Edges and choose the smallest
potential Energy repends on Elasticity ? ignore for now
*/
			}
		}
	}

	(void)timeDelta;
}





Physics2D::ObjectForceData::~ObjectForceData() { }
Physics2D::ObjectForceData::ObjectForceData()
{ }

void Physics2D::ObjectForceData::Calculate(Point2D contact, Point2D force)
{
	Contact = contact;
	Force = force;

	float dot = Point2D::dot(Force, Contact);
	ForcePos = (Contact * ((dot / Contact.length2())));
	ForceRot = Force - ForcePos;
	Torque = Point2D::cross(Contact, ForceRot);
}
void Physics2D::ObjectForceData::Calculate(Object & obj, Point2D contact, Point2D force)
{
	Calculate(contact - obj.ExtData.Now.Pos, force);
}

Physics2D::ObjectForceData::ObjectForceData(Point2D contact, Point2D force)
{
	Calculate(contact, force);
}
Physics2D::ObjectForceData::ObjectForceData(Object & obj, Point2D contact, Point2D force)
{
	Calculate(obj, contact, force);
}

void Physics2D::ObjectForceData::Apply(Object & obj)
{
	obj.ExtData.Acl.Pos += Force / obj.IntData.Mass;
	obj.ExtData.Acl.Rot += Angle::Radians(Torque / obj.IntData.MomentOfInertia);
}



Point2D Physics2D::DragObjectForce(Object & obj, Ray2D drag, float scalar)
{
	// subtract the speed of the Contact
	/*{
		Point2D vel = obj.AbsoluteVelocityOf(obj.RelativePositionOf(drag.Pos));
		data.Force = (drag.Dir - vel) * scalar;
	}*/
	// almost good

	// dont just subtract, scale it somehow.
	// scale based on Mass and Velocity and View Zoom ?
	// decrease Force if Velocity goes in the same Direction
	// this is probably easy
	{
		Point2D momentum = obj.AbsoluteVelocityOf(obj.RelativePositionOf(drag.Pos)) * obj.IntData.Mass;
		//Point2D force = obj.ExtData.Vel.Pos * obj.IntData.Mass;
		return (drag.Dir - momentum) * scalar;
	}
	// this works better
	// but hight scalar makes things janky
}

Physics2D::ObjectDragForceData Physics2D::ApplyDragForce(float timeDelta, Object & obj, Ray2D drag, float scalar, bool change)
{
	ObjectDragForceData data;
	data.Drag = drag;

	Point2D Center = obj.ExtData.Now.Pos;
	Point2D Origin = drag.Pos;
	data.Contact = Line2D(Center, Origin);
//	data.Contact = Line2D(Center, obj.AbsolutePositionOf(obj.IntData.CenterOfMass));

	ObjectForceData force_data(obj, drag.Pos, DragObjectForce(obj, drag, scalar));

	std::cout << "ObjectForceData:\n";
	std::cout << "Contact  : " << force_data.Contact.length() << " dm\n";
	std::cout << "Force    : " << force_data.Force.length() << " kg*dm/s^2\n";
	std::cout << "ForcePos : " << force_data.ForcePos.length() << " kg*dm/s^2\n";
	std::cout << "ForceRot : " << force_data.ForceRot.length() << " kg*dm/s^2\n";
	std::cout << "Torque   : " << force_data.Torque << " kg*dm^2/s^2\n";
	std::cout << '\n';

	force_data.Apply(obj);

	(void)timeDelta;
	(void)change;

	return data;
}


