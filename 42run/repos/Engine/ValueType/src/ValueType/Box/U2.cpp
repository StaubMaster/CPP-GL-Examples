#include "ValueType/Box/U2.hpp"
#include "ValueType/Bool/2.hpp"



BoxU2::BoxU2()
	: Box_2(
		VectorU2(0xFFFFFFFF),
		VectorU2(0x00000000)
	)
{ }
BoxU2::BoxU2(VectorU2 min, VectorU2 max)
	: Box_2(min, max)
{ }



#include "../src/ValueType/Box/__.cpp"
#include "../src/ValueType/Box/_2.cpp"
template struct Box__<unsigned int, VectorU2, BoxU2>;
template struct Box_2<unsigned int, VectorU2, BoxU2>;
