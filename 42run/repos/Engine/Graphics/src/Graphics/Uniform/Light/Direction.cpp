#include "Graphics/Uniform/Light/Direction.hpp"
#include "ValueType/Light/Direction.hpp"



Uniform::LightDirection::LightDirection(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Base(Name + ".Base")
	, Dir(Name + ".Direction")
{ }
Uniform::LightDirection::LightDirection(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Base(layout, Name + ".Base")
	, Dir(layout, Name + ".Direction")
{ }



void Uniform::LightDirection::Put(const ::LightDirection & obj)
{
	Base.Put(obj.Base);
	Dir.Put(obj.Dir);
}
