#ifndef  ENTRY_CONTAINER_ENTRY_DATA_HPP
# define ENTRY_CONTAINER_ENTRY_DATA_HPP

# include "Generics/Container/Entry.hpp"

namespace EntryContainer
{

template<typename T> class Base;

template<typename T>
class EntryData : public Container::Entry
{
	public:
	Base<T> * Container;

	public:
	virtual void DebugInfo() override { }

	public:
	EntryData() : Container::Entry()
	{
		Container = nullptr;
	}
	EntryData(const EntryData & other) : Container::Entry(other)
	{
		Container = other.Container;
	}
	EntryData(Base<T> * container, unsigned int off, unsigned int len) : Container::Entry(off, len)
	{
		Container = container;
	}
	virtual ~EntryData()
	{
		if (Container != nullptr)
		{
			Container -> RemoveEntry(this);
		}
	}

	private:
	void CheckContainer() const
	{
		if (Container == nullptr)
		{
			const char * msg = "EntryContainer::EntryData Entry Container Invalid.";
			//std::cout << msg << "\n";
			throw msg;
		}
	}
	void CheckIndex(unsigned int idx) const
	{
		if (idx >= this -> Length)
		{
			const char * msg = "EntryContainer::EntryData Index invalid.";
			//std::cout << msg << "\n";
			throw msg;
		}
	}

	public:
	T * Data() const
	{
		CheckContainer();
		return &((*Container)[Offset]);
	}

	public:
	const T & operator[](unsigned int idx) const
	{
		CheckContainer();
		CheckIndex(idx);
		return (*Container)[Offset + idx];
	}
	const T & operator*() const
	{
		CheckContainer();
		return (*Container)[Offset];
	}
	T & operator[](unsigned int idx)
	{
		CheckContainer();
		CheckIndex(idx);
		Container -> Change();
		return (*Container)[Offset + idx];
	}
	T & operator*()
	{
		CheckContainer();
		Container -> Change();
		return (*Container)[Offset];
	}

	public:
	/*void ShowEntry() const
	{
		std::cout << "{" << Offset << " " << Length << "}";
		std::cout << " ";
		std::cout << "[" << Min() << " " << Max() << "]";
		//for (unsigned int i = 0; i < Length; i++)
		//{
		//	std::cout << " ";
		//	std::cout << (*this)[i];
		//}
		std::cout << "\n";
	}*/

	public:
	void Move(unsigned int offset)
	{
		for (unsigned int i = 0; i < this -> Length; i++)
		{
			(*Container)[offset + i] = (*Container)[this -> Offset + i];
		}
		this -> Offset = offset;
	}
};

};

#endif