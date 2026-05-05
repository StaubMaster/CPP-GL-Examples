#ifndef  WAIT_DO_TIME_HPP
# define WAIT_DO_TIME_HPP

# include "Telemetry/ValueAverager.hpp"
# include <iostream>

struct WaitDoTime
{
	ValueAverager<float>	DoTime;
	ValueAverager<float>	WaitTime;
	WaitDoTime();
};
std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj);

#endif