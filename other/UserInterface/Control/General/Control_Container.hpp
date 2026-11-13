#ifndef  UI_CONTROL_CONTROL_CONTAINER_HPP
# define UI_CONTROL_CONTROL_CONTAINER_HPP

# include "Generics/Container/Binary.hpp"

struct DisplayPosition;

namespace UI
{
namespace Control
{
template <typename Type>
class Control_Container
{
	public:
	Container::Binary<Type*>	Children;

	public:
	virtual void	ChildClear()
	{
		Children.Clear();
	}
	virtual void	ChildRemove(Type & control)
	{
		for (unsigned int i = 0; i < Children.Count(); i++)
		{
			if (Children[i] == &control)
			{
				Children.RemoveAt(i);
				i--;
			}
		}
	}
	virtual void	ChildInsert(Type & control)
	{
		Children.Insert(&control);
	}

	public:
	void	ChildRemove(Type * control)
	{
		if (control != nullptr)
		{
			ChildRemove(*control);
		}
	}
	void	ChildInsert(Type * control)
	{
		if (control != nullptr)
		{
			ChildInsert(*control);
		}
	}

	private:	virtual	bool		Check(const DisplayPosition & display_pos) const = 0;
	public:		virtual	Type *		Find(const DisplayPosition & display_pos) = 0;



	public:
	virtual ~Control_Container() = default;
	Control_Container() = default;
	Control_Container(const Control_Container & other) = delete;
	Control_Container & operator=(const Control_Container & other) = delete;
};
};
};

#endif