#ifndef  ENTRY_CONTAINER_ENTRY_HPP
# define ENTRY_CONTAINER_ENTRY_HPP

# include "EntryData.hpp"

# include <iostream>

namespace EntryContainer
{

template<typename T>
class Entry
{
	private:
	public:
	EntryData<T> * Data;

	public:
	virtual void DebugInfo() { }

	public:
	Entry()
	{
		Data = NULL;
	}
	Entry(Base<T> & container, unsigned int count)
	{
		Data = container.InsertEntry(count);
	}
	~Entry()
	{
		delete Data;
	}

	Entry(const Entry<T> & other)
	{
		if (other.Data != NULL && other.Data -> Container != NULL)
		{
			Data = other.Data -> Container -> DuplicateEntry(other.Data);
		}
		else
		{
			Data = NULL;
		}
	}
	Entry<T> & operator=(const Entry<T> & other)
	{
		Dispose();
		if (other.Data != NULL)
		{
			Data = other.Data -> Container -> DuplicateEntry(other.Data);
		}
		return *this;
	}

	public:
	unsigned int Length() const { return Data -> Length; }

	private:
	//	these are a lot so extra function
	//	once everything works again, turn these into excpetions
	void CheckData() const
	{
		if (Data == NULL)
		{
			const char * msg = "EntryContainer::Entry Entry Invalid.";
			//std::cout << msg << "\n";
			throw msg;
		}
	}
	/*void CheckDataContainer() const
	{
		if (Data -> Container == NULL)
		{
			const char * msg = "EntryContainer::Entry Entry Invalid.";
			//std::cout << msg << "\n";
			throw msg;
		}
	}*/
	void CheckIndex(unsigned int idx) const
	{
		if (idx >= Data -> Length)
		{
			const char * msg = "EntryContainer::Entry Index invalid.";
			//std::cout << msg << "\n";
			throw msg;
		}
	}

	public:
	const T & operator[](unsigned int idx) const
	{
		CheckData();
		//CheckDataContainer();
		CheckIndex(idx);
		//Data -> Container -> Changed = true;
		//return (Data -> Container -> DataPointer(Data -> Offset))[idx];
		//return (*Data)[idx];
		//return (Data -> Data())[idx];
		return (*Data)[idx];
	}
	const T & operator*() const
	{
		CheckData();
		//CheckDataContainer();
		//return *(Data -> Container -> DataPointer(Data -> Offset));
		//return *(*Data);
		//return *(Data -> Data());
		return *(*Data);
	}
	T & operator[](unsigned int idx)
	{
		CheckData();
		//CheckDataContainer();
		CheckIndex(idx);
		//return (*Data)[idx];
		//return (*Data)[idx];
		//return (Data -> Data())[idx];
		return (*Data)[idx];
	}
	T & operator*()
	{
		CheckData();
		//CheckDataContainer();
		//return *(*Data);
		//return *(*Data);
		//return *(Data -> Data());
		return *(*Data);
	}

	public:
	bool Is() const
	{
		return (Data != NULL);
	}
	void Allocate(Base<T> & container, unsigned int count)
	{
		Dispose();
		Data = container.InsertEntry(count);
	}
	void Dispose()
	{
		if (Data != NULL)
		{
			delete Data;
			Data = NULL;
		}
	}
};

};

#endif