#include "ItemTool.hpp"



ItemTool::ItemTool(::PolyHedra & pallet)
	: ItemBase()
	, Pallet(&pallet)
{ }
ItemTool::ItemTool(::PolyHedra * pallet)
	: ItemBase()
	, Pallet(pallet)
{ }
