#ifndef  ATTRIBUTE_LAYOUT_HPP
# define ATTRIBUTE_LAYOUT_HPP

# include "Generics/Container/Binary.hpp"

# include "OpenGLEnums.hpp"

namespace Attribute
{
class Base;
class Layout
{
	public:
	void	LogInfo() const;

	private:
	Container::Binary<Attribute::Base*>		Attributes;
	public:
	bool	IsDynamic = false; // delete with Buffer
	public:
	void	Clear();
	void	Put(Attribute::Base & attribute);
	void	Put(Attribute::Base * attribute);

	public:
	GL::AttributeDivisor					Divisor;
	GL::AttributeStride						Stride;

	public:
	virtual ~Layout();
	Layout() = delete;
	Layout(GL::AttributeDivisor divisor, GL::AttributeStride stride);
	Layout(GL::AttributeDivisor divisor);

	Layout(const Layout & other);
	Layout & operator=(const Layout & other) = delete;

	public:
	void	Bind() const;

	public:
	void	CalcStride();
};
};

#endif