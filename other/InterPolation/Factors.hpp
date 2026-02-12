#ifndef  FACTORS_HPP
# define FACTORS_HPP

template<typename FactorType>
struct Factors
{
	private:
	unsigned int Count;
	FactorType * Data;

	public:
	FactorType & operator[](unsigned int idx)
	{
		return Data[idx];
	}

	Factors(unsigned int count)
	{
		Count = count;
		Data = new FactorType[Count];
	}
	~Factors()
	{
		delete[] Data;
	}

	Factors(const Factors & other)
	{
		Count = other.Count;
		Data = new FactorType[Count];
		for (unsigned int i = 0; i < Count; i++)
		{
			Data[i] = other.Data[i];
		}
	}
	Factors & operator=(const Factors & other)
	{
		Count = other.Count;
		for (unsigned int i = 0; i < Count; i++)
		{
			Data[i] = other.Data[i];
		}
		return *this;
	}

	/*template<typename otherType>
	otherType Sum(Factors<otherType> & other)
	{
		otherType t;
		for (unsigned int i = 0; i < Count; i++)
		{
			t = t + (other.Data[i] * Data[i]);
		}
		return t;
	}*/
};

#endif