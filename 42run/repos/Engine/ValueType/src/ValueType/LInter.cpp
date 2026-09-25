#include "ValueType/LInter.hpp"



LInter::LInter(float t0, float t1)
	: _T0(t0)
	, _T1(t1)
{ }



LInter LInter::T0() { return LInter(1.0f, 0.0f); }
LInter LInter::T1() { return LInter(0.0f, 1.0f); }



void LInter::SetT0(float val) { _T0 = val; _T1 = 1.0f - val; }
void LInter::SetT1(float val) { _T1 = val; _T0 = 1.0f - val; }

float LInter::GetT0() const { return _T0; }
float LInter::GetT1() const { return _T1; }



float LInter::Interpolate(float val0, float val1)
{
	return (val0 * _T0) + (val1 * _T1);
}
