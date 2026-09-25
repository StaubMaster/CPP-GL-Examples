#include "Graphics/Attribute/General/Layout.hpp"
#include "Graphics/Attribute/General/Base.hpp"



void Attribute::Layout::Clear()
{
	for (unsigned int i = 0; i < Attributes.Count(); i++)
	{
		if (Attributes[i] -> IsDynamic)
		{
			delete Attributes[i];
		}
	}
	Attributes.Clear();
}
void Attribute::Layout::Put(Attribute::Base & attribute)
{
	Attributes.Insert(&attribute);
}
void Attribute::Layout::Put(Attribute::Base * attribute)
{
	if (attribute != nullptr)
	{
		Attributes.Insert(attribute);
	}
}



Attribute::Layout::~Layout()
{
	for (unsigned int i = 0; i < Attributes.Count(); i++)
	{
		if (Attributes[i] -> IsDynamic)
		{
			delete Attributes[i];
		}
	}
}
Attribute::Layout::Layout(GL::AttributeDivisor divisor, GL::AttributeStride stride)
	: Attributes()
	, Divisor(divisor)
	, Stride(stride)
{ }
Attribute::Layout::Layout(GL::AttributeDivisor divisor)
	: Attributes()
	, Divisor(divisor)
	, Stride(0)
{ }

Attribute::Layout::Layout(const Layout & other)
	: Attributes(other.Attributes)
	, Divisor(other.Divisor)
	, Stride(other.Stride)
{ }
/*Attribute::Layout & Attribute::Layout::operator=(const Layout & other)
{
	Attributes = other.Attributes;
}*/



void Attribute::Layout::Bind() const
{
	GL::AttributeOffset offset = nullptr;
	for (unsigned int i = 0; i < Attributes.Count(); i++)
	{
		Attributes[i] -> Bind(Divisor, Stride, offset);
	}
}



void Attribute::Layout::CalcStride()
{
	Stride = 0;
	for (unsigned int i = 0; i < Attributes.Count(); i++)
	{
		Stride += Attributes[i] -> CalcSize();
	}
}
