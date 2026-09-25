#include "ValueType/DepthFactors.hpp"



DepthFactors::DepthFactors(float near, float far)
{
	Near = near;
	Far = far;
	Calc();
}



void DepthFactors::Calc()
{
	Diff = Far - Near;
	Summ = Far + Near;
	Mul2 = Far * Near * 2;

	Factor0 = Summ / Diff;
	Factor1 = Mul2 / Diff;
}

void DepthFactors::ChangeNear(float near)
{
	Near = near;
	Calc();
}
void DepthFactors::ChangeFar(float far)
{
	Far = far;
	Calc();
}
