#include "BufferData.hpp"



UI::Graph::BufferData::BufferData()
{ }
UI::Graph::BufferData::BufferData(BoxF2 box, VectorF2 pos, ColorF4 col)
	: Box(box)
	, Pos(pos)
	, Col(col)
{ }
