#include "WaitDoTime.hpp"
#include <iomanip>



WaitDoTime::WaitDoTime(const char * name)
	: Name(name)
	, DoTime(64)
	, WaitTime(64)
	, ThreadName("ThreadName")
{ }



const int digits = 6;

std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj)
{
	o << obj.ThreadName;
	o << ' ';
	o << '{';
	o << std::fixed << std::setw(2 + digits) << std::setfill(' ') << std::setprecision(digits) << obj.WaitTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(2 + digits) << std::setfill(' ') << std::setprecision(digits) << obj.WaitTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(2 + digits) << std::setfill(' ') << std::setprecision(digits) << obj.WaitTime.Max() << 's';
	o << '|';
	o << std::fixed << std::setw(2 + digits) << std::setfill(' ') << std::setprecision(digits) << obj.DoTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(2 + digits) << std::setfill(' ') << std::setprecision(digits) << obj.DoTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(2 + digits) << std::setfill(' ') << std::setprecision(digits) << obj.DoTime.Max() << 's';
	o << '}';
	o << ' ';
	o << obj.Name;
	return o;
}
