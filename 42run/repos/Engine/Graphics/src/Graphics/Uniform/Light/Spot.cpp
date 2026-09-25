#include "Graphics/Uniform/Light/Spot.hpp"
#include "ValueType/Light/Spot.hpp"



Uniform::LightSpot::LightSpot(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Base(Name + ".Base")
	, Pos(Name + ".Position")
	, Dir(Name + ".Direction")
	, Range(Name + ".Range")
{ }
Uniform::LightSpot::LightSpot(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Base(layout, Name + ".Base")
	, Pos(layout, Name + ".Position")
	, Dir(layout, Name + ".Direction")
	, Range(layout, Name + ".Range")
{ }



void Uniform::LightSpot::Put(const ::LightSpot & obj)
{
	Base.Put(obj.Base);
	Pos.Put(obj.Pos);
	Dir.Put(obj.Dir);
	Range.Put(obj.Range);
}
