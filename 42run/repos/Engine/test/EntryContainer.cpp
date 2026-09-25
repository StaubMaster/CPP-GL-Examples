#include "Miscellaneous/EntryContainer/Binary.hpp"

#include <iostream>



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



void Test_EntryContainer_Binary()
{
	EntryContainer::Binary<int> container;
	Container_Show(container);
	//container.ShowEntrys();

	std::cout << "Allocate\n";
	EntryContainer::Entry<int> ent0(container, 4);
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
	
	std::cout << "Allocate\n";
	EntryContainer::Entry<int> ent1(container, 3);
	//container.ShowEntrys();
	Container_Show(container);
	std::cout << "\n";
	
	std::cout << "Allocate\n";
	EntryContainer::Entry<int> ent2(container, 2);
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
	
	std::cout << "Allocate\n";
	EntryContainer::Entry<int> ent3(container, 5);
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
	
	std::cout << "Allocate\n";
	EntryContainer::Entry<int> ent4(container, 5);
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent0.Length(); i++) { ent0[i] = 1; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent1.Length(); i++) { ent1[i] = 2; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent2.Length(); i++) { ent2[i] = 3; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent3.Length(); i++) { ent3[i] = 4; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent4.Length(); i++) { ent4[i] = 5; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
	
	std::cout << "Dispose\n";
	ent1.Dispose();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
	
	std::cout << "Dispose\n";
	ent3.Dispose();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent0.Length(); i++) { ent0[i] = 10; }
	for (unsigned int i = 0; i < ent2.Length(); i++) { ent2[i] = 20; }
	for (unsigned int i = 0; i < ent4.Length(); i++) { ent4[i] = 30; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
	
	std::cout << "Is Compact " << container.IsCompact() << "\n";
	std::cout << "\n";

	std::cout << "Compact Here\n";
	//container.MakeCompact();
	container.CompactHere();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Is Compact " << container.IsCompact() << "\n";
	std::cout << "\n";

	//std::cout << "Allocate\n";
	//ent1.Allocate(container, 9);
	////container.ShowData();
	//std::cout << "\n";

	//std::cout << "Change\n";
	//for (unsigned int i = 0; i < ent1.Length(); i++) { ent1[i] = 9; }
	////container.ShowData();
	//std::cout << "\n";
}
void Test_EntryContainer_EntryCopy()
{
	EntryContainer::Binary<int> container;
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Allocate\n";
	EntryContainer::Entry<int> ent0(container, 4);
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	//std::cout << "Copy\n";
	//EntryContainer::Entry<int> ent1(ent0);
	//ContainerData(container);
	//container.ShowEntrys();
	//std::cout << "\n";

	std::cout << "Copy\n";
	EntryContainer::Entry<int> ent2;
	ent2 = ent0;
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Change\n";
	for (unsigned int i = 0; i < ent0.Length(); i++) { ent0[i] = i; }
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Compact\n";
	container.CompactHere();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Dispose\n";
	ent0.Dispose();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	//std::cout << "Dispose\n";
	//ent1.Dispose();
	//ContainerData(container);
	//container.ShowEntrys();
	//std::cout << "\n";

	std::cout << "Dispose\n";
	ent2.Dispose();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";

	std::cout << "Compact\n";
	container.CompactHere();
	Container_Show(container);
	//container.ShowEntrys();
	std::cout << "\n";
}
void Test_EntryContainer_Changed()
{
	EntryContainer::Binary<int> container;

	std::cout << "changed " << container.Changed() << "\n";
	std::cout << "Entry()\n";
	EntryContainer::Entry<int> entry(container, 1);
	std::cout << "changed " << container.Changed() << "\n";
	std::cout << '\n';

	container.UnChange();
	std::cout << "changed " << container.Changed() << "\n";
	std::cout << "Entry operator*\n";
	*entry = 123;
	std::cout << "changed " << container.Changed() << "\n";
	std::cout << '\n';

	container.UnChange();
	std::cout << "changed " << container.Changed() << "\n";
	std::cout << "Entry operator[]\n";
	entry[0] = 123;
	std::cout << "changed " << container.Changed() << "\n";
}



int main()
{
	//Test_EntryContainer_Binary();
	//Test_EntryContainer_EntryCopy();
	//Test_EntryContainer_Changed();

	std::cout << "\nmain() return\n";
	return 0;
}
