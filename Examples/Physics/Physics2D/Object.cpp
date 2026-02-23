#include "Physics2D/Object.hpp"
#include "PolyGon/Data.hpp"



bool Physics2D::Object::Valid() const { return (MainInstance != nullptr) && Data.Is(); }
const ::PolyGon * Physics2D::Object::PolyGon() const { return (MainInstance -> PolyGon); }

const Trans2D & Physics2D::Object::Now() const { return (*Data).Now; }
const Trans2D & Physics2D::Object::Vel() const { return (*Data).Vel; }

Trans2D & Physics2D::Object::Now() { return (*Data).Now; }
Trans2D & Physics2D::Object::Vel() { return (*Data).Vel; }

unsigned int Physics2D::Object::CornerCount() const { return (PolyGon() -> Corners.Count()); }
unsigned int Physics2D::Object::SideCount() const { return (PolyGon() -> Sides.Count()); }

Point2D Physics2D::Object::CornerFromIndex(unsigned int idx) const { return PolyGon() -> Corners[idx].Pos; }

Point2D Physics2D::Object::RelativePositionOf(Point2D p) const
{
	const Trans2D & now = Now();
	return now.Rot.rotateFore(p - now.Pos);
}
Point2D Physics2D::Object::AbsolutePositionOf(Point2D p) const
{
	const Trans2D & now = Now();
	return now.Rot.rotateBack(p) + now.Pos;
}
Point2D Physics2D::Object::AbsoluteVelocityOf(Point2D p) const
{
	const Trans2D & vel = Vel();
	Point2D v;

	Point2D perp = p.perpendicular0().normalize();
	perp = Now().Rot.rotateBack(perp);
	// use Angle stuff instead ?

	v = perp * (vel.Rot.Ang.ToRadians() * p.length());
	v += vel.Pos;

	return v;
}





Physics2D::Object::~Object()
{ }
Physics2D::Object::Object()
	: MainInstance(nullptr)
	, Data()
	, IsStatic(true)
	, Mass(0.0f)
{ }
Physics2D::Object::Object(const Object & other)
	: MainInstance(other.MainInstance)
	, Data(other.Data)
	, IsStatic(other.IsStatic)
	, Mass(other.Mass)
{ }
Physics2D::Object & Physics2D::Object::operator=(const Object & other)
{
	MainInstance = other.MainInstance;
	Data = other.Data;
	IsStatic = other.IsStatic;
	Mass = other.Mass;
	return *this;
}



Physics2D::Object::Object(Physics2D::MainInstance & main_inst, bool is_static)
	: MainInstance(&main_inst)
	, Data(*(*MainInstance).Instances, 1)
	, IsStatic(is_static)
	, Mass(1.0f)
{ }
Physics2D::Object::Object(Physics2D::MainInstance & main_inst, Trans2D now, bool is_static)
	: MainInstance(&main_inst)
	, Data(*(*MainInstance).Instances, 1)
	, IsStatic(is_static)
	, Mass(1.0f)
{
	Now() = now;
}
Physics2D::Object::Object(Physics2D::MainInstance & main_inst, Trans2D now, Trans2D vel, bool is_static)
	: MainInstance(&main_inst)
	, Data(*(*MainInstance).Instances, 1)
	, IsStatic(is_static)
	, Mass(1.0f)
{
	Now() = now;
	Vel() = vel;
}





bool Physics2D::Object::IsContaining(Point2D p) const
{
	return PolyGon() -> IsContaining(Now().Transform1(p));
}
