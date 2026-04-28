#ifndef  ITEM_BASE_HPP
# define ITEM_BASE_HPP

struct VectorF2;

struct ItemBase
{
	unsigned int	Count;
	~ItemBase();
	ItemBase();
	virtual void	Show(VectorF2 pos) = 0;
	virtual void	Hide() = 0;
};

#endif