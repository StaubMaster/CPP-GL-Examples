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

	protected:
	void mResizeLimit(unsigned int limit)
	{
		if (limit == this -> _Limit) { return; }

		Member<T> other;
		this -> Swap(other);
		this -> mAllocate(limit, limit);
		this -> mTransfer(other);
		this -> Swap(other);
		this -> Clear();
		this -> Swap(other);
	}

	protected:
	virtual unsigned int	CalcLimit(unsigned int wanted_count) = 0;

	private:
	void InsertGap(Entry gap)
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
	void RemoveGap(Entry gap)
	{
		for (unsigned int i = gap.Offset; i < this -> _Count; i++)
		{
			this -> _Data[i] = this -> _Data[i + gap.Length];
		}
	}

	public:
	Entry	Insert(const T & item)
	{
		Entry entry(this -> _Count, 1);

		unsigned int newCount = this -> _Count + entry.Length;
		unsigned int newLimit = CalcLimit(newCount);

		this -> mResizeLimit(newLimit);

		if (newCount <= this -> _Limit)
		{
			this -> _Data[entry.Offset] = item;
			this -> _Count = newCount;
		}
		else
		{
			entry.MakeEmpty();
		}
		return entry;
	}
	void	Remove(unsigned int idx)
	{
		Entry entry(idx, 1);
		if (entry.Limit() > this -> _Count) { return; }

		unsigned int newCount = this -> _Count - entry.Length;
		unsigned int newLimit = CalcLimit(newCount);

		RemoveGap(entry);

		this -> mResizeLimit(newLimit);

		this -> _Count = newCount;
	}
};
};

#endif