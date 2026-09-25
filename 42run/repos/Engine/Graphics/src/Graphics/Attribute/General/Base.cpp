#include "Graphics/Attribute/General/Base.hpp"
#include "Graphics/Attribute/General/Layout.hpp"



Attribute::Base::~Base()
{ }

Attribute::Base & Attribute::Base::operator=(const Base & other)
{
	(void)other;
	return *this;
}



Attribute::Base::Base(Layout & layout, bool is_dynamic)
	: IsDynamic(is_dynamic)
{
	layout.Put(this);
}
Attribute::Base::Base(Layout & layout, const Base & other, bool is_dynamic)
	: IsDynamic(is_dynamic)
{
	(void)other;
	layout.Put(this);
}
