#ifndef  MULTIFORM_GENERIC_BASE_HPP
# define MULTIFORM_GENERIC_BASE_HPP

# include "Graphics/Multiform/General/Base.hpp"

# include "Graphics/Uniform/General/Base.hpp"
# include "Graphics/Uniform/General/Layout.hpp"

# include "Graphics/Shader/Base.hpp"

namespace Multiform
{
template <typename DataType>
class GBase : public Base
{
	public:
	DataType	Data;

	public:
	virtual ~GBase()
	{ }
	GBase(std::string name)
		: Base(name)
	{ }

	public:
	void	PutData(Uniform::Base & uniform) override
	{
		uniform.PutVoid(&Data);
		uniform.Multiform = nullptr;
	}
	void	PutData(Uniform::Base & uniform, Shader::Base & shader) override
	{
		(void)uniform;
		(void)shader;
	}

	public:
	void	ChangeData(const DataType & data)
	{
		Data = data;
		PutUniformThis();
	}
};
};

#endif