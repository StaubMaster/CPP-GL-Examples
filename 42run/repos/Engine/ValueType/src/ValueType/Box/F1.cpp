#include "ValueType/Box/F1.hpp"



BoxF1::BoxF1()
	: Box_1(
		float(+1/0.0f),
		float(-1/0.0f)
	)
{ }
BoxF1::BoxF1(float min, float max)
	: Box_1(min, max)
{ }



#include "../src/ValueType/Box/__.cpp"
#include "../src/ValueType/Box/_1.cpp"
template struct Box__<void, float, BoxF1>;
template struct Box_1<void, float, BoxF1>;
