#include "DataShow.hpp"

#include "ValueType/Bool/3.hpp"
#include "ValueType/Vector/U3.hpp"
#include "ValueType/UndexBox3D.hpp"
#include "ValueType/UndexLoop3D.hpp"

#include <iostream>

int main()
{
	UndexLoop3D loop(
		VectorU3(0xFFFFFFFF - 1, 0xFFFFFFFF - 1, 0xFFFFFFFF - 1), Bool3(false),
		VectorU3(0xFFFFFFFF - 0, 0xFFFFFFFF - 0, 0xFFFFFFFF - 0), Bool3(false)
	);

	std::cout << 0xFFFFFFFF << '\n';
	unsigned int u = 0;
	VectorU3 udx;
	for (udx = loop.Min(); loop.Check(udx).All(true); loop.Next(udx))
	{
		std::cout << u << ' ' << udx << '\n';
		u++;
	}
	std::cout << udx << '\n';

	return 0;
}
