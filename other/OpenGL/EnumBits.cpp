#include <iostream>

enum class Enum1 : unsigned int
{
	Val01 = 0b01,
	Val10 = 0b10,
};

Enum1 operator|(Enum1 val0, Enum1 val1) { return (Enum1)((unsigned int)val0 | (unsigned int)val1); }
std::ostream & operator<<(std::ostream & stream, Enum1 val)
{
	switch (val)
	{
		case Enum1::Val01: stream << "Val01"; break;
		case Enum1::Val10: stream << "Val10"; break;
		default: stream << ((unsigned int)val); break;
	}
	return stream;
}

int main()
{
	Enum1 var0 = Enum1::Val01;
	Enum1 var1 = Enum1::Val10;
	Enum1 var2 = var0 | var1;
	std::cout << "var0: " << var0 << '\n';
	std::cout << "var1: " << var1 << '\n';
	std::cout << "var2: " << var2 << '\n';
	return 0;
}
