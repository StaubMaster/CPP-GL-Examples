#include "Physics2D/Object.hpp"
#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Manager.hpp"

#include "PolyGon/Object.hpp"



void Physics2D::Object::Update(float timeDelta)
{
	if (!IsStatic)
	{
		ExtData.Update(timeDelta);
	}
	ExtData.Update(IntData);
	ExtData.Zero();
}



Point2D Physics2D::Object::RelativePositionOf(Point2D p) const { return ExtData.Now / p; }
Point2D Physics2D::Object::AbsolutePositionOf(Point2D p) const { return ExtData.Now * p; }
Point2D Physics2D::Object::AbsoluteVelocityOf(Point2D p) const
{
	return Point2D::cross(ExtData.Vel.Rot.Ang.ToRadians(), (ExtData.Now.Rot * p)) + ExtData.Vel.Pos;
//	Point2D perp = p.perpendicular0().normalize();
//	perp = Data.Now.Rot * perp;
//	perp = perp * (Data.Vel.Rot.Ang.ToRadians() * p.length());
//	return Data.Vel.Pos - perp;
}



const ::PolyGon::Object & Physics2D::Object::PolyGon() const { return *(InstanceManager -> PolyGon); }

unsigned int Physics2D::Object::CornerCount() const { return (PolyGon().Corners.Count()); }

unsigned int Physics2D::Object::SideCount() const { return (PolyGon().Faces.Count()); }

bool Physics2D::Object::IsContaining(Point2D p) const { return PolyGon().IsContaining(RelativePositionOf(p)); }

Point2D Physics2D::Object::RelativePositionOfIndex(unsigned int idx) const { return PolyGon().Corners[idx].Pos; }
Point2D Physics2D::Object::AbsolutePositionOfIndex(unsigned int idx) const { return AbsolutePositionOf(RelativePositionOfIndex(idx)); }
Point2D Physics2D::Object::AbsoluteVelocityOfIndex(unsigned int idx) const { return AbsoluteVelocityOf(RelativePositionOfIndex(idx)); }

Line2D Physics2D::Object::EdgeOfIndex(unsigned int idx) const
{
	if (idx == 0)
	{
		return Line2D(
			AbsolutePositionOfIndex(CornerCount() - 1),
			AbsolutePositionOfIndex(idx - 0)
		);
	}
	else
	{
		return Line2D(
			AbsolutePositionOfIndex(idx - 1),
			AbsolutePositionOfIndex(idx - 0)
		);
	}
}
Point2D Physics2D::Object::EdgeNormalOfIndex(unsigned int idx) const
{
	Line2D line = EdgeOfIndex(idx);
	return (line.Pos1 - line.Pos0).perpendicular0().normalize();
}





void Physics2D::Object::GraphicsUpdate()
{
	// Store Forces individually ?
	if (Arrows.Is())
	{
//		Point2D now = ExtData.Now.Pos;
//		Point2D vel = ExtData.Vel.Pos;
//		Point2D acl = ExtData.Acl.Pos;
//
//		unsigned int idx = 0;
//		Arrows[idx] = Arrow2D::Inst::Data(now, now + vel, 16.0f, ColorF4(0.0f, 0.5f, 0.0f)); idx++;
//
//		/*for (unsigned int j = 0; j < CornerCount(); j++)
//		{
//			Point2D p = CornerFromIndex(j);
//			Point2D now = AbsolutePositionOf(p);
//			Point2D vel = AbsoluteVelocityOf(p);
//			//Arrows[1 + (j * 2 + 0)] = Arrow2D::Inst::Data(now, now + vel, 12.0f, ColorF4(0.5f, 1.0f, 0.5f)); idx++;
//			vel -= ExtData.Vel.Pos;
//			//Arrows[idx] = Arrow2D::Inst::Data(now, now + vel, 16.0f, ColorF4(0.0f, 0.5f, 0.0f)); idx++;
//		}*/
//		vel = Point2D(0, ExtData.Vel.Rot.Ang.ToRadians());
//		Arrows[idx] = Arrow2D::Inst::Data(now, now + vel, 16.0f, ColorF4(0.0f, 0.5f, 0.0f)); idx++;

		Point2D origin = ExtData.Now.Pos;
		//Trans2D & now = ExtData.Now;
		Trans2D & vel = ExtData.Vel;
		Trans2D & acl = ExtData.Acl;
		unsigned int idx = 0;

		(Arrows[idx] = ColorF4(0.0f, 0.5f, 0.0f)) = Ray2D(origin, vel.Pos); idx++;
		(Arrows[idx] = ColorF4(0.0f, 0.5f, 0.0f)) = Ray2D(origin, Point2D(0, vel.Rot.Ang.ToRadians())); idx++;
		(Arrows[idx] = ColorF4(0.0f, 0.0f, 0.5f)) = Ray2D(origin, acl.Pos); idx++;
		(Arrows[idx] = ColorF4(0.0f, 0.0f, 0.5f)) = Ray2D(origin, Point2D(0, acl.Rot.Ang.ToRadians())); idx++;

		//Point2D gravity = InstanceManager -> Manager -> Gravity;
		//if (now.Pos.Y > 0.0f) { gravity.Y = -(InstanceManager -> Manager -> GravityToY); }
		//if (now.Pos.Y < 0.0f) { gravity.Y = +(InstanceManager -> Manager -> GravityToY); }
		//Arrows[idx] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.0f, 0.0f), 12.0f, Ray2D(origin, gravity)); idx++;
	}
}



void Physics2D::Object::Show_PolyGon() { DrawPolyGon = true; }
void Physics2D::Object::Show_WireFrame() { DrawWireFrame = true; }
void Physics2D::Object::Show_WireFrameBox() { DrawWireFrameBox = true; }
void Physics2D::Object::Show_Arrows()
{
	if (!Arrows.Is())
	{
		Arrows.Allocate(0
			+ 1		// Center Move Vel
			+ 1		// Center Spin Vel
			+ 1		// Center Move Acl
			+ 1		// Center Spin Acl
		//	+ 1		// Gravity
		);
	}
}

void Physics2D::Object::Hide_PolyGon() { DrawPolyGon = false; }
void Physics2D::Object::Hide_WireFrame() { DrawWireFrame = false; }
void Physics2D::Object::Hide_WireFrameBox() { DrawWireFrameBox = false; }
void Physics2D::Object::Hide_Arrows()
{
	if (Arrows.Is())
	{
		Arrows.Dispose();
	}
}





Physics2D::Object::~Object()
{ }
Physics2D::Object::Object()
	: InstanceManager(nullptr)
	, RemoveNextFrame(false)
	, IntData()
	, ExtData()
	, IsTangible(true)
	, IsStatic(true)
	, DrawPolyGon(false)
	, DrawWireFrame(false)
	, DrawWireFrameBox(false)
	, Arrows()
{ }
Physics2D::Object::Object(const Object & other)
	: InstanceManager(other.InstanceManager)
	, RemoveNextFrame(other.RemoveNextFrame)
	, IntData(other.IntData)
	, ExtData(other.ExtData)
	, IsTangible(other.IsTangible)
	, IsStatic(other.IsStatic)
	, DrawPolyGon(other.DrawPolyGon)
	, DrawWireFrame(other.DrawWireFrame)
	, DrawWireFrameBox(other.DrawWireFrameBox)
	, Arrows(other.Arrows)
{ }
Physics2D::Object & Physics2D::Object::operator=(const Object & other)
{
	InstanceManager = other.InstanceManager;
	RemoveNextFrame = other.RemoveNextFrame;
	IntData = other.IntData;
	ExtData = other.ExtData;
	IsTangible = other.IsTangible;
	IsStatic = other.IsStatic;
	DrawPolyGon = other.DrawPolyGon;
	DrawWireFrame = other.DrawWireFrame;
	DrawWireFrameBox = other.DrawWireFrameBox;
	Arrows = other.Arrows;
	return *this;
}



Physics2D::Object & Physics2D::Object::Construct(bool is_static)
{
	Object * obj = new Object();
	obj -> InstanceManager = &Physics2D::InstanceManager::Current();
	obj -> InstanceManager -> Manager -> Objects.Insert(obj);
	obj -> IntData = obj -> InstanceManager -> IntData;
	obj -> IsStatic = is_static;
	obj -> DrawPolyGon = true;
	return *obj;
}
Physics2D::Object & Physics2D::Object::Construct(Trans2D now, bool is_static)
{
	Object * obj = new Object();
	obj -> InstanceManager = &Physics2D::InstanceManager::Current();
	obj -> InstanceManager -> Manager -> Objects.Insert(obj);
	obj -> IntData = obj -> InstanceManager -> IntData;
	obj -> ExtData.Now = now;
	obj -> IsStatic = is_static;
	obj -> DrawPolyGon = true;
	return *obj;
}
Physics2D::Object & Physics2D::Object::Construct(Trans2D now, Trans2D vel, bool is_static)
{
	Object * obj = new Object();
	obj -> InstanceManager = &Physics2D::InstanceManager::Current();
	obj -> InstanceManager -> Manager -> Objects.Insert(obj);
	obj -> IntData = obj -> InstanceManager -> IntData;
	obj -> ExtData.Now = now;
	obj -> ExtData.Vel = vel;
	obj -> IsStatic = is_static;
	obj -> DrawPolyGon = true;
	return *obj;
}
