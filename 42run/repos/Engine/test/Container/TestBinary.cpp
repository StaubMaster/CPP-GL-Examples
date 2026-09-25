#include <iostream>
#include "Generics/Container/Binary.hpp"

template<typename TypeItem>
void BinaryShowInfo(const char * name, const Container::Binary<TypeItem> & cont)
{
	std::cout << name;
	std::cout << ' ';
	if (cont.IsNull())
	{ std::cout << '!'; }
	else
	{ std::cout << '_'; }
	std::cout << '[';
	std::cout << cont.Count();
	std::cout << '|';
	std::cout << cont.Limit();
	std::cout << ']';
	std::cout << (const void *)(cont.ToArray().Memory());
	std::cout << '\n';
}

template<typename TypeItem>
void BinaryShowItems(const Container::Binary<TypeItem> & cont)
{
	for (unsigned int i = 0; i < cont.Count(); i++)
	{ std::cout << cont[i] << ' '; }
	std::cout << '\n';
}

template<typename TypeItem>
void BinaryShowInfoItems(const char * name, const Container::Binary<TypeItem> & cont)
{
	std::cout << name;
	std::cout << ' ';
	if (cont.IsNull())
	{ std::cout << '!'; }
	else
	{ std::cout << '_'; }
	std::cout << '[';
	std::cout << cont.Count();
	std::cout << '|';
	std::cout << cont.Limit();
	std::cout << ']';
	std::cout << (const void *)(cont.ToArray().Memory());
	std::cout << ' ';
	for (unsigned int i = 0; i < cont.Count(); i++)
	{ std::cout << cont[i] << ' '; }
	std::cout << '\n';
}



void TestBinary()
{
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Binary<int>	cont;
		BinaryShowInfo("cont", cont);
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Binary<int>	cont;
		BinaryShowInfo("cont", cont);

		cont.Insert(1);
		BinaryShowInfoItems("cont", cont);

		cont.Insert(2);
		cont.Insert(3);
		cont.Insert(4);
		BinaryShowInfoItems("cont", cont);

		cont.RemoveAt(2);
		BinaryShowInfoItems("cont", cont);

		cont.RemoveAt(0);
		cont.RemoveAt(0);
		cont.RemoveAt(0);
		BinaryShowInfoItems("cont", cont);
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Binary<int>	cont0;
		cont0.Insert(0);
		cont0.Insert(1);
		cont0.Insert(2);
		cont0.Insert(3);
		BinaryShowInfoItems("cont0", cont0);

		Container::Binary<int>	cont1(cont0);
		BinaryShowInfoItems("cont0", cont0);
		BinaryShowInfoItems("cont1", cont1);

		cont1.Insert(4);
		BinaryShowInfoItems("cont0", cont0);
		BinaryShowInfoItems("cont1", cont1);
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
	{
		Container::Binary<int> cont;
		cont.Insert(1);
		cont.Insert(2);
		cont.Insert(3);
		cont.Insert(4);

		Container::Array<int> arr = cont.ToArray();
		std::cout << "cont " << (const void *)cont.ToArray().Memory() << '\n';
		std::cout << "arr " << (const void *)arr.Memory() << '\n';
		cont.Clear();

		std::cout << "arr " << (const void *)arr.Memory() << '\n';
		for (unsigned int i = 0; i < arr.Length(); i++)
		{ std::cout << arr[i] << ' '; }
		std::cout << '\n';
	}
	std::cout << '\n' << "line:" << __LINE__ << '\n' << '\n';
}
