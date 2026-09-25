#include "Graphics/Attribute/General/FloatNBase.hpp"



Attribute::FloatNBase::~FloatNBase()
{ }

Attribute::FloatNBase & Attribute::FloatNBase::operator=(const FloatNBase & other)
{
	Index = other.Index;
	return *this;
}



Attribute::FloatNBase::FloatNBase(Layout & layout, bool is_dynamic)
	: Base(layout, is_dynamic)
	, Index(-1)
{ }
Attribute::FloatNBase::FloatNBase(Layout & layout, GL::AttributeLocation index, bool is_dynamic)
	: Base(layout, is_dynamic)
	, Index(index)
{ }
Attribute::FloatNBase::FloatNBase(Layout & layout, const FloatNBase & other, bool is_dynamic)
	: Base(layout, is_dynamic)
	, Index(other.Index)
{ }



void Attribute::FloatNBase::Change(GL::AttributeLocation index)
{
	Index = index;
}
