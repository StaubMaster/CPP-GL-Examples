#include "Graphics/Attribute/General/IntNBase.hpp"



Attribute::IntNBase::~IntNBase()
{ }

Attribute::IntNBase & Attribute::IntNBase::operator=(const IntNBase & other)
{
	Index = other.Index;
	return *this;
}



Attribute::IntNBase::IntNBase(Layout & layout, bool is_dynamic)
	: Base(layout, is_dynamic)
	, Index(-1)
{ }
Attribute::IntNBase::IntNBase(Layout & layout, const IntNBase & other, bool is_dynamic)
	: Base(layout, is_dynamic)
	, Index(other.Index)
{ }

void Attribute::IntNBase::Change(GL::AttributeLocation index)
{
	Index = index;
}
