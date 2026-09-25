#include "Graphics/Uniform/LInter.hpp"
#include "ValueType/LInter.hpp"



Uniform::LInter::LInter(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, T0(Name + ".T0")
	, T1(Name + ".T1")
{ }
Uniform::LInter::LInter(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, T0(layout, Name + ".T0")
	, T1(layout, Name + ".T1")
{ }



void Uniform::LInter::Put(const ::LInter & obj)
{
	T0.Put(obj.GetT0());
	T1.Put(obj.GetT1());
}
