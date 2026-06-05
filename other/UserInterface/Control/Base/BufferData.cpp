#include "BufferData.hpp"



UI::Control::Main::BufferData::BufferData()
{ }
UI::Control::Main::BufferData::BufferData(VectorF2 pos)
	: Pos(pos)
{ }



UI::Control::Inst::BufferData::BufferData()
{ }
UI::Control::Inst::BufferData::BufferData(BoxF2 box, float layer, ColorF4 col)
	: Box(box)
	, Layer(layer)
	, Col(col)
{ }
