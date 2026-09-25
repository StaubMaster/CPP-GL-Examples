#include "FilePath.hpp"
#include <iostream>



int main()
{
	std::cout << '\n';
	{
		FilePath here = FilePath::Here();
		std::cout << here << '\n';

		FilePath parent = here.Parent();
		std::cout << parent << '\n';

		FilePath child = here.Child("asd/123");
		std::cout << child << '\n';
	}
	std::cout << '\n';

	std::cout << "main return\n";
	return 0;
}
