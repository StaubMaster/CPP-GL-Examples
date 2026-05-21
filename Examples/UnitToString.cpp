#include "UnitToString.hpp"
#include <sstream>
#include <iomanip>


std::string Seperated1000(unsigned int n)
{
	unsigned int part[4];
	part[0] = n % 1000; n = n / 1000;
	part[1] = n % 1000; n = n / 1000;
	part[2] = n % 1000; n = n / 1000;
	part[3] = n % 1000; n = n / 1000;
	std::stringstream ss;
	if (part[3] != 0) { ss << std::setw(3) << std::setfill('0') << part[3] << '.'; }
	if (part[2] != 0) { ss << std::setw(3) << std::setfill('0') << part[2] << '.'; }
	if (part[1] != 0) { ss << std::setw(3) << std::setfill('0') << part[1] << '.'; }
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

#include <math.h>

static thread_local int		string_buffer_idx = 0;
static thread_local char	string_buffer[256];
static const char * string_buffer_done()
{
	string_buffer[string_buffer_idx] = '\0';
	return string_buffer;
}static void string_buffer_new()
{
	string_buffer_idx = 0;
}
static void string_buffer_put(char c)
{
	string_buffer[string_buffer_idx] = c;
	string_buffer_idx++;
}
static void string_buffer_digit_10(int digit)
{
	char c = '?';
	if (digit >= 0 && digit <= 9)
	{
		c = digit + '0';
	}
	string_buffer_put(c);
}

/*static void IntToString(int num)
{
	(void)num;
}*/

const char * FloatToString(float num)
{
	string_buffer_new();
	string_buffer_put('0');
	string_buffer_put('.');

	num = abs(num);
	int full;

	full = num;
	num -= full;

	for (int i = 0; i < 6; i++)
	{
		num *= 10;

		full = num;
		string_buffer_digit_10(full);
		num -= full;
	}

	return string_buffer_done();
}
