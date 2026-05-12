#ifndef  WAIT_DO_TIME_HPP
# define WAIT_DO_TIME_HPP

# include "Telemetry/ValueAverager.hpp"
# include <iostream>

struct WaitDoTime
{
	const char *			Name;
	ValueAverager<float>	DoTime;
	ValueAverager<float>	WaitTime;
	const char * 			ThreadName = "ThreadName";
	WaitDoTime(const char * name);
};
std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj);

#endif