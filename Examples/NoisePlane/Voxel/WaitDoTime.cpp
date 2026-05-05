#include "WaitDoTime.hpp"



WaitDoTime::WaitDoTime()
	: DoTime(64)
	, WaitTime(64)
{ }



std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj)
{
	o << '{';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Max() << 's';
	o << '|';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(5) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Max() << 's';
	o << '}';
	return o;
}
