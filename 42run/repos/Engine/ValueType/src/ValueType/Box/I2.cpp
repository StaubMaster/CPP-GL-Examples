#include "ValueType/Box/I2.hpp"



BoxI2::BoxI2()
	: Box_2(
		VectorI2(0x7FFFFFFF),
		VectorI2(0x80000000)
	)
{ }
BoxI2::BoxI2(VectorI2 min, VectorI2 max)
	: Box_2(min, max)
{ }



#include "../src/ValueType/Box/__.cpp"
#include "../src/ValueType/Box/_2.cpp"
template struct Box__<int, VectorI2, BoxI2>;
template struct Box_2<int, VectorI2, BoxI2>;
