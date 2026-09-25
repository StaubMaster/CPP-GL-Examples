#ifndef  ENTRY_CONTAINER_BASE_HPP
# define ENTRY_CONTAINER_BASE_HPP

# include "Entry.hpp"
# include "Generics/Container/Member.hpp"
# include "Generics/Container/Binary.hpp"

namespace EntryContainer
{

template<typename T>
class Base : public Container::Member<T>
{
//	protected:
//	Container::Base<T> &	Data;

	protected:
	Container::Binary<EntryData<T>*>	Entrys;

	protected:
	bool	_IsLocked;

	public:
	bool	_Changed;

	public:
	bool IsLocked() const { return _IsLocked; }
	void Lock() { _IsLocked = true; }
	void UnLock() { _IsLocked = false; }

	public:
	bool Changed() const { return _Changed; }
	void Change() { _Changed = true; }
	void UnChange() { _Changed = false; }



	public:
	Base() : Container::Member<T>(),
		Entrys(),
		_IsLocked(false),
		_Changed(false)
	{ }
	virtual ~Base()
	{
		//delete[] _Data;
		for (unsigned int i = 0; i < Entrys.Count(); i++)
		{
			Entrys[i] -> Container = NULL;
			delete Entrys[i];	// remove this ?
			/*
				EntryData is pointen to in 2 places
				here and in Entry
				if this is deleted then the Entrys still exist
				Container is set to NULL
				so Entry knows that the EntryContainer no longer exists
				and so can safely delete it itself
			*/
		}
	}

	public:
	/*void ShowEntrys() const
	{
		std::cout << "Entrys " << Entrys.Count() << "\n";
		for (unsigned int i = 0; i < Entrys.Count(); i++)
		{
			std::cout << "[" << i << "]";
			std::cout << " ";
			Entrys[i] -> ShowEntry();
		}
	}*/

	public:
	struct FindResult
	{
		unsigned int Idx;
		EntryData<T> * Ptr;

		FindResult() :
			Idx(0xFFFFFFFF),
			Ptr(NULL)
		{ }
		FindResult(unsigned int idx, EntryData<T> * ptr) :
			Idx(idx),
			Ptr(ptr)
		{ }
	};
	protected:
	FindResult FindEntry(EntryData<T> * entry) const
	{
		for (unsigned int i = 0; i < Entrys.Count(); i++)
		{
			if (Entrys[i] == entry) { return FindResult(i, Entrys[i]); }
		}
		return FindResult();
	}
	FindResult FindEntryContaining(unsigned int data_index) const
	{
		for (unsigned int i = 0; i < Entrys.Count(); i++)
		{
			if (data_index >= Entrys[i] -> Min() && data_index <= Entrys[i] -> Max())
			{
				return FindResult(i, Entrys[i]);
			}
		}
		return FindResult();
	}

	FindResult FindNextEntry(unsigned int data_index) const
	{
		unsigned int entry_idx = 0xFFFFFFFF;
		unsigned int entry_dist = 0xFFFFFFFF;
		for (unsigned int i = 0; i < Entrys.Count(); i++)
		{
			if (data_index <= Entrys[i] -> Offset)
			{
				unsigned int dist = Entrys[i] -> Offset - data_index;
				if (dist < entry_dist)
				{
					entry_dist = dist;
					entry_idx = i;
				}
			}
		}
		if (entry_idx != 0xFFFFFFFF)
		{
			return FindResult(entry_idx, Entrys[entry_idx]);
		}
		return FindResult();
	}
	FindResult FindNextEntryDuplicate(EntryData<T> * entry, unsigned int entry_idx) const
	{
		for (unsigned int i = entry_idx; i < Entrys.Count(); i++)
		{
			if (Entrys[i] -> Offset == entry -> Offset &&
				Entrys[i] -> Length == entry -> Length)
			{
				return FindResult(i, Entrys[i]);
			}
		}
		return FindResult();
	}



	public:
	virtual void	Clear() = 0;

	protected:
	virtual unsigned int	CalcLimit(unsigned int wanted_count) = 0;



	public:
	virtual EntryData<T> *	InsertEntry(unsigned int size) = 0;
	virtual void			RemoveEntry(EntryData<T> * entry) = 0;
	virtual EntryData<T> *	DuplicateEntry(EntryData<T> * entry) = 0;
};

};

#endif
