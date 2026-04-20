#include "PolyHedraObjectArray.hpp"



PolyHedraObject & PolyHedraObjectArray::operator[](unsigned int i)
{
	return Array[i];
}



PolyHedraObjectArray::~PolyHedraObjectArray()
{
	delete[] Array;
}
PolyHedraObjectArray::PolyHedraObjectArray()
	: Count(0)
	, Array(nullptr)
{ }



void PolyHedraObjectArray::Create(PolyHedra * polyhedra, unsigned int count)
{
	Count = count;
	Array = new PolyHedraObject[Count];
	for (unsigned int i = 0; i < Count; i++)
	{
		Array[i].Create(polyhedra);
	}
}
void PolyHedraObjectArray::Create(unsigned int polyhedra, unsigned int count)
{
	Count = count;
	Array = new PolyHedraObject[Count];
	for (unsigned int i = 0; i < Count; i++)
	{
		Array[i].Create(polyhedra);
	}
}

void PolyHedraObjectArray::Delete()
{
	delete[] Array;
	Array = nullptr;
	Count = 0;
}
