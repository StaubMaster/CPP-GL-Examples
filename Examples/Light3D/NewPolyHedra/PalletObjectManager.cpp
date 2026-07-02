#include "PalletObjectManager.hpp"
#include "Pallet.hpp"

#include "OpenGL.hpp"



NewPolyHedra_PalletObjectManager::NewPolyHedra_PalletObjectManager()
	: Pallet(nullptr)
	, BufferVertexArray()
	, Buffer(GL::BufferDataUsage::StreamDraw)
{ }



void NewPolyHedra_PalletObjectManager::Draw()
{
	InstancesToBuffer();

	BufferVertexArray.Bind();
	//Buffer.Bind();
	//Pallet -> Buffer.Bind();
	Pallet -> Texture.Bind();
	GL::DrawArraysInstanced(GL::DrawMode::Triangles, 0
		, Pallet -> Buffer.Count
		, Buffer.Count
	);
}



void NewPolyHedra_PalletObjectManager::GraphicsCreate()
{
	Buffer.Create();
	BufferVertexArray.Create();
}
void NewPolyHedra_PalletObjectManager::GraphicsDelete()
{
	Buffer.Delete();
	BufferVertexArray.Delete();
}
