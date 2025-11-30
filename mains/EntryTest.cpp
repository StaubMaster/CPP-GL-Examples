
#include <iostream>

#include "Debug.hpp"

#include "Miscellaneous/Container/Base.hpp"
#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Base.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/EntryData.hpp"
#include "Miscellaneous/EntryContainer/Entry.hpp"



struct TestObj
{
	int data0;
	int data1;

	TestObj()
	{
		
	}
	~TestObj()
	{
		
	}

	TestObj(const TestObj & other)
	{
		data0 = other.data0;
		data1 = other.data1;
	}
	TestObj & operator=(const TestObj & other)
	{
		data0 = other.data0;
		data1 = other.data1;
		return *this;
	}
};

EntryContainer::Dynamic<TestObj> * Container0;
Container::Dynamic<EntryContainer::Entry<TestObj>> * Container1;



void Init()
{
	std::cout << "\nInit ...\n\n";
	Container0 = new EntryContainer::Dynamic<TestObj>();
	Container1 = new Container::Dynamic<EntryContainer::Entry<TestObj>>();
	std::cout << "\nInit done\n\n";
}
void Populate()
{
	std::cout << "\nPopulate ...\n\n";
	EntryContainer::Entry<TestObj> entry(*Container0, 1);
	Container1 -> Insert(entry);
	(*entry).data0 = 123;
	(*entry).data0 = 444;
	std::cout << "\nPopulate done\n\n";
}
void Free()
{
	std::cout << "\nFree ...\n\n";
	delete Container1;
	delete Container0;
	std::cout << "\nFree done\n\n";
}
void Frame()
{
	std::cout << "Frame" << '\n';
	for (unsigned int i = 0; i < Container0 -> Count(); i++)
	{
		std::cout << "data0" << ' ' << ((*Container0)[i].data0) << '\n';
		std::cout << "data1" << ' ' << ((*Container0)[i].data1) << '\n';
	}
	std::cout << '\n';
	for (unsigned int i = 0; i < Container1 -> Count(); i++)
	{
		for (unsigned int j = 0; j < (*Container1)[i].Length(); j++)
		{
			std::cout << "data0" << ' ' << ((*Container1)[i][j]).data0 << '\n';
			std::cout << "data1" << ' ' << ((*Container1)[i][j]).data0 << '\n';
		}
	}
	std::cout << '\n';
}



int main()
{
	try
	{
		Init();
		Populate();
		Frame();
		Frame();
		Frame();
		Free();
	}
	catch (std::exception & ex)
	{
		std::cerr << "Error: " << ex.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "Error: " << "Unknown" << '\n';
	}
	std::cout << "\nmain() return\n\n";
	return 0;
}
