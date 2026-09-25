#include "Graphics/Uniform/Depth.hpp"
#include "ValueType/Depth.hpp"



Uniform::Depth::Depth(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Factors(Name + ".Factors")
	, Range(Name + ".Range")
	, Color(Name + ".Color")
{ }
Uniform::Depth::Depth(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Factors(layout, Name + ".Factors")
	, Range(layout, Name + ".Range")
	, Color(layout, Name + ".Color")
{ }



void Uniform::Depth::Put(const ::Depth & obj)
{
	Factors.Put(obj.Factors);
	Range.Put(obj.Range);
	Color.Put(obj.Color);
}
