#include <iostream>
#include "Generics/Container/Array.hpp"

template<typename TypeItem>
void ArrayInfo(const char * name, const Container::Array<TypeItem> & arr)
{
	std::cout << name;
	std::cout << ' ';
	if (arr.IsNull())
	{
		std::cout << '!';
	}
	else
	{
		std::cout << '_';
	}
	std::cout << '[';
	std::cout << arr.Length();
	std::cout << ']';
	std::cout << (const void *)arr.Memory();
	std::cout << '\n';
}

void TestArray()
{
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Array<int>	arr;
		ArrayInfo("arr", arr);
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Array<int>	arr(12);
		ArrayInfo("arr", arr);
		arr.NewLengthHere(24);
		ArrayInfo("arr", arr);
		arr.NewLengthHere(12);
		ArrayInfo("arr", arr);
		arr.NewLength(24);
		ArrayInfo("arr", arr);
		arr.NewLength(24, 2);
		ArrayInfo("arr", arr);
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Array<int>	arr0(12);
		ArrayInfo("arr0", arr0);

		Container::Array<int>	arr1(arr0);
		ArrayInfo("arr1", arr1);

		std::cout << "arr0.Clear()\n"; arr0.Clear();
		ArrayInfo("arr0", arr0);
		ArrayInfo("arr1", arr1);

		std::cout << "arr0 = arr1\n"; arr0 = arr1;
		ArrayInfo("arr0", arr0);
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Array<int>	arr0({0, 1, 2, 3});
		Container::Array<int>	arr1(arr0);

		ArrayInfo("arr0", arr0);
		for (unsigned int i = 0; i < arr0.Length(); i++)
		{ std::cout << arr0[i] << ' '; }
		std::cout << '\n';

		ArrayInfo("arr1", arr1);
		for (unsigned int i = 0; i < arr1.Length(); i++)
		{ std::cout << arr1[i] << ' '; }
		std::cout << '\n';

		std::cout << "arr0[2] = 9;\n"; arr0[2] = 9;

		ArrayInfo("arr0", arr0);
		for (unsigned int i = 0; i < arr0.Length(); i++)
		{ std::cout << arr0[i] << ' '; }
		std::cout << '\n';

		ArrayInfo("arr1", arr1);
		for (unsigned int i = 0; i < arr1.Length(); i++)
		{ std::cout << arr1[i] << ' '; }
		std::cout << '\n';

		std::cout << "arr1.Seperate()\n"; arr1.Seperate();
		std::cout << "arr0[1] = 9;\n"; arr0[1] = 9;

		ArrayInfo("arr0", arr0);
		for (unsigned int i = 0; i < arr0.Length(); i++)
		{ std::cout << arr0[i] << ' '; }
		std::cout << '\n';

		ArrayInfo("arr1", arr1);
		for (unsigned int i = 0; i < arr1.Length(); i++)
		{ std::cout << arr1[i] << ' '; }
		std::cout << '\n';
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
}
