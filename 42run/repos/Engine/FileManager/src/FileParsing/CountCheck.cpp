#include "FileParsing/CountCheck.hpp"
#include <sstream>



CountCheckEqual::CountCheckEqual(unsigned int val)
{
	Val = val;
}
bool CountCheckEqual::Check(unsigned int val) const
{
	return (val == Val);
}
std::string CountCheckEqual::ToString() const
{
	std::ostringstream oss;
	oss << "n == " << Val;
	return oss.str();
}



CountCheckRange::CountCheckRange(unsigned int min, unsigned int max)
{
	Min = min;
	Max = max;
}
bool CountCheckRange::Check(unsigned int val) const
{
	return (val >= Min && val <= Max);
}
std::string CountCheckRange::ToString() const
{
	std::ostringstream oss;
	oss << Min << " <= n == " << Max;
	return oss.str();
}



CountCheckModulo::CountCheckModulo(unsigned int mod, unsigned int val)
{
	Mod = mod;
	Val = val;
}
bool CountCheckModulo::Check(unsigned int val) const
{
	return ((val % Mod) == Val);
}
std::string CountCheckModulo::ToString() const
{
	std::ostringstream oss;
	oss << "(n == " << Mod << ") == " << Val;
	return oss.str();
}
