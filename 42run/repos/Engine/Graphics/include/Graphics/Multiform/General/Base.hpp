#ifndef  MULTIFORM_BASE_HPP
# define MULTIFORM_BASE_HPP

# include <string>

# include "Generics/Container/Binary.hpp"

namespace Shader { class Base; };
namespace Uniform { class Layout; class Base; };

namespace Multiform
{
class Layout;
class Base
{
	public:
	std::string							Name;
	Container::Binary<Uniform::Base*>	Uniforms;

	protected:
	virtual ~Base();

	private:
	Base() = delete;
	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;

	protected:
	Base(std::string name);
	Base(Layout & layout, std::string name);

	public:
	void	Clear();

	public:
	void	FindUniforms(Uniform::Layout & layout);
	void	FindUniforms(Uniform::Layout * layout);
	void	FindUniforms(Container::Array<Uniform::Layout*> & layouts);

	public:
	virtual void	PutData(Uniform::Base & uniform) = 0;
	virtual void	PutData(Uniform::Base & uniform, Shader::Base & shader) = 0;

	public:
	void	PutUniformThis();
};
};

#endif