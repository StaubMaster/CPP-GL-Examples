#ifndef  UNIT_TO_STRING_HPP
# define UNIT_TO_STRING_HPP



const char *	ToString(unsigned int num, unsigned char digits = 1);
const char *	ToString(float num);



# include <string>

std::string Seperated1000(unsigned int n);

std::string Memory1000ToString(unsigned long long memory);

// stringstream is slow, try to avoid in here ?
// Seperator: remove leading 0

/* Memory1000:
	make a general Unit1000, Memory just has 'B' after
	also make general Unit1024
*/

/* Float
	Time is done in µs, so 6 digits
	do 1000 Units with float ?
	so convert them to ints ?
	but also make a general float to string
*/

#endif