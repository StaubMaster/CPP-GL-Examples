#include "Graphics/Uniform/AspectRatio.hpp"
#include "Display/AspectRatio.hpp"



Uniform::AspectRatio::AspectRatio(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Value(name)
{ }
Uniform::AspectRatio::AspectRatio(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Value(layout, name)
{ }



void Uniform::AspectRatio::Put(const ::AspectRatio & obj)
{
	Value.Put(obj.Value);
}
