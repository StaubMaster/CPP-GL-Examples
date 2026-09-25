
#ifndef  UNIFORM_TYPE_BASE_HPP
# define UNIFORM_TYPE_BASE_HPP

# include "Graphics/Uniform/General/Base.hpp"

namespace Uniform
{
template <typename ValueType>
class TypeBase : public Base // rename to TypeBase ?
{
	protected:
	virtual ~TypeBase()
	{ }
	TypeBase() = delete;

	protected:
	TypeBase(std::string name, bool is_dynamic)
		: Base(name, is_dynamic)
	{ }
	TypeBase(Layout & layout, std::string name, bool is_dynamic)
		: Base(layout, name, is_dynamic)
	{ }

	public:
	void	Find(Shader::Base & shader) override
	{
		(void)shader;
	}

	public:
	void	PutVoid(const void * val) override
	{
		Put(*((const ValueType *)val));
	};
	virtual void	Put(const ValueType & obj) = 0;
};
};

#endif
