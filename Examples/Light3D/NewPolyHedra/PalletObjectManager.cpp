#include "PalletObjectManager.hpp"
#include "Pallet.hpp"

#include "Graphics/Attribute/General/Layout.hpp"
#include "OpenGL.hpp"



NewPolyHedra_PalletObjectManager::NewPolyHedra_PalletObjectManager()
	: Pallet(nullptr)
	, BufferVertexArray()
	, Buffer(GL::BufferDataUsage::StreamDraw)
{ }



void NewPolyHedra_PalletObjectManager::VertexBufferInit()
{
	BufferVertexArray.Bind();
	Buffer.Bind();
	Buffer.Update();
	if (Pallet != nullptr)
	{
		Pallet -> Buffer.Bind();
		if (Pallet -> Layout != nullptr)
		{
			Pallet -> Layout -> Bind();
		}
	}
	VertexArray::BindNone();
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
void NewPolyHedra_PalletObjectManager::GraphicsDraw()
{
	InstancesToBuffer();
	if (Pallet != nullptr)
	{
		BufferVertexArray.Bind();
		Buffer.Bind();
		Pallet -> Buffer.Bind();
		Pallet -> Texture.Bind();
		GL::DrawArraysInstanced(GL::DrawMode::Triangles, 0
			, Pallet -> Buffer.Count
			, Buffer.Count
		);
	}
}
