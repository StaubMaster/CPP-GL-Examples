#include "Graphics/Uniform/RangeF.hpp"
#include "ValueType/RangeF.hpp"



Uniform::RangeF::RangeF(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Min(Name + ".Min")
	, Len(Name + ".Len")
	, Max(Name + ".Max")
{ }
Uniform::RangeF::RangeF(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Min(layout, Name + ".Min")
	, Len(layout, Name + ".Len")
	, Max(layout, Name + ".Max")
{ }



void Uniform::RangeF::Put(const ::RangeF & obj)
{
	Min.Put(obj.GetMin());
	Len.Put(obj.Length());
	Max.Put(obj.GetMax());
}
