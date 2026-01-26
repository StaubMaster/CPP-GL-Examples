#include <iostream>
#include <string>



int main(int argc, char * args[])
{
	for (int a = 0; a < argc; a++)
	{
		std::string str(args[a]);
		for (unsigned int i = 2; i < str.size(); i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				if (str[i - 1] != '_')
				{
					std::cout << (char)(str[i] - 'A' + 'a');
				}
				else { std::cout << str[i]; }
			}
			else if (str[i] != '_') { std::cout << str[i]; }
		}
		std::cout << " = ";
		std::cout << str;
		std::cout << ",\n";
	}
}
