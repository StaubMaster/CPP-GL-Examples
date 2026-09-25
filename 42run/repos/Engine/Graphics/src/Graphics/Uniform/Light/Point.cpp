#include "Graphics/Uniform/Light/Point.hpp"
#include "ValueType/Light/Point.hpp"



Uniform::LightPoint::LightPoint(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Base(Name + ".Base")
	, Pos(Name + ".Position")
{ }
Uniform::LightPoint::LightPoint(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Base(layout, Name + ".Base")
	, Pos(layout, Name + ".Position")
{ }



void Uniform::LightPoint::Put(const ::LightPoint & obj)
{
	Base.Put(obj.Base);
	Pos.Put(obj.Pos);
}
