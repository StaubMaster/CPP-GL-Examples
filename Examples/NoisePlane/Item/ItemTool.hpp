#ifndef  ITEM_TOOL_HPP
# define ITEM_TOOL_HPP

# include "ItemBase.hpp"

# include "PolyHedra/PolyHedra.hpp"

struct ItemTool : public ItemBase
{
	::PolyHedra *		Pallet = nullptr;
	unsigned int		Count = 0;
	~ItemTool() = default;
	ItemTool() = default;
	ItemTool(::PolyHedra & pallet);
	ItemTool(::PolyHedra * pallet);
};

#endif