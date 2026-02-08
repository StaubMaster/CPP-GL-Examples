
#include <iostream>

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/Container/Tight.hpp"
#include "Miscellaneous/Container/Fixed.hpp"
#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/Pointer.hpp"



void Show_Header(const char * name)
{
	std::cout << "\n\n";
	std::cout << "################################\n";
	std::cout << name << '\n';
	std::cout << "################################\n";
}
void Show_Footer()
{
	std::cout << "################################\n";
	std::cout << "\n\n";
}



void Container_Show(Container::Member<int> & container)
{
	std::cout << "[" << container.Limit() << "|" << container.Count() << "]";
	for (unsigned int i = 0; i < container.Limit(); i++)
	{
		std::cout << " ";
		if (i < container.Count())
		{ std::cout << container[i]; }
		else
		{ std::cout << "|"; }
	}
	std::cout << "\n";
}
void Container_Show_Insert(Container::Member<int> & container, int item)
{
	Container::Entry entry(container.Count(), 1);
	std::cout << "[" << entry.Offset << "|" << entry.Length << "]";
	//for (unsigned int i = 0; i < container.Limit(); i++)
	for (unsigned int i = 0; i < entry.Limit(); i++)
	{
		std::cout << " ";
		if (i >= entry.Min() && i <= entry.Max())
		{ std::cout << "+"; }
		else
		{ std::cout << " "; }
	}
	std::cout << "\n";
	(void)item;
}
void Container_Show_Remove(Container::Member<int> & container, unsigned int idx)
{
	Container::Entry entry(idx, 1);
	std::cout << "[" << entry.Offset << "|" << entry.Length << "]";
	for (unsigned int i = 0; i < entry.Limit(); i++)
	{
		std::cout << " ";
		if (i >= entry.Min() && i <= entry.Max())
		{ std::cout << "-"; }
		else
		{ std::cout << " "; }
	}
	std::cout << "\n";
	(void)container;
}



void Container_Insert(Container::Base<int> & container, int item)
{
	Container_Show_Insert(container, item);
	container.Insert(item);
	Container_Show(container);
}
void Container_Remove(Container::Base<int> & container, unsigned int idx)
{
	Container_Show_Remove(container, idx);
	container.Remove(idx);
	Container_Show(container);
}



void Test_Container_Binary_IncDec()
{
	Show_Header("Container::Binary::IncDec");

	Container::Binary<int> cont;
	Container_Show(cont);

	Container_Insert(cont, 0);
	Container_Insert(cont, 1);
	Container_Insert(cont, 2);
	Container_Insert(cont, 3);
	Container_Insert(cont, 4);
	Container_Insert(cont, 5);

	Container_Remove(cont, 3);
	Container_Remove(cont, 3);
	Container_Remove(cont, 2);

	Show_Footer();
}
void Test_Container_Binary_Swap()
{
	Show_Header("Container::Binary::Swap");

	Container::Binary<int> cont0;
	for (unsigned int i = 0; i < 5; i++)
	{ cont0.Insert(0); }

	Container::Binary<int> cont1;
	for (unsigned int i = 0; i < 2; i++)
	{ cont1.Insert(1); }

	std::cout << '\n';
	std::cout << "cont0: "; Container_Show(cont0);
	std::cout << "cont1: "; Container_Show(cont1);

	cont0.Swap(cont1);

	std::cout << '\n';
	std::cout << "cont0: "; Container_Show(cont0);
	std::cout << "cont1: "; Container_Show(cont1);

	cont1.Swap(cont0);

	std::cout << '\n';
	std::cout << "cont0: "; Container_Show(cont0);
	std::cout << "cont1: "; Container_Show(cont1);

	Show_Footer();
}
void Test_Container_Binary_Bind()
{
	Show_Header("Container::Binary::Bind");

	Container::Binary<int> cont;
	for (unsigned int i = 0; i < 5; i++)
	{ cont.Insert(i); }

	Container::Binary<int> bind;
	std::cout << "cont.Data: " << cont.Data() << '\n';
	std::cout << "bind.Data: " << bind.Data() << '\n';
	std::cout << "== ?: " << (cont.Data() == bind.Data()) << '\n';
	std::cout << '\n';
	
	bind.Bind(cont);
	std::cout << "cont.Data: " << cont.Data() << '\n';
	std::cout << "bind.Data: " << bind.Data() << '\n';
	std::cout << "== ?: " << (cont.Data() == bind.Data()) << '\n';
	std::cout << '\n';

	Container_Show(cont);
	Container_Show(bind);
	std::cout << '\n';

	Show_Footer();
}
void Test_Container_Binary_Copy()
{
	Show_Header("Container::Binary::Copy");

	Container::Binary<int> cont;
	for (unsigned int i = 0; i < 5; i++)
	{ cont.Insert(i); }

	Container::Binary<int> copy;
	std::cout << "cont.Data: " << cont.Data() << '\n';
	std::cout << "copy.Data: " << copy.Data() << '\n';
	std::cout << "== ?: " << (cont.Data() == copy.Data()) << '\n';
	std::cout << '\n';

	copy.Copy(cont);
	std::cout << "cont.Data: " << cont.Data() << '\n';
	std::cout << "copy.Data: " << copy.Data() << '\n';
	std::cout << "== ?: " << (cont.Data() == copy.Data()) << '\n';
	std::cout << '\n';

	Container_Show(cont);
	Container_Show(copy);
	std::cout << '\n';

	Show_Footer();
}
void Test_Container_Binary()
{
	Test_Container_Binary_IncDec();
	Test_Container_Binary_Swap();
	Test_Container_Binary_Bind();
	Test_Container_Binary_Copy();
}

void Test_Container_Tight_IncDec()
{
	Show_Header("Container::Tight::IncDec");

	Container::Tight<int> cont;
	Container_Show(cont);

	Container_Insert(cont, 0);
	Container_Insert(cont, 1);
	Container_Insert(cont, 2);
	Container_Insert(cont, 3);
	Container_Insert(cont, 4);
	Container_Insert(cont, 5);

	Container_Remove(cont, 1);
	Container_Remove(cont, 1);
	Container_Remove(cont, 2);

	Container_Remove(cont, 4);

	Show_Footer();
}
void Test_Container_Tight()
{
	Test_Container_Tight_IncDec();
}

void Test_Container_Fixed_IncDec()
{
	Show_Header("Container::Fixed::IncDec");

	Container::Fixed<int> cont;
	Container_Show(cont);
	cont.Allocate(4);
	Container_Show(cont);

	Container_Insert(cont, 0);
	Container_Insert(cont, 1);
	Container_Insert(cont, 2);
	Container_Insert(cont, 3);
	Container_Insert(cont, 4);
	Container_Insert(cont, 5);

	Container_Remove(cont, 1);
	Container_Remove(cont, 1);
	Container_Remove(cont, 2);

	Container_Remove(cont, 4);

	Show_Footer();
}
void Test_Container_Fixed_Contruct()
{
	Show_Header("Container::Fixed(n)");

	Container::Fixed<int> cont(4);
	Container_Show(cont);

	Container_Insert(cont, 0);
	Container_Insert(cont, 1);
	Container_Insert(cont, 2);
	Container_Insert(cont, 3);
	Container_Insert(cont, 4);
	Container_Insert(cont, 5);

	Container_Remove(cont, 1);
	Container_Remove(cont, 1);
	Container_Remove(cont, 2);

	Container_Remove(cont, 4);

	Show_Footer();
}
void Test_Container_Fixed()
{
	Test_Container_Fixed_IncDec();
	Test_Container_Fixed_Contruct();
}

void Test_Container_Array_Empty()
{
	Show_Header("Container::Array()");

	Container::Array<int> cont;
	Container_Show(cont);
	cont.Allocate(4, 4);
	Container_Show(cont);

	Show_Footer();
}
void Test_Container_Array_Number()
{
	Show_Header("Container::Array(n)");

	Container::Array<int> cont(4);
	Container_Show(cont);

	Show_Footer();
}
void Test_Container_Array()
{
	Test_Container_Array_Empty();
	Test_Container_Array_Number();
}

void Test_Container_Pointer()
{
	int arr[4];
	arr[0] = 3;
	arr[1] = 2;
	arr[2] = 1;
	arr[3] = 0;
	Container::Pointer<int> cont(arr, 4);
	Container_Show(cont);

	cont[0] = 9;
	Container_Show(cont);

	cont[3] = 8;
	Container_Show(cont);
}

void Test_Container_Binary_Bind_Pointer()
{
	Container::Binary<int> binary;
	for (unsigned int i = 0; i < 5; i++)
	{ binary.Insert(i); }

	Container_Show(binary);

	Container::Pointer<int> pointer(binary);

	Container_Show(pointer);
}
void Test_Container()
{
	Test_Container_Binary_Bind_Pointer();
}



int main()
{
	//Test_Container_Binary();
	//Test_Container_Tight();
	//Test_Container_Fixed();
	//Test_Container_Array();
	//Test_Container_Pointer();
	Test_Container();
	std::cout << "\nmain() return\n";
	return 0;
}
