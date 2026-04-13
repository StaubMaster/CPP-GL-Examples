#include "ChunkValue.hpp"



ChunkValue::~ChunkValue() { }
ChunkValue::ChunkValue()
	: Known(false)
	, Undex()
	, Value(0.0f)
{ }
ChunkValue::ChunkValue(const ChunkValue & other)
	: Known(other.Known)
	, Undex(other.Undex)
	, Value(other.Value)
{ }
ChunkValue & ChunkValue::operator=(const ChunkValue & other)
{
	Known = other.Known;
	Undex = other.Undex;
	Value = other.Value;
	return *this;
}

void ChunkValue::Change(VectorU3 udx, float val)
{
	Known = true;
	Undex = udx;
	Value = val;
}
ColorF4 ChunkValue::ToColor() const
{
	if (Value > 0.0f) { return ColorF4(+Value, 0, 0); }
	if (Value < 0.0f) { return ColorF4(0, 0, -Value); }
	return ColorF4(0, 0, 0);
}
