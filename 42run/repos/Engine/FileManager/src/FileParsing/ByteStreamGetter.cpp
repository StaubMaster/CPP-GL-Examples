#include "FileParsing/ByteStreamGetter.hpp"



ByteStreamGetter::~ByteStreamGetter() { }

ByteStreamGetter::ByteStreamGetter(ByteBlock block)
	: ByteStreamBase(block)
	, Index(0)
{ }



void ByteStreamGetter::Move(uint64 step) { Index += step; }



uint8 ByteStreamGetter::Get1()
{
	uint8 val = Block[Index];
	Index += 1;
	return val;
}
uint16 ByteStreamGetter::Get2()
{
	uint16 val = 0;
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		ptr[0] = Block[Index + 0];
		ptr[1] = Block[Index + 1];
	}
	else
	{
		ptr[0] = Block[Index + 1];
		ptr[1] = Block[Index + 0];
	}
	Index += 2;
	return val;
}
uint32 ByteStreamGetter::Get4()
{
	uint32 val;
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		ptr[0] = Block[Index + 0];
		ptr[1] = Block[Index + 1];
		ptr[2] = Block[Index + 2];
		ptr[3] = Block[Index + 3];
	}
	else
	{
		ptr[0] = Block[Index + 3];
		ptr[1] = Block[Index + 2];
		ptr[2] = Block[Index + 1];
		ptr[3] = Block[Index + 0];
	}
	Index += 4;
	return val;
}
uint64 ByteStreamGetter::Get8()
{
	uint64 val;
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		ptr[0] = Block[Index + 0];
		ptr[1] = Block[Index + 1];
		ptr[2] = Block[Index + 2];
		ptr[3] = Block[Index + 3];
		ptr[4] = Block[Index + 4];
		ptr[5] = Block[Index + 5];
		ptr[6] = Block[Index + 6];
		ptr[7] = Block[Index + 7];
	}
	else
	{
		ptr[0] = Block[Index + 7];
		ptr[1] = Block[Index + 6];
		ptr[2] = Block[Index + 5];
		ptr[3] = Block[Index + 4];
		ptr[4] = Block[Index + 3];
		ptr[5] = Block[Index + 2];
		ptr[6] = Block[Index + 1];
		ptr[7] = Block[Index + 0];
	}
	Index += 8;
	return val;
}

ByteBlock ByteStreamGetter::GetBlock(uint64 size)
{
	return Block.BlockAt(Index, size);
}
