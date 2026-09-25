#ifndef  UNIFORM_LAYOUT_HPP
# define UNIFORM_LAYOUT_HPP

# include "Generics/Container/Binary.hpp"

# include "OpenGLEnums.hpp"

namespace Shader { class Base; };
namespace Multiform { class Base; };

namespace Uniform
{
class Base;
class FloatNBase;
class UIntNBase;
class Buffer;
class Layout
{
	public:
	void	LogInfo() const;

	private:
	Container::Binary<Uniform::Base*>	Uniforms;
	public:
	bool	IsDynamic = false; // delete with Shader
	public:
	void	Clear();
	void	Put(Uniform::Base & uniform);
	void	Put(Uniform::Base * uniform);

	public:
	::Shader::Base *	Shader;
	// AssignShader() ?

	public:
	virtual ~Layout();
	Layout();
	Layout(Shader::Base & shader);

	Layout(const Layout & other);
	Layout & operator=(const Layout & other) = delete;

	public:
	bool	IsBound() const;
	void	Bind();

	public:
	void	Find();
	void	Find(Multiform::Base & multiform);

	public:
	void	UpdateData();

	public:
	void	Bind(Buffer & uniform, GL::BlockBinding binding);
};
};

#endif