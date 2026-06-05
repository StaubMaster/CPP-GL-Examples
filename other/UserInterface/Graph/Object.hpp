#ifndef  UI_GRAPH_OBJECT_HPP
# define UI_GRAPH_OBJECT_HPP

# include "ValueType/Box/F2.hpp"
# include "ValueType/ColorF4.hpp"

namespace UI
{
namespace Graph
{
struct ObjectData;

struct Object
{
	ObjectData *	Data;

	bool		Is() const;

	bool		Visibility() const;
	void		Hide();
	void		Full();

	BoxF2 &		Box();

	~Object();
	Object();
	Object(const Object & other);
	Object & operator=(const Object & other);

	void	Delete();
	void	Create();
};
};
};

#endif