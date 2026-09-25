#include "FileParsing/ByteStreamQueue.hpp"



ByteStreamQueue::~ByteStreamQueue() { }

ByteStreamQueue::ByteStreamQueue(ByteBlock block)
	: ByteStreamBase(block)
	, IndexSet(0)
	, IndexGet(0)
{ }



void ByteStreamQueue::MoveSet() { IndexSet++; }
void ByteStreamQueue::MoveGet() { IndexGet++; }
void ByteStreamQueue::MoveSet(uint64 move) { IndexSet += move; }
void ByteStreamQueue::MoveGet(uint64 move) { IndexGet += move; }



void ByteStreamQueue::Set1(uint8 val)
{
	Block[IndexSet] = val;
	IndexSet += 1;
}
void ByteStreamQueue::Set2(uint16 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[IndexSet + 0] = ptr[0];
		Block[IndexSet + 1] = ptr[1];
	}
	else
	{
		Block[IndexSet + 1] = ptr[0];
		Block[IndexSet + 0] = ptr[1];
	}
	IndexSet += 2;
}
void ByteStreamQueue::Set4(uint32 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[IndexSet + 0] = ptr[0];
		Block[IndexSet + 1] = ptr[1];
		Block[IndexSet + 2] = ptr[2];
		Block[IndexSet + 3] = ptr[3];
	}
	else
	{
		Block[IndexSet + 3] = ptr[0];
		Block[IndexSet + 2] = ptr[1];
		Block[IndexSet + 1] = ptr[2];
		Block[IndexSet + 0] = ptr[3];
	}
	IndexSet += 4;
}
void ByteStreamQueue::Set8(uint64 val)
{
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		Block[IndexSet + 0] = ptr[0];
		Block[IndexSet + 1] = ptr[1];
		Block[IndexSet + 2] = ptr[2];
		Block[IndexSet + 3] = ptr[3];
		Block[IndexSet + 4] = ptr[4];
		Block[IndexSet + 5] = ptr[5];
		Block[IndexSet + 6] = ptr[6];
		Block[IndexSet + 7] = ptr[7];
	}
	else
	{
		Block[IndexSet + 7] = ptr[0];
		Block[IndexSet + 6] = ptr[1];
		Block[IndexSet + 5] = ptr[2];
		Block[IndexSet + 4] = ptr[3];
		Block[IndexSet + 3] = ptr[4];
		Block[IndexSet + 2] = ptr[5];
		Block[IndexSet + 1] = ptr[6];
		Block[IndexSet + 0] = ptr[7];
	}
	IndexSet += 8;
}

void ByteStreamQueue::SetBlock(const ByteBlock & block)
{
	for (uint64 i = 0; i < block.Length(); i++)
	{
		Block[IndexSet + i] = block[i];
	}
	IndexSet += block.Length();
}



void ByteStreamQueue::Set1(uint64 idx, uint8 val)
{
	Block[idx] = val;
}
void ByteStreamQueue::Set2(uint64 idx, uint16 val)
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
void ByteStreamQueue::Set4(uint64 idx, uint32 val)
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
void ByteStreamQueue::Set8(uint64 idx, uint64 val)
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



uint8 ByteStreamQueue::Get1()
{
	uint8 val = Block[IndexGet];
	IndexGet += 1;
	return val;
}
uint16 ByteStreamQueue::Get2()
{
	uint16 val = 0;
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		ptr[0] = Block[IndexGet + 0];
		ptr[1] = Block[IndexGet + 1];
	}
	else
	{
		ptr[0] = Block[IndexGet + 1];
		ptr[1] = Block[IndexGet + 0];
	}
	IndexGet += 2;
	return val;
}
uint32 ByteStreamQueue::Get4()
{
	uint32 val;
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		ptr[0] = Block[IndexGet + 0];
		ptr[1] = Block[IndexGet + 1];
		ptr[2] = Block[IndexGet + 2];
		ptr[3] = Block[IndexGet + 3];
	}
	else
	{
		ptr[0] = Block[IndexGet + 3];
		ptr[1] = Block[IndexGet + 2];
		ptr[2] = Block[IndexGet + 1];
		ptr[3] = Block[IndexGet + 0];
	}
	IndexGet += 4;
	return val;
}
uint64 ByteStreamQueue::Get8()
{
	uint64 val;
	uint8 * ptr = (uint8 *)&val;
	if (Order == ByteOrder::HiToLo)
	{
		ptr[0] = Block[IndexGet + 0];
		ptr[1] = Block[IndexGet + 1];
		ptr[2] = Block[IndexGet + 2];
		ptr[3] = Block[IndexGet + 3];
		ptr[4] = Block[IndexGet + 4];
		ptr[5] = Block[IndexGet + 5];
		ptr[6] = Block[IndexGet + 6];
		ptr[7] = Block[IndexGet + 7];
	}
	else
	{
		ptr[0] = Block[IndexGet + 7];
		ptr[1] = Block[IndexGet + 6];
		ptr[2] = Block[IndexGet + 5];
		ptr[3] = Block[IndexGet + 4];
		ptr[4] = Block[IndexGet + 3];
		ptr[5] = Block[IndexGet + 2];
		ptr[6] = Block[IndexGet + 1];
		ptr[7] = Block[IndexGet + 0];
	}
	IndexGet += 8;
	return val;
}

ByteBlock ByteStreamQueue::GetBlock(uint64 size)
{
	return Block.BlockAt(IndexGet, size);
}
