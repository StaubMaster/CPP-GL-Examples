#include "3D/Chunk/Graphics.hpp"
#include "3D/Chunk/GraphicsData.hpp"
#include "3D/Chunk.hpp"

#include "Telemetry/StopWatch.hpp"

#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"



void ChunkGraphics::ChangeMedia(const DirectoryInfo & dir)
{
	ShaderU.Change({
		dir.File("Shaders/Voxel/VoxelU.vert"),
		dir.File("Shaders/Voxel/Voxel.frag"),
	});
	ShaderU.AssignLayout(ShaderLayoutU);

	ShaderF.Change({
		dir.File("Shaders/Voxel/VoxelF.vert"),
		dir.File("Shaders/Voxel/Voxel.frag"),
	});
	ShaderF.AssignLayout(ShaderLayoutF);

	BufferLayoutU.Voxel.Change(0);
	BufferLayoutU.Texture.Change(1);
	BufferLayoutU.Chunk.Change(2);
	BufferU.Buffer.AssignLayout(BufferLayoutU);

	BufferLayoutF.Pos.Change(0);
	BufferLayoutF.Tex.Change(1);
	BufferLayoutF.Normal.Change(2);
	BufferF.Buffer.AssignLayout(BufferLayoutF);
}



void ChunkGraphics::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Texture.Create();
	ShaderU.Create();
	ShaderF.Create();
	BufferU.Create();
	BufferF.Create();

	BufferU.Init();
	BufferU.SizeOf = sizeof(VoxelGraphicsDataU::Vertex);
	BufferU.NewSizeMemory(1024 * 1024 * 1024); // 1GiB

	BufferF.Init();
	BufferF.SizeOf = sizeof(VoxelGraphicsDataF::Vertex);
	BufferF.NewSizeMemory(1024 * 1024 * 1024); // 1GiB

	GraphicsExist = true;
}
void ChunkGraphics::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Texture.Delete();
	ShaderU.Delete();
	ShaderF.Delete();
	BufferU.Delete();
	BufferF.Delete();

	BufferU.Buffer.Count = 0;
	BufferF.Buffer.Count = 0;

	GraphicsExist = false;
}



// uint Binary::FindCount(item)
// bool Binary::FindZero(item)
template <typename TypeItem> static bool FindZero(const Container::Binary<TypeItem> & container, const TypeItem & item)
{
	for (unsigned int i = 0; i < container.Count(); i++)
	{
		if (container[i] == item)
		{
			return false;
		}
	}
	return true;
}



unsigned int ChunkGraphics::ChunkThreadQueue::Count()
{
	Mutex.lock();
	unsigned int c = Queue.Count();
	Mutex.unlock();
	return c;
}
void ChunkGraphics::ChunkThreadQueue::Put(Chunk & chunk)
{
	Mutex.lock();

	if (!FindZero(Queue, &chunk))
	{
		Mutex.unlock();
		return;
	}
	Queue.Insert(&chunk);

	Mutex.unlock();
}



ValueAccumulator<float> ChunkGraphics::DrawTotal(64);
ValueAccumulator<float> ChunkGraphics::DrawWait(64);
ValueAccumulator<float> ChunkGraphics::DrawTextureBind(64);
ValueAccumulator<float> ChunkGraphics::DrawShaderBind(64);
ValueAccumulator<float> ChunkGraphics::DrawUpdateBind(64);
ValueAccumulator<float> ChunkGraphics::DrawBufferDraw(64);

//#include <iostream>
void ChunkGraphics::Draw()
{
	if (!GraphicsExist) { return; }



	StopWatch sw;

	sw.Clear();
	Texture.Bind();
	DrawTextureBind.NewValue(sw.ElapsedTime());



	sw.Clear();
	Queue.Mutex.lock();
	for (unsigned int i = 0; i < Queue.Queue.Count(); i++)
	{
		Chunk * ptr = Queue.Queue[i];
		if (ptr == nullptr) { continue; }
		ptr -> GraphicsData_Put();
	}
	Queue.Queue.Clear();
	Queue.Mutex.unlock();
	DrawUpdateBind.NewValue(sw.ElapsedTime());



	sw.Clear();
	ShaderU.Bind();
	DrawShaderBind.NewValue(sw.ElapsedTime());

	sw.Clear();
	BufferU.Bind();
	BufferU.Draw();
	DrawBufferDraw.NewValue(sw.ElapsedTime());



	sw.Clear();
	ShaderF.Bind();
	DrawShaderBind.NewValue(sw.ElapsedTime());

	sw.Clear();
	BufferF.Bind();
	BufferF.Draw();
	DrawBufferDraw.NewValue(sw.ElapsedTime());
}
