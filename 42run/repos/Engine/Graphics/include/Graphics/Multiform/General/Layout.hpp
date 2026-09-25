#ifndef  MULTIFORM_LAYOUT_HPP
# define MULTIFORM_LAYOUT_HPP

# include "Generics/Container/Binary.hpp"

namespace Uniform { class Layout; };

namespace Multiform
{
class Base;
class Layout
{
	public:
	void	LogInfo() const;

	public:
	Container::Binary<::Multiform::Base *>	Multiforms;

	public:
	virtual ~Layout();
	Layout();

	Layout(const Layout & other) = delete;
	Layout & operator=(const Layout & other) = delete;

	public:
	void	Find(Uniform::Layout & layout);
	void	Find(Uniform::Layout * layout);
	void	Find(Container::Array<Uniform::Layout*> & layouts);
};
};
	
#endif