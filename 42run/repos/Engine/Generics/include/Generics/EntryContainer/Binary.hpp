#ifndef  ENTRY_CONTAINER_BINARY_HPP
# define ENTRY_CONTAINER_BINARY_HPP

# include "Base.hpp"
# include "Generics/Container/Binary.hpp"

namespace EntryContainer
{

template<typename T>
class Binary : public Base<T>
{
//	//public:
//	//	unsigned int Count() const { return _Count; }

//	public:
//	virtual void DebugInfo() override { }

	public:
	Binary() : Base<T>()
	{ }
	~Binary()
	{ }

	public:
	/*void ShowData() const override
	{
		std::cout << "Container Data: " << _Count << " " << this -> _Limit << "\n";
		for (unsigned int i = 0; i < this -> _Limit; i++)
		{
			//if ((i % 8) == 0) { if (i != 0) { std::cout << "\n"; } }
			//else { std::cout << " "; }
			if (i != 0) { std::cout << " "; }
			std::cout << this -> _Data[i];
		}
		if (this -> _Limit != 0) { std::cout << "\n"; }
	}*/

	public:
	bool IsCompact() const
	{
		unsigned int data_idx = 0;
		for (unsigned int i = 0; i < this -> Entrys.Count(); i++)
		{
			EntryData<T> * entry = this -> FindEntryContaining(data_idx).Ptr;
			if (entry == NULL) { return false; }
			if (entry -> Offset != data_idx) { return false; }
			data_idx += entry -> Length;
		}
		if (this -> _Count != data_idx) { return false; }
		return true;
	}
	//	dosent handle duplicate entrys
	/*void CompactLimit()
	{
		unsigned int limit = 0;
		for (unsigned int i = 0; i < this -> Entrys.Count(); i++)
		{
			limit += this -> Entrys[i] -> Length;
		}
		T * data = new T[limit];

		unsigned int data_idx;
		for (unsigned int i = 0; i < this -> Entrys.Count(); i++)
		{
			for (unsigned int j = 0; j < this -> Entrys[i] -> Length; j++)
			{
				data[data_idx + j] = (*this -> Entrys[i])[j];
			}
			this -> Entrys[i] -> Offset = data_idx;
			data_idx += this -> Entrys[i] -> Length;
		}

		delete[] this -> _Data;
		this -> _Data = data;
		this -> _Limit = limit;
	}*/

	void CompactHere()
	{
		unsigned int data_idx = 0;
		unsigned int entry_idx = this -> FindNextEntry(data_idx).Idx;
		this -> _Count = 0;
		while (entry_idx != 0xFFFFFFFF)
		{
			EntryData<T> * entry = this -> Entrys[entry_idx];
			if (entry -> Limit() > this -> _Count) { this -> _Count = entry -> Limit(); }
			unsigned int dupe_idx = this -> FindNextEntryDuplicate(entry, entry_idx + 1).Idx;
			entry -> Move(data_idx);
			if (dupe_idx == 0xFFFFFFFF)
			{
				data_idx = entry -> Limit();
				entry_idx = this -> FindNextEntry(data_idx).Idx;
			}
			else
			{
				entry_idx = dupe_idx;
			}
		}
	}

	public:
	void	Clear() override
	{
		this -> mDelete();
	}

	private:
	void mResizeLimit(unsigned int limit)
	{
		if (limit == this -> _Limit) { return; }

		Container::Member<T> other;
		this -> Swap(other);
		this -> mAllocate(limit, limit);
		this -> mTransfer(other);
		this -> Swap(other);
		this -> mDelete();
		this -> Swap(other);
	}

	private:
	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		for (unsigned char shift = 31; shift < 32; shift--)
		{
			unsigned int size = 0xFFFFFFFF >> shift;
			if (size >= wanted_count)
			{
				return size;
			}
		}
		return 0;
	}

	public:
	EntryData<T> * InsertEntry(unsigned int size) override
	{
		if (this -> _IsLocked) { return NULL; }

		unsigned int newCount = this -> _Count + size;
		//unsigned int newLimit = Container::Behaviour::BinarySize(newCount);
		unsigned int newLimit = CalcLimit(newCount);

		mResizeLimit(newLimit);

		EntryData<T> * entry = new EntryData<T>(this, this -> _Count, size);
		this -> Entrys.Insert(entry);
		this -> _Changed = true;
		this -> _Count = newCount;
		return entry;
	}
	void RemoveEntry(EntryData<T> * entry) override
	{
		if (this -> _IsLocked) { return; }
		this -> _Changed = true;
		unsigned int entry_idx = this -> FindEntry(entry).Idx;
		if (entry_idx == 0xFFFFFFFF)
		{
			//std::cout << "EntryContainer::Dynamic Entry not found." << "\n";
			throw "EntryContainer::Dynamic Entry not found.";
		}
		this -> Entrys.Remove(entry_idx);
		entry -> Container = NULL;
		/*if (this -> FindNextEntryDuplicate(entry, 0).Idx == 0xFFFFFFFF)
		{
			_Count -= entry -> Length;
		}*/
	}
	EntryData<T> * DuplicateEntry(EntryData<T> * entry) override
	{
		if (this -> _IsLocked) { return NULL; }
		if (entry == NULL)
		{
			return NULL;
		}
		EntryData<T> * other = new EntryData<T>(*entry);
		this -> Entrys.Insert(other);
		return other;
	}
};

};

#endif
