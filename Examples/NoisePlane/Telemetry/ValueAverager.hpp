#ifndef  VALUE_AVERAGER_HPP
# define VALUE_AVERAGER_HPP

template<typename ValueType>
class ValueAverager
{
	public:
	unsigned int	Limit;
	unsigned int	Count;
	unsigned int	Index;
	ValueType *		Data;

	public:
	ValueType	Min() const
	{
		if (Count == 0) { return 0; }
		ValueType val = Data[0];
		for (unsigned int i = 1; i < Count; i++)
		{
			if (val > Data[i])
			{
				val = Data[i];
			}
		}
		return val;
	}
	ValueType	Max() const
	{
		if (Count == 0) { return 0; }
		ValueType val = Data[0];
		for (unsigned int i = 1; i < Count; i++)
		{
			if (val < Data[i])
			{
				val = Data[i];
			}
		}
		return val;
	}
	ValueType	Sum() const
	{
		ValueType sum = 0;
		for (unsigned int i = 0; i < Count; i++)
		{
			sum += Data[i];
		}
		return sum;
	}
	ValueType	Average() const
	{
		return Sum() / Count;
	}

	void		NewValue(ValueType value)
	{
		Data[Index] = value;
		Index++;

		if (Index == Limit)
		{
			Index = 0;
		}
		if (Count < Index)
		{
			Count = Index;
		}
	}
	void		Clear()
	{
		Count = 0;
		Index = 0;
	}

	public:
	~ValueAverager()
	{
		delete[] Data;
	}
	ValueAverager() = delete;
	ValueAverager(unsigned int limit)
		: Limit(limit)
		, Count(0)
		, Index(0)
		, Data(new ValueType[Limit])
	{ }
	ValueAverager(const ValueAverager & other) = delete;
	ValueAverager & operator=(const ValueAverager & other) = delete;
};

#endif