#include "Physics2D/Object.hpp"
#include "Physics2D/InstanceManager.hpp"
#include "Physics2D/Manager.hpp"

#include "PolyGon/PolyGon.hpp"
#include "PolyGon/Data.hpp"



//bool Physics2D::Object::IsValid() const { return (InstanceManager != nullptr); }
//const ::PolyGon * Physics2D::Object::PolyGon() const { if (IsValid()) { return (InstanceManager -> PolyGon); } return nullptr; }
const ::PolyGon * Physics2D::Object::PolyGon() const { return (InstanceManager -> PolyGon); }



void Physics2D::Object::UpdateEntrys()
{
//	if (Data_PolyGon.Is()) { (*Data_PolyGon) = Data; }
//	if (Data_WireFrame.Is()) { (*Data_WireFrame) = Data; }
//	if (Data_WireFrameBox.Is()) { (*Data_WireFrameBox) = Data; }
	if (Arrows.Is())
	{
		Point2D now = Data.Now.Pos;
		Point2D vel = Data.Vel.Pos;

		unsigned int idx = 0;
		Arrows[idx] = Arrow2D::Inst::Data(now, now + vel, 16.0f, ColorF4(0.0f, 0.5f, 0.0f)); idx++;

		for (unsigned int j = 0; j < CornerCount(); j++)
		{
			Point2D p = CornerFromIndex(j);
			Point2D now = AbsolutePositionOf(p);
			Point2D vel = AbsoluteVelocityOf(p);
			//Arrows[1 + (j * 2 + 0)] = Arrow2D::Inst::Data(now, now + vel, 12.0f, ColorF4(0.5f, 1.0f, 0.5f)); idx++;
			vel -= Data.Vel.Pos;
			Arrows[idx] = Arrow2D::Inst::Data(now, now + vel, 16.0f, ColorF4(0.0f, 0.5f, 0.0f)); idx++;
		}

		Point2D gravity = InstanceManager -> Manager -> Gravity;
		if (now.Y > 0.0f) { gravity.Y = -(InstanceManager -> Manager -> GravityToY); }
		if (now.Y < 0.0f) { gravity.Y = +(InstanceManager -> Manager -> GravityToY); }
		Arrows[idx] = Arrow2D::Inst::Data(now, now + gravity, 12.0f, ColorF4(0.5f, 0.0f, 0.0f)); idx++;
	}
}



void Physics2D::Object::Show_PolyGon()
{
	/*if (!Data_PolyGon.Is())
	{
		Data_PolyGon.Allocate(*(*InstanceManager).Instances_PolyGon, 1);
	}*/
	DrawPolyGon = true;
}
void Physics2D::Object::Show_WireFrame()
{
	/*if (!Data_WireFrame.Is())
	{
		Data_WireFrame.Allocate(*(*InstanceManager).Instances_WireFrame, 1);
	}*/
	DrawWireFrame = true;
}
void Physics2D::Object::Show_WireFrameBox()
{
	/*if (!Data_WireFrameBox.Is())
	{
		Data_WireFrameBox.Allocate(*(*InstanceManager).Instances_WireFrameBox, 1);
	}*/
	DrawWireFrameBox = true;
}
void Physics2D::Object::Show_Arrows()
{
	/*if (!Data_Arrows.Is())
	{
		//Data_Arrows.Allocate((*(*InstanceManager).Manager).Arrow.Instances, 1 + CornerCount() * 2 + 1);
		//Data_Arrows.Allocate(Arrow2D::Manager::Current().Instances, 1 + CornerCount() * 2 + 1);
		Data_Arrows.Allocate(1 + CornerCount() * 2 + 1);
	}*/
	if (!Arrows.Is())
	{
		Arrows.Allocate(
			1				// Center Move Vel
			+ CornerCount()	// Corner Spin Vel
			+ 1		// Gravity
			);
	}
}

void Physics2D::Object::Hide_PolyGon()
{
	/*if (Data_PolyGon.Is())
	{
		Data_PolyGon.Dispose();
	}*/
	DrawPolyGon = false;
}
void Physics2D::Object::Hide_WireFrame()
{
	/*if (Data_WireFrame.Is())
	{
		Data_WireFrame.Dispose();
	}*/
	DrawWireFrame = false;
}
void Physics2D::Object::Hide_WireFrameBox()
{
	/*if (Data_WireFrameBox.Is())
	{
		Data_WireFrameBox.Dispose();
	}*/
	DrawWireFrameBox = false;
}
void Physics2D::Object::Hide_Arrows()
{
	/*if (Data_Arrows.Is())
	{
		Data_Arrows.Dispose();
	}*/
	if (Arrows.Is())
	{
		Arrows.Dispose();
	}
}

unsigned int Physics2D::Object::CornerCount() const { return (PolyGon() -> Corners.Count()); }
unsigned int Physics2D::Object::SideCount() const { return (PolyGon() -> Sides.Count()); }

Point2D Physics2D::Object::CornerFromIndex(unsigned int idx) const { return PolyGon() -> Corners[idx].Pos; }

Point2D Physics2D::Object::RelativePositionOf(Point2D p) const { return Data.Now / p; }
Point2D Physics2D::Object::AbsolutePositionOf(Point2D p) const { return Data.Now * p; }
Point2D Physics2D::Object::AbsoluteVelocityOf(Point2D p) const
{
	return Point2D::cross(Data.Vel.Rot.Ang.ToRadians(), (Data.Now.Rot * p)) + Data.Vel.Pos;
//	Point2D perp = p.perpendicular0().normalize();
//	perp = Data.Now.Rot * perp;
//	perp = perp * (Data.Vel.Rot.Ang.ToRadians() * p.length());
//	return Data.Vel.Pos - perp;
}





Physics2D::Object::~Object()
{ }
Physics2D::Object::Object()
	: InstanceManager(nullptr)
//	, Data_PolyGon()
//	, Data_WireFrame()
//	, Data_WireFrameBox()
//	, Data_Arrows()
	, Data()
	, Arrows()
	, RemoveNextFrame(false)
	, DrawPolyGon(false)
	, DrawWireFrame(false)
	, DrawWireFrameBox(false)
	, IsTangible(true)
	, IsStatic(true)
	, Mass(0.0f)
{ }
Physics2D::Object::Object(const Object & other)
	: InstanceManager(other.InstanceManager)
//	, Data_PolyGon(other.Data_PolyGon)
//	, Data_WireFrame(other.Data_WireFrame)
//	, Data_WireFrameBox(other.Data_WireFrameBox)
//	, Data_Arrows(other.Data_Arrows)
	, Data(other.Data)
	, Arrows(other.Arrows)
	, RemoveNextFrame(other.RemoveNextFrame)
	, DrawPolyGon(other.DrawPolyGon)
	, DrawWireFrame(other.DrawWireFrame)
	, DrawWireFrameBox(other.DrawWireFrameBox)
	, IsTangible(other.IsTangible)
	, IsStatic(other.IsStatic)
	, Mass(other.Mass)
{ }
Physics2D::Object & Physics2D::Object::operator=(const Object & other)
{
	InstanceManager = other.InstanceManager;
//	Data_PolyGon = other.Data_PolyGon;
//	Data_WireFrame = other.Data_WireFrame;
//	Data_WireFrameBox = other.Data_WireFrameBox;
//	Data_Arrows = other.Data_Arrows;
	Data = other.Data;
	Arrows = other.Arrows;
	RemoveNextFrame = other.RemoveNextFrame;
	DrawPolyGon = other.DrawPolyGon;
	DrawWireFrame = other.DrawWireFrame;
	DrawWireFrameBox = other.DrawWireFrameBox;
	IsTangible = other.IsTangible;
	IsStatic = other.IsStatic;
	Mass = other.Mass;
	return *this;
}



/*Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, bool is_static)
	: InstanceManager(&inst_manager)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data()
	, IsTangible(true)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }*/
/*Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, Trans2D now, bool is_static)
	: InstanceManager(&inst_manager)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data(now)
	, IsTangible(true)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }*/
/*Physics2D::Object::Object(Physics2D::InstanceManager & inst_manager, Trans2D now, Trans2D vel, bool is_static)
	: InstanceManager(&inst_manager)
	, Data_PolyGon(*(*InstanceManager).Instances_PolyGon, 1)
	, Data_WireFrame()
	, Data_WireFrameBox()
	, Data_Arrows()
	, Data(now, vel)
	, IsTangible(true)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }*/

bool Physics2D::Object::IsContaining(Point2D p) const { return PolyGon() -> IsContaining(Data.Now / p); }



Physics2D::Object & Physics2D::Object::Construct(bool is_static)
{
	Object * obj = new Object();
	obj -> InstanceManager = &Physics2D::InstanceManager::Current();
	obj -> DrawPolyGon = true;
	obj -> IsStatic = is_static;
	obj -> Mass = 1.0f;
	obj -> InstanceManager -> Manager -> Objects.Insert(obj);
	return *obj;
}
Physics2D::Object & Physics2D::Object::Construct(Trans2D now, bool is_static)
{
	Object * obj = new Object();
	obj -> InstanceManager = &Physics2D::InstanceManager::Current();
	obj -> Data.Now = now;
	obj -> DrawPolyGon = true;
	obj -> IsStatic = is_static;
	obj -> Mass = 1.0f;
	obj -> InstanceManager -> Manager -> Objects.Insert(obj);
	return *obj;
}
Physics2D::Object & Physics2D::Object::Construct(Trans2D now, Trans2D vel, bool is_static)
{
	Object * obj = new Object();
	obj -> InstanceManager = &Physics2D::InstanceManager::Current();
	obj -> Data.Now = now;
	obj -> Data.Vel = vel;
	obj -> DrawPolyGon = true;
	obj -> IsStatic = is_static;
	obj -> Mass = 1.0f;
	obj -> InstanceManager -> Manager -> Objects.Insert(obj);
	return *obj;
}
