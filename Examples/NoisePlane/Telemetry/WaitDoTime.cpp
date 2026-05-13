#include "WaitDoTime.hpp"
#include <iomanip>



WaitDoTime::WaitDoTime(const char * name)
	: Name(name)
	, DoTime(64)
	, WaitTime(64)
	, ThreadName("ThreadName")
{ }



std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj)
{
//	o << (const void *)obj.ThreadName;
	o << ' ';
	o << '{';
	o << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(4) << obj.WaitTime.Max() << 's';
	o << '|';
	o << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Min() << 's';
	o << ' ';
	o << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Average() << 's';
	o << ' ';
	o << std::fixed << std::setw(6) << std::setfill(' ') << std::setprecision(4) << obj.DoTime.Max() << 's';
	o << '}';
	o << ' ';
	o << obj.Name;
	return o;
}
