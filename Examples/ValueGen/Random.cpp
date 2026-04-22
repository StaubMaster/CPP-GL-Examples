#include "Random.hpp"
#include <cstdlib>



unsigned int Random::Mutilate(unsigned int val)
{
	/* 32 Bit Numbers with 16 0s and 16 1s
	0xD15A2AB5
	0x943B3DA1
	0x38C07F99
	0x256FF109
	0xFF2505C1
	0x54A7C82F
	0xC263176D
	0x0388BBED
	0x569A7748
	0x8E4EED44
	0xE09E2FE0
	0x1E2B2C5E
	0x07FC7A18
	0x630E0FF1
	*/
	val = val + 0xC263176D;
	val = ((val ^ 0xD15A2AB5) << 19) ^ ((val ^ 0x943B3DA1) >> 13);
	val = val + 0xFF2505C1;
	val = ((val ^ 0x38C07F99) << 9) ^ ((val ^ 0x256FF109) >> 23);
	val = val + 0x54A7C82F;
	return val;
}



unsigned int Random::UInt32()
{
	unsigned int r = rand();
	r = r ^ (rand() << 7);
	r = r ^ (rand() << 14);
	r = r ^ (rand() << 21);
	r = r ^ (rand() << 24);
	r = r ^ (rand() << 28);
	return r;
}

float Random::Float01In()
{
	return ((float)(UInt32() & 0x7FFFFFFF)) / 0x80000000;
}
float Random::Float01Ex()
{
	return (float)(UInt32()) / 0xFFFFFFFF;
}
