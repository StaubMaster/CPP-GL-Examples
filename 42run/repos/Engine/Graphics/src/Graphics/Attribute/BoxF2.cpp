#include "Graphics/Attribute/BoxF2.hpp"



Attribute::BoxF2::~BoxF2() { }

Attribute::BoxF2::BoxF2(Layout & layout, bool is_dynamic)
	: Attribute::Base(layout, is_dynamic)
	, Min(layout)
	, Max(layout)
{ }
Attribute::BoxF2::BoxF2(Layout & layout, const BoxF2 & other, bool is_dynamic)
	: Attribute::Base(layout, other, is_dynamic)
	, Min(layout, other.Min)
	, Max(layout, other.Max)
{ }



void Attribute::BoxF2::Bind(GL::AttributeDivisor divisor, GL::AttributeStride stride, GL::AttributeOffset & offset) const
{
	(void)divisor;
	(void)stride;
	(void)offset;
	//Min.Bind(divisor, stride, offset);
	//Max.Bind(divisor, stride, offset);
}

unsigned int Attribute::BoxF2::CalcSize() const
{
	//return Min.CalcSize() + Max.CalcSize();
	return 0;
}
