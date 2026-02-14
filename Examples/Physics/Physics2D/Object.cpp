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
Point2D Physics2D::Object::TransCorner(unsigned int idx) const
{
	const Trans2D & trans = Now();
	return trans.Rot.rotateBack(PolyGon() -> Corners[idx].Pos) + trans.Pos;
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
