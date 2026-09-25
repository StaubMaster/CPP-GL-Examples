#include "FileParsing/BitStreamGetter.hpp"



BitStreamGetter::~BitStreamGetter() { }

BitStreamGetter::BitStreamGetter(ByteBlock block)
	: BitStreamBase(block)
	, IndexGetBit(0)
	, IndexGetByte(0)
{ }



const uint8 * BitStreamGetter::DataAtIndex() const { return Block.DataAt(IndexGetByte); }



void BitStreamGetter::MoveNextByte()
{
	if (IndexGetBit != 0)
	{
		IndexGetBit = 0;
		IndexGetByte++;
	}
}
void BitStreamGetter::MoveByte(uint32 step)
{
	IndexGetByte += step;
}
void BitStreamGetter::MoveBit(uint32 step)
{
	IndexGetBit += step;
	IndexGetByte += IndexGetBit >> 3;
	IndexGetBit &= 0b111;
}



uint8 BitStreamGetter::Get8(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT8_BIT_LIMIT) + 1;

	uint8 val;
	if (IndexGetBit != 0)
	{
		val = ((uint8)Block[IndexGetByte]) >> (IndexGetBit);
		val |= ((uint8)Block[IndexGetByte + 1]) << ((1 * 8) - IndexGetBit);
	}
	else
	{
		val = ((uint8)Block[IndexGetByte]);
	}

	return val;
}
uint16 BitStreamGetter::Get16(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT16_BIT_LIMIT) + 1;

	uint16 val;
	if (IndexGetBit != 0)
	{
		val = ((uint16)Block[IndexGetByte]) >> (IndexGetBit);
		val |= ((uint16)Block[IndexGetByte + 1]) << ((1 * 8) - IndexGetBit);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint16)Block[IndexGetByte + 2]) << ((2 * 8) - IndexGetBit); }
	}
	else
	{
		val = ((uint16)Block[IndexGetByte]);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint16)Block[IndexGetByte + 1]) << (1 * 8); }
	}

	if (bit_count != UINT16_BIT_COUNT)
	{
		val = val & (UINT16_BIT_MASK >> (UINT16_BIT_COUNT - bit_count));
	}

	return val;
}
uint32 BitStreamGetter::Get32(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT32_BIT_LIMIT) + 1;

	uint32 val;
	if (IndexGetBit != 0)
	{
		val = ((uint32)Block[IndexGetByte]) >> (IndexGetBit);
		val |= ((uint32)Block[IndexGetByte + 1]) << ((1 * 8) - IndexGetBit);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint32)Block[IndexGetByte + 2]) << ((2 * 8) - IndexGetBit); }
		if (bit_count > (2 * 8) - 1)	{ val |= ((uint32)Block[IndexGetByte + 3]) << ((3 * 8) - IndexGetBit); }
		if (bit_count > (3 * 8) - 1)	{ val |= ((uint32)Block[IndexGetByte + 4]) << ((4 * 8) - IndexGetBit); }
	}
	else
	{
		val = ((uint32)Block[IndexGetByte]);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint32)Block[IndexGetByte + 1]) << (1 * 8); }
		if (bit_count > (2 * 8) - 1)	{ val |= ((uint32)Block[IndexGetByte + 2]) << (2 * 8); }
		if (bit_count > (3 * 8) - 1)	{ val |= ((uint32)Block[IndexGetByte + 3]) << (3 * 8); }
	}

	if (bit_count != UINT32_BIT_COUNT)
	{
		val = val & (UINT32_BIT_MASK >> (UINT32_BIT_COUNT - bit_count));
	}

	return val;
}
uint64 BitStreamGetter::Get64(uint8 bit_count) const
{
	if (bit_count == 0) { return 0; }
	bit_count = ((bit_count - 1) & UINT64_BIT_LIMIT) + 1;

	uint64 val;
	if (IndexGetBit != 0)
	{
		val = ((uint64)Block[IndexGetByte]) >> (IndexGetBit);
		val |= ((uint64)Block[IndexGetByte + 1]) << ((1 * 8) - IndexGetBit);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 2]) << ((2 * 8) - IndexGetBit); }
		if (bit_count > (2 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 3]) << ((3 * 8) - IndexGetBit); }
		if (bit_count > (3 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 4]) << ((4 * 8) - IndexGetBit); }
		if (bit_count > (4 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 5]) << ((5 * 8) - IndexGetBit); }
		if (bit_count > (5 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 6]) << ((6 * 8) - IndexGetBit); }
		if (bit_count > (6 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 7]) << ((7 * 8) - IndexGetBit); }
		if (bit_count > (7 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 8]) << ((8 * 8) - IndexGetBit); }
	}
	else
	{
		val = ((uint64)Block[IndexGetByte]);
		if (bit_count > (1 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 1]) << (1 * 8); }
		if (bit_count > (2 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 2]) << (2 * 8); }
		if (bit_count > (3 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 3]) << (3 * 8); }
		if (bit_count > (4 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 4]) << (4 * 8); }
		if (bit_count > (5 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 5]) << (5 * 8); }
		if (bit_count > (6 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 6]) << (6 * 8); }
		if (bit_count > (7 * 8) - 1)	{ val |= ((uint64)Block[IndexGetByte + 7]) << (7 * 8); }
	}

	if (bit_count != UINT64_BIT_COUNT)
	{
		val = val & (UINT64_BIT_MASK >> (UINT64_BIT_COUNT - bit_count));
	}

	return val;
}



uint8 BitStreamGetter::Get8Move(uint8 bit_count)
{
	uint8 val = Get8(bit_count);
	MoveBit(bit_count);
	return val;
}
uint16 BitStreamGetter::Get16Move(uint8 bit_count)
{
	uint16 val = Get16(bit_count);
	MoveBit(bit_count);
	return val;
}
uint32 BitStreamGetter::Get32Move(uint8 bit_count)
{
	uint32 val = Get32(bit_count);
	MoveBit(bit_count);
	return val;
}
uint64 BitStreamGetter::Get64Move(uint8 bit_count)
{
	uint64 val = Get64(bit_count);
	MoveBit(bit_count);
	return val;
}



const char * BitStreamGetter::LenReachedException::what() const throw() { return "BitStreamGetter Length reached"; }
