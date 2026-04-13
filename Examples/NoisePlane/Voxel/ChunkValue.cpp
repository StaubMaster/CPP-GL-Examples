#include "ChunkValue.hpp"



ChunkValue::~ChunkValue() { }
ChunkValue::ChunkValue()
	: Known(false)
	, Value()
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

bool ChunkValue::IsSolid() const
{
	if (Known)
	{
		return (Value.IsSolid());
	}
	return true;
}
void ChunkValue::Change(Voxel val)
{
	Known = true;
	Value = val;
}
