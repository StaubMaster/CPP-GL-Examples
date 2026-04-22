#include "UnitToString.hpp"
#include <sstream>



std::string Seperated1000(unsigned int n)
{
	unsigned int part[4];
	part[0] = n % 1000; n = n / 1000;
	part[1] = n % 1000; n = n / 1000;
	part[2] = n % 1000; n = n / 1000;
	part[3] = n % 1000; n = n / 1000;
	std::stringstream ss;
	if (part[3] != 0) { ss << part[3] << '.'; }
	if (part[2] != 0) { ss << part[2] << '.'; }
	if (part[1] != 0) { ss << part[1] << '.'; }
	ss << part[0];
	return ss.str();
}

std::string Memory1000ToString(unsigned long long memory)
{
	const char * factor = "B";
	if (memory >= 1000) { memory = memory / 1000; factor = "kB"; }
	if (memory >= 1000) { memory = memory / 1000; factor = "MB"; }
	if (memory >= 1000) { memory = memory / 1000; factor = "GB"; }
	std::stringstream ss;
	ss << memory << factor;
	return ss.str();
}
