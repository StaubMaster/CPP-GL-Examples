#include "ChunkValue.hpp"



ChunkValue::~ChunkValue() { }
ChunkValue::ChunkValue()
	: Known(false)
	, Value(0.0f)
{ }
ChunkValue::ChunkValue(const ChunkValue & other)
	: Known(other.Known)
	, Value(other.Value)
{ }
ChunkValue & ChunkValue::operator=(const ChunkValue & other)
{
	Known = other.Known;
	Value = other.Value;
	return *this;
}

bool ChunkValue::Check(float val) const
{
	if (Known)
	{
		return (Value == val);
	}
	return false;
}
void ChunkValue::Change(float val)
{
	Known = true;
	Value = val;
}
