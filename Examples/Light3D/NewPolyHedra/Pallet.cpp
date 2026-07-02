#include "Pallet.hpp"



NewPolyHedra_Pallet::NewPolyHedra_Pallet()
	: Object(nullptr)
	, Buffer(GL::BufferDataUsage::StaticDraw)
	, Texture()
{ }



void NewPolyHedra_Pallet::GraphicsCreate()
{
	Buffer.Create();
}
void NewPolyHedra_Pallet::GraphicsDelete()
{
	Buffer.Delete();
}
