#include "FilePath.hpp"
#include <iostream>



int main()
{
/*	Paths
e/asd/123		[ "e" "asd" "123" ]
e//asd//123		[ "e" "asd" "123" ]
e///asd///123	[ "e" "asd" "123" ]
./asd/123		[ "." "asd" "123" ]
../asd/123		[ ".." "asd" "123" ]
/e/asd/123		[ "/e" "asd" "123" ]
//e/asd/123		[ "/e" "asd" "123" ]
E:/asd/123		[ "E:" "asd" "123" ]
*/

	{
		const char * str [] {
			"e/asd/123",
			"e//asd//123",
			"e///asd///123",
			"./asd/123",
			"../asd/123",
			"/e/asd/123",
			"//e/asd/123",
			"E:/asd/123",
			"/",
			"//",
			"///",
			"",
			"asd",
			"asd/123",
			"asd/",
			"asd//",
			"asd///",
		}; int len = 17;
		std::cout << '\n';
		for (int i = 0; i < len; i++)
		{
			FilePath path(str[i]);
			std::cout << str[i] << " " << path.Segments.ToString() << '\n';
		}
	}

	std::cout << "main return\n";
	return 0;
}
