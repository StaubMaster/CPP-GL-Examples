#include "Graphics/Uniform/Light/Base.hpp"
#include "ValueType/Light/Base.hpp"



Uniform::LightBase::LightBase(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Intensity(Name + ".Intensity")
	, Color(Name + ".Color")
{ }
Uniform::LightBase::LightBase(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Intensity(layout, Name + ".Intensity")
	, Color(layout, Name + ".Color")
{ }



void Uniform::LightBase::Put(const ::LightBase & obj)
{
	Intensity.Put(obj.Intensity);
	Color.Put(obj.Color);
}
