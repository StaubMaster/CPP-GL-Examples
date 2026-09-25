#include "ValueType/Box/I3.hpp"



BoxI3::BoxI3()
	: Box_3(
		VectorI3(0x7FFFFFFF),
		VectorI3(0x80000000)
	)
{ }
BoxI3::BoxI3(VectorI3 min, VectorI3 max)
	: Box_3(min, max)
{ }



#include "../src/ValueType/Box/__.cpp"
#include "../src/ValueType/Box/_3.cpp"
template struct Box__<int, VectorI3, BoxI3>;
template struct Box_3<int, VectorI3, BoxI3>;
