#include "UnitToString.hpp"



static thread_local int		string_buffer_idx = 0;
static thread_local char	string_buffer[256];
static const char * string_buffer_done()
{
	string_buffer[string_buffer_idx] = '\0';
	return string_buffer;
}
static void string_buffer_new()
{
	string_buffer_idx = 0;
}
static void string_buffer_reverse()
{
	int i = 0;
	int j = string_buffer_idx - 1;
	char temp;
	while (i < j)
	{
		temp = string_buffer[i];
		string_buffer[i] = string_buffer[j];
		string_buffer[j] = temp;
		i++;
		j--;
	}
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

static void string_buffer_uint32_rev(unsigned int num, unsigned char digits)
{
	for (int i = 0; i < 10; i++)
	{
		unsigned int digit = num % 10;
		num /= 10;
		if (digit != 0 || i < digits)
		{
			string_buffer_digit_10(digit);
		}
	}
}



#include <math.h>

const char * ToStringU32(unsigned int num, unsigned char digits)
{
	string_buffer_new();

	string_buffer_uint32_rev(num, digits);
	string_buffer_reverse();

	return string_buffer_done();
}
const char * ToStringI32(int num, unsigned char digits)
{
	string_buffer_new();

	string_buffer_uint32_rev(num, digits);
	if (num > 0) { string_buffer_put('+'); }
	if (num < 0) { string_buffer_put('-'); }
	// for padding, give 0 a ' '
	// also give 0x7FFFFFFF a ' ' since its kind of both ?
	string_buffer_reverse();

	return string_buffer_done();
}
const char * ToStringF32(float num, unsigned char digits_after, unsigned char digits_before)
{
	string_buffer_new();

	char sign = '!';
	if (num == 0.0f)     { sign = ' '; }
	else if (num > 0.0f) { sign = '+'; }
	else if (num < 0.0f) { sign = '-'; }

	num = abs(num);
	int full;

	full = num;
	num -= full;
	string_buffer_uint32_rev(full, digits_before);
	string_buffer_put(sign);
	string_buffer_reverse();

	string_buffer_put('.');
	for (int i = 0; i < digits_after; i++)
	{
		num *= 10;

		full = num;
		string_buffer_digit_10(full);
		num -= full;
	}

	return string_buffer_done();
}



const char * ToString(unsigned int num, unsigned char digits)
{ return ToStringU32(num, digits); }
const char * ToString(int num, unsigned char digits)
{ return ToStringI32(num, digits); }
const char * ToString(float num, unsigned char digits_after, unsigned char digits_before)
{ return ToStringF32(num, digits_after, digits_before); }



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
