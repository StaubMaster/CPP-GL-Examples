#ifndef  CONTAINER_BASE_HPP
# define CONTAINER_BASE_HPP

# include "Member.hpp"
# include "Entry.hpp"



namespace Container
{
template<typename T>
class Base : public Member<T>
{
	public:
	Base() : Member<T>()
	{ }
	virtual ~Base()
	{ }

	Base(const Base<T> & other) = delete;
	Base & operator=(const Base<T> & other) = delete;

	public:
	virtual void	Clear() = 0;
	void	Remember(T * data, unsigned int limit, unsigned int count = 0)
	{
		Clear();
		this -> mRemember(data, limit, count);
	}
	void	Allocate(unsigned int limit, unsigned int count = 0)
	{
		Clear();
		this -> mAllocate(limit, count);
	}

	protected:
	virtual void	mAssign(const Member<T> other) = 0;

	public:
	void	Assign(const Member<T> other)
	{
		Clear();
		mAssign(other);
	}
	void	Bind(const Member<T> & other)
	{
		Clear();
		this -> mBind(other);
	}
	void	Copy(const Member<T> & other)
	{
		Clear();
		this -> mCopy(other);
	}

	private:
	void mResizeLimit(unsigned int limit)
	{
		if (limit == this -> _Limit) { return; }

		Member<T> other;
		this -> Swap(other);
		this -> mAllocate(limit, limit);
		this -> mTransfer(other);
		this -> Swap(other);
		this -> mDelete();
		this -> Swap(other);
	}

	protected:
	virtual unsigned int	CalcLimit(unsigned int wanted_count) = 0;

	public:
	void	Trim()
	{
		mResizeLimit(this -> _Count);
	}
	void	MakeNativeSize()
	{
		mResizeLimit(CalcLimit(this -> _Count));
	}

	private:
	void	InsertGap(Entry gap)
	{
		//	done in reverse, else it would override
		if (this -> _Count != 0)
		{
			for (unsigned int i = this -> _Count - 1; i >= gap.Offset; i--)
			{
				this -> _Data[i + gap.Length] = this -> _Data[i];
			}
		}
	}
	void	RemoveGap(Entry gap)
	{
		for (unsigned int i = gap.Offset; i < this -> _Count; i++)
		{
			this -> _Data[i] = this -> _Data[i + gap.Length];
		}
	}

	public:
	Entry	Insert(const Member<T> & items)
	{
		Entry entry(this -> _Count, items.Count());

		unsigned int newCount = this -> _Count + entry.Length;
		unsigned int newLimit = CalcLimit(newCount);

		mResizeLimit(newLimit);

		if (newCount <= this -> _Limit)
		{
			for (unsigned int i = 0; i < entry.Length; i++)
			{
				this -> _Data[entry.Offset + i] = items[i];
			}
			this -> _Count = newCount;
		}
		else
		{
			entry.MakeEmpty();
		}
		return entry;
	}

	public:
	Entry	Insert(const T & item)
	{
		Container::Member<T> items;
		items.mRemember(&item, 1, 1);
		return Insert(items);
	}
	void	Remove(unsigned int idx)
	{
		Entry entry(idx, 1);
		if (entry.Limit() > this -> _Count) { return; }

		unsigned int newCount = this -> _Count - entry.Length;
		unsigned int newLimit = CalcLimit(newCount);

		RemoveGap(entry);

		mResizeLimit(newLimit);

		this -> _Count = newCount;
	}
};
};

#endif