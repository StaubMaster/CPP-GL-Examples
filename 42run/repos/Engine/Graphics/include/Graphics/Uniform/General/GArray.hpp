
#ifndef  GENERIC_UNIFORM_ARRAY_HPP
# define GENERIC_UNIFORM_ARRAY_HPP

# include "Graphics/Uniform/General/Base.hpp"
# include "Graphics/Uniform/General/TypeBase.hpp"

# include <sstream>

namespace Uniform
{
template <typename UniformType, typename DataType>
class GArray
{
	//	Use Containers
	public:
	const unsigned int	Limit;

	private:
	UniformType **	Uniforms;

	public:
	GArray(Uniform::Layout & layout, std::string name, unsigned int count)
		: Limit(count)
	{
		Uniforms = new UniformType*[Limit];
		for (unsigned int i = 0; i < Limit; i++)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			Uniforms[i] = new UniformType(layout, ss.str());
		}
	}
	~GArray()
	{
		for (unsigned int i = 0; i < Limit; i++)
		{
			delete Uniforms[i];
		}
		delete[] Uniforms;
	}

	public:
	UniformType & operator[](unsigned int index)
	{
		return *(Uniforms[index]);
	}

	public:
	void PutData(DataType * data, unsigned int count)
	{
		if (Limit < count) { count = Limit; }
		for (unsigned int i = 0; i < count; i++)
		{
			Uniforms[i] -> PutData(data[i]);
		}
	}
};
};

#endif
