#include "FileParsing/ByteStreamSetter.hpp"



ByteStreamSetter::~ByteStreamSetter() { }

ByteStreamSetter::ByteStreamSetter(ByteBlock block)
	: ByteStreamBase(block)
	, Index(0)
{ }



void ByteStreamSetter::Move(uint64 step) { Index += step; }



void ByteStreamSetter::Set1(uint8 val)
{
	Block[Index] = val;
	Index += 1;
}
void ByteStreamSetter::Set2(uint16 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[Index + 0] = ptr[0];
		Block[Index + 1] = ptr[1];
	}
	else
	{
		Block[Index + 1] = ptr[0];
		Block[Index + 0] = ptr[1];
	}
	Index += 2;
}
void ByteStreamSetter::Set4(uint32 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[Index + 0] = ptr[0];
		Block[Index + 1] = ptr[1];
		Block[Index + 2] = ptr[2];
		Block[Index + 3] = ptr[3];
	}
	else
	{
		Block[Index + 3] = ptr[0];
		Block[Index + 2] = ptr[1];
		Block[Index + 1] = ptr[2];
		Block[Index + 0] = ptr[3];
	}
	Index += 4;
}
void ByteStreamSetter::Set8(uint64 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[Index + 0] = ptr[0];
		Block[Index + 1] = ptr[1];
		Block[Index + 2] = ptr[2];
		Block[Index + 3] = ptr[3];
		Block[Index + 4] = ptr[4];
		Block[Index + 5] = ptr[5];
		Block[Index + 6] = ptr[6];
		Block[Index + 7] = ptr[7];
	}
	else
	{
		Block[Index + 7] = ptr[0];
		Block[Index + 6] = ptr[1];
		Block[Index + 5] = ptr[2];
		Block[Index + 4] = ptr[3];
		Block[Index + 3] = ptr[4];
		Block[Index + 2] = ptr[5];
		Block[Index + 1] = ptr[6];
		Block[Index + 0] = ptr[7];
	}
	Index += 8;
}

void ByteStreamSetter::SetBlock(const ByteBlock & block)
{
	for (uint64 i = 0; i < block.Length(); i++)
	{
		Block[Index + i] = block[i];
	}
	Index += block.Length();
}



void ByteStreamSetter::Set1(uint64 idx, uint8 val)
{
	Block[idx] = val;
}
void ByteStreamSetter::Set2(uint64 idx, uint16 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[idx + 0] = ptr[0];
		Block[idx + 1] = ptr[1];
	}
	else
	{
		Block[idx + 1] = ptr[0];
		Block[idx + 0] = ptr[1];
	}
}
void ByteStreamSetter::Set4(uint64 idx, uint32 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[idx + 0] = ptr[0];
		Block[idx + 1] = ptr[1];
		Block[idx + 2] = ptr[2];
		Block[idx + 3] = ptr[3];
	}
	else
	{
		Block[idx + 3] = ptr[0];
		Block[idx + 2] = ptr[1];
		Block[idx + 1] = ptr[2];
		Block[idx + 0] = ptr[3];
	}
}
void ByteStreamSetter::Set8(uint64 idx, uint64 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[idx + 0] = ptr[0];
		Block[idx + 1] = ptr[1];
		Block[idx + 2] = ptr[2];
		Block[idx + 3] = ptr[3];
		Block[idx + 4] = ptr[4];
		Block[idx + 5] = ptr[5];
		Block[idx + 6] = ptr[6];
		Block[idx + 7] = ptr[7];
	}
	else
	{
		Block[idx + 7] = ptr[0];
		Block[idx + 6] = ptr[1];
		Block[idx + 5] = ptr[2];
		Block[idx + 4] = ptr[3];
		Block[idx + 3] = ptr[4];
		Block[idx + 2] = ptr[5];
		Block[idx + 1] = ptr[6];
		Block[idx + 0] = ptr[7];
	}
}
