#include "ValueType/Box/F2.hpp"



BoxF2::BoxF2()
	: Box_2(
		VectorF2(+1/0.0f),
		VectorF2(-1/0.0f)
	)
{ }
BoxF2::BoxF2(VectorF2 min, VectorF2 max)
	: Box_2(min, max)
{ }



#include "../src/ValueType/Box/__.cpp"
#include "../src/ValueType/Box/_2.cpp"
template struct Box__<float, VectorF2, BoxF2>;
template struct Box_2<float, VectorF2, BoxF2>;
