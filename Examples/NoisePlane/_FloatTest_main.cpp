// dont want to include cmath for Float Infinity and NaN
// just use division by 0.0

#include "ValueType/uint.hpp"
#include <iostream>
#include <cmath>

// 0x7F800000 +Infinity
// 0xFF800000 -Infinity
// 0x7FC00000 NaN (sign and fraction could be different)

#define TEST_POSITIVE_INFINITY +1 / 0.0f
#define TEST_NEGATIVE_INFINITY -1 / 0.0f
#define TEST_NAN 0 / 0.0f

void ShowFloat32Bits(float val)
{
	std::cout << "val " << val << '\n';

	uint32 bits = *((uint32*)&val);
	std::cout << ToBase16(bits) << '\n';

	uint32 fraction = (bits) & 0x7FFFFF;
	uint32 exponent = (bits >> 23) & 0xFF;
	uint32 sign = (bits >> 31);

	std::cout << ToBase2(sign << (31 - 0), 0) << ' ' << ToBase2(exponent << (31 - 7), 7) << ' ' <<  ToBase2(fraction << (31 - 22), 22) << '\n';
	std::cout << '\n';
}

void ShowValues()
{
	std::cout << '\n';
	{
		std::cout << "Normal\n";
		ShowFloat32Bits(0.15625f);
		ShowFloat32Bits(123.456f);
		ShowFloat32Bits(-9.81f);
	}
	std::cout << '\n';
	{
		std::cout << "Zero\n";
		ShowFloat32Bits(+0.0f);
		ShowFloat32Bits(-0.0f);
	}
	std::cout << '\n';
}
void ShowMacros()
{
	std::cout << '\n';
	{
		std::cout << "+Infinity\n";
		ShowFloat32Bits(+INFINITY);
	}
	std::cout << '\n';
	{
		std::cout << "-Infinity\n";
		ShowFloat32Bits(-INFINITY);
	}
	std::cout << '\n';
	{
		std::cout << "NaN\n";
		ShowFloat32Bits(NAN);
	}
	std::cout << '\n';
}
void ShowMyMacros()
{
	std::cout << '\n';
	{
		std::cout << "+Infinity\n";
		ShowFloat32Bits(TEST_POSITIVE_INFINITY);
	}
	std::cout << '\n';
	{
		std::cout << "-Infinity\n";
		ShowFloat32Bits(TEST_NEGATIVE_INFINITY);
	}
	std::cout << '\n';
	{
		std::cout << "NaN\n";
		ShowFloat32Bits(TEST_NAN);
	}
	std::cout << '\n';
}

int main()
{
	ShowMyMacros();
	return 0;
}
