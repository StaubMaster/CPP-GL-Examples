#include "Graphics/Uniform/PixelSize.hpp"
#include "Display/PixelSize.hpp"



Uniform::PixelSize::PixelSize(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Full(Name + ".Full")
	, Half(Name + ".Half")
{ }
Uniform::PixelSize::PixelSize(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Full(layout, Name + ".Full")
	, Half(layout, Name + ".Half")
{ }



void Uniform::PixelSize::Put(const ::PixelSize & obj)
{
	Full.Put(obj.Full);
	Half.Put(obj.Half);
}
