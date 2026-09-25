#include "FileParsing/ByteBlock.hpp"
#include <iostream>



uint32 ByteBlock::Length() const { return Bytes.Length(); }

uint8 * ByteBlock::Data() { return Bytes.Data(); }
const uint8 * ByteBlock::Data() const { return Bytes.Data(); }

uint8 * ByteBlock::DataAt(uint64 idx) { return &Bytes[idx]; }
const uint8 * ByteBlock::DataAt(uint64 idx) const { return &Bytes[idx]; }

uint8 & ByteBlock::operator[](uint64 idx) { return Bytes[idx]; }
const uint8 & ByteBlock::operator[](uint64 idx) const { return Bytes[idx]; }

ByteBlock ByteBlock::BlockAt(uint64 idx, uint64 size) const
{
	return ByteBlock(size, &Bytes[idx]);
}



ByteBlock::~ByteBlock() { }
void ByteBlock::Dispose() { Bytes.Clear(); }



ByteBlock::ByteBlock()
	: Bytes()
{ }
ByteBlock::ByteBlock(uint64 size)
	: Bytes(size)
{ }
ByteBlock::ByteBlock(uint64 size, uint8 * data)
	: Bytes(size, data)
{ }
ByteBlock::ByteBlock(uint64 size, const uint8 * data)
	: Bytes(size, data)
{ }



ByteBlock::ByteBlock(const ByteBlock & other)
	: Bytes(other.Bytes)
{ }
ByteBlock ByteBlock::operator=(const ByteBlock & other)
{
	Bytes = other.Bytes;
	return *this;
}



ByteBlock & ByteBlock::Concatenation(uint64 size)
{
	ByteBlock block = *this;
	Bytes.Size(block.Length() + size);

	for (uint64 i = 0; i < block.Length(); i++)
	{
		Bytes[i] = block.Bytes[i];
	}

	return *this;
}
ByteBlock & ByteBlock::Concatenation(const ByteBlock & other)
{
	ByteBlock block = *this;
	Bytes.Size(block.Length() + other.Length());

	for (uint64 i = 0; i < block.Length(); i++)
	{
		Bytes[i] = block.Bytes[i];
	}
	for (uint64 i = 0; i < other.Length(); i++)
	{
		Bytes[i + block.Length()] = other.Bytes[i];
	}

	return *this;
}



ByteBlock::ByteBlock(const std::string & str)
	: Bytes(str.length())
{
	for (uint64 i = 0; i < Bytes.Size(); i++)
	{
		Bytes[i] = str[i];
	}
}
