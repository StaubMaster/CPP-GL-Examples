#include "Display/AspectRatio.hpp"


AspectRatio::~AspectRatio()
{ }
AspectRatio::AspectRatio()
	: Value()
{ }

AspectRatio::AspectRatio(const AspectRatio & other)
	: Value(other.Value)
{ }
AspectRatio & AspectRatio::operator=(const AspectRatio & other)
{
	Value = other.Value;
	return *this;
}

AspectRatio::AspectRatio(VectorF2 size)
{
	Change(size);
}

void AspectRatio::Change(VectorF2 size)
{
	// == 0.0f ?
	if (size.X == size.Y)
	{
		Value.X = 1.0f;
		Value.Y = 1.0f;
	}
	else if (size.X > size.Y)
	{
		Value.X = size.Y / size.X;
		Value.Y = 1.0f;
	}
	else if (size.X < size.Y)
	{
		Value.X = 1.0f;
		Value.Y = size.X / size.Y;
	}
	//else // NAN ?
	//{ }
}
